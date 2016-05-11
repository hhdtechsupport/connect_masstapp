<?php
/**
 * @file
 * Custom pages for CAPTConnect.
 */

/**
 * Menu callback.
 * View the registrations for the Event.
 */
function captconnect_custom_view_registrations($node) {
  global $user;
  if ($node->type == 'event') {
    drupal_set_title(t('Registrations for event "!title"', array('!title' => $node->title)));

    $event = entity_metadata_wrapper('node', $node);
    $date_format = variable_get('captconnect_custom_register_date_format', 'long_day_at_time');
    $lines_per_page = variable_get('captconnect_custom_register_lines_per_page', 10);

    $reg_flag = flag_get_flag('registration');
    $part_flag = flag_get_flag('participate');

    // Get all the instances.
    $instances = array();
    foreach ($event->field_date_instance->getIterator() as $instance) {
      $dates = $instance->field_date->value();
      $start_time = strtotime($dates['value'] . ' UTC');
      $end_time = strtotime($dates['value2'] . ' UTC');
      $instances[] = array('start' => $start_time, 'end' => $end_time, 'instance' => $instance);
    }
    usort($instances, '_captconnect_custom_sort_instances');

    $table = array(
      'rows' => array(),
      'header' => array(
        t('Registrant'),
        t('Registered'),
        t('Cancel Registration'),
        t('Participation'),
        ),
      'attributes' => array(
        'id' => 'registrations-list',
        ),
      'sticky' => TRUE,
      'empty' => t('There are currently no instances of this event.'),
      );

    foreach ($instances as $instance_data) {
      // Note that $instance is metadata_wrapper form.
      $instance = $instance_data['instance'];
      $dates = $instance->field_date->value();
      $limit = $instance->field_max_registration->value();
      $start_time = $instance_data['start'];
      $lead_time = variable_get('captconnect_custom_participate_lead_time', 1800);

      // Whether to show "cancel" and "participate" links.
      $show_links = node_access('update', $node);
      if (!$show_links) {
        unset($table['header'][3], $table['header'][2]);
      }

      // Is the event instance past?
      $instance_is_past = ($instance_data['end'] < REQUEST_TIME);

      // Is the instance at max capacity?
      $instance_is_full = ($reg_flag->get_count($instance->nid->value()) >= $limit && $limit > 0);

      // We can link the instance title to its node if the setting says so
      // and the user has permission.
      $instance_label = format_date($instance_data['start'], $date_format);
      if (variable_get('captconnect_custom_registrations_link_instance', 1)
      && (user_access('edit any instance content')
      || (user_access('edit own instance content') && $instance->uid->value() == $user->uid))) {
        $title_link = l($instance_label, 'node/' . $instance->nid->value() . '/edit',
          array('query' => drupal_get_destination()));

      }
      else {
        $title_link = $instance_label;
      }

      if ($instance_is_past) {
        $title_link .= ' <span class="instance-complete">' . t('Complete') . '</span>';
      }

      if ($instance_is_full) {
        $title_link .= ' <span class="instance-full">' . t('Full') . '</span>';
      }

      $table['rows'][] = array(array(
        'data' => $title_link,
        'colspan' => 20,
        'class' => array('instance-label'),
        ));

      // Get the event join link.
      $link = $instance->field_link->value();

      // Get all the registration details.
      $rows = db_select('flagging', 'f')
        ->fields('f', array('uid', 'timestamp'))
        ->condition('f.entity_id', $instance->nid->value())
        ->condition('f.fid', $reg_flag->fid)
        ->extend('PagerDefault')
        ->limit($lines_per_page)
        ;
      $rows = $rows->execute()
        ->fetchAllKeyed()
        ;

      if (count($rows) > 0) {
        $users = entity_load('user', array_keys($rows));
        foreach ($users as $uid => $account) {
          $registrant = (user_access('administer users') ?
            l(format_username($account), "user/$account->uid/edit") : format_username($account));
          $roles = $account->roles;
          unset($roles[DRUPAL_AUTHENTICATED_RID]);
          if ($user->uid == $uid) {
            $roles[] = 'me';
          }

          $join_class = array('join-link');
          $join_class[] = ($user->uid == $uid ? 'mark' : 'proxy');

          // Query parameter for all links below.
          $query = drupal_get_destination();
          $query += array('token' => flag_get_token($instance->nid->value()));

          if ($user->uid == $uid) {
            $reg_link = l(t($reg_flag->get_label('unflag_short', $instance->nid->value())),
              'flag/unflag/registration/' . $instance->nid->value(), array('query' => $query));
          }
          else {
            // @TODO: Cancel registration for someone else.
            $reg_link = l(t($reg_flag->get_label('unflag_short', $instance->nid->value())),
              'event/unregister/' . $instance->nid->value() . '/' . $account->uid, array('query' => $query));
          }

          if ($part_flag->is_flagged($instance->nid->value(), $uid)) {
            if ($user->uid == $uid) {
              $join = flag_create_link('participate', $instance->nid->value());
            }
            else {
              $attrs = array('title' => $part_flag->get_label('unflag_long', $instance->nid->value()));
              $join = l($part_flag->get_label('unflag_short', $instance->nid->value()),
                'event/participate/' . $instance->nid->value() . '/' . $account->uid,
                array('query' => $query, 'attributes' => $attrs));
            }
          }
          else {
            if ($user->uid == $uid) {
              $join = flag_create_link('participate', $instance->nid->value());
            }
            else {
              $attrs = array('title' => $part_flag->get_label('flag_long', $instance->nid->value()));
              $join = l($part_flag->get_label('flag_short', $instance->nid->value()),
                'event/participate/' . $instance->nid->value() . '/' . $account->uid,
                array('query' => $query, 'attributes' => $attrs));
            }
          }

          // Build the table row.
          $row = array(
            array('data' => $registrant, 'class' => array('registrant-name')),
            array('data' => format_date($rows[$uid]), 'class' => array('date-registered')),
            );

          // If this user has flagging permission, show the links.
          if ($show_links) {
            $row[] = array('data' => $reg_link, 'class' => array('cancel-link'));
            $row[] = array('data' => $join, 'class' => $join_class);
          }
          $table['rows'][] = array(
            'data' => $row,
            'class' => array_map('drupal_html_class', $roles),
            );
        }
      }

      // Display Access information.
      $text = $instance->field_access_information->value();
      if (!empty($text['value'])) {
        $table['rows'][] = array(array(
          'data' => check_markup($text['value'], $text['format']),
          'colspan' => 20,
          'class' => array('access-information'),
          ));
      }
    }

    // Place the table and pager.
    $ret = theme('table', $table);
    $pager = array('#theme' => 'pager', '#weight' => 50);
    $ret .= drupal_render($pager);

    // In order to access the "register other" button, they need
    // to be in the same group and have 'register others' permission.
    if (user_access('bypass node access')) {
      $in_nodes_group = TRUE;
    }
    else {
      $in_nodes_group = FALSE;
      foreach ($node->og_group_ref[LANGUAGE_NONE] as $group) {
        if (og_is_member('node', $group['target_id'], 'user')) {
          $in_nodes_group = TRUE;
          break;
        }
      }
    }
    if ($in_nodes_group && user_access('register others')) {
      $register_others = array(
        '#theme' => 'link',
        '#text' => t(variable_get('captconnect_custom_proxy_register_text', 'Register Someone Else')),
        '#path' => 'register_others',
        '#options' => array(
          'attributes' => array('class' => array('button', 'pretty-button', 'register-others-button')),
          'html' => FALSE,
          'query' => drupal_get_destination(),
          ),
        );
    }
    else {
      $register_others = NULL;
    }

    $ret .= drupal_render($register_others);

    return $ret;
  }
}

/**
 * Menu callback.
 * View the registration questions for the Event.
 */
function captconnect_custom_view_questions($node) {
  global $user;
//  dpm($node, 'captconnect_custom_view_questions');
  $no_yes = array(t('No'), t('Yes'));
  $output = '<div id="questions-and-answers">';
  $css = '#questions-and-answers table {width:31%;float:left;margin-right:1em;}
    ';
  drupal_add_css($css, 'inline');

  if ($node->type == 'event') {
    if (isset($node->field_question[LANGUAGE_NONE])) {
      foreach ($node->field_question[LANGUAGE_NONE]as $quest) {
        $question = node_load($quest['target_id']);
        $table = array(
          'header' => array(),
          'rows' => array(),
          'empty' => t('Could not find anything.'),
          'attributes' => array(
            'id' => 'answers-' . $question->nid,
            'class' => array('question-answers'),
            ),
          'caption' => l($question->title, 'node/'.$question->nid),
          );
        // Handle answers here.
        if (isset($question->field_answers[LANGUAGE_NONE])) {
          foreach ($question->field_answers[LANGUAGE_NONE] as $ans) {
            $answer = node_load($ans['target_id']);
            $answ = $answer->field_answer[LANGUAGE_NONE][0]['value'];
            switch ($question->field_question_type[LANGUAGE_NONE][0]['value']) {
              case 'yesno':
                $answ = $no_yes[$answ];
                break;

              case 'select':
                $answ = array();
                if (count($answer->field_answer[LANGUAGE_NONE])) {
                  foreach ($answer->field_answer[LANGUAGE_NONE] as $value) {
                    $answ[] = $value['safe_value'];
                  }
                  $answ = (count($answ) > 1 ?
                    theme('item_list', array('items' => $answ)) : $answ[0]);
                }
                break;

              case 'text':
                break;
            }
            $table['rows'][] = array($answ);
          }
        }
        $output .= theme('table', $table);
      }
    }
  }
  else {
    $output = t("I don't understand how you got here.");
  }

  return $output . '</div>';
}

/**
 * Menu Callback
 * Show a list of Presenter activity.
 */
function captconnect_custom_presenter_list() {
  $output = '';

  $table = array(
    'header' => array(
      /*t('Picture')*/ '',
      array('data' => t('Name'), 'field' => 'title', 'sort' => 'asc'),
      t('Event'),
      ),
    'rows' => array(),
    'attributes' => array(
      'id' => 'presenter-list',
      ),
    'empty' => t('There are no presenters to show.'),
    'sticky' => TRUE,
    );

  $pquery = db_select('node', 'n')
    ->extend('PagerDefault')
    ->extend('TableSort')
    ->limit(variable_get('captconnect_custom_presenters_list_limit', 10))
    ->orderByHeader($table['header']);
  $pquery->condition('n.status', 1);
  $pquery->condition('n.type', 'presenter');
  $pquery->join('field_data_field_presenter_image', 'i', 'i.entity_id = n.nid');
  $pquery->join('file_managed', 'f', 'f.fid = i.field_presenter_image_fid');
  $pquery->fields('n', array('nid', 'title'));
  $pquery->addField('f', 'uri');

  $style = variable_get('captconnect_custom_presenters_list_style', 'presenter_image');

  $result = $pquery->execute();
  $event_query = "SELECT e.field_events_target_id AS event_id, ne.title AS event "
    . "FROM {field_data_field_events} e "
    . "INNER JOIN {node} ne ON ne.nid = e.field_events_target_id "
    . "WHERE e.entity_id = :presenter "
    . "ORDER BY ne.title "
    ;
  foreach ($result as $row) {
    $events = db_query($event_query, array(':presenter' => $row->nid))->fetchAllAssoc('event_id', PDO::FETCH_ASSOC);
    $event_list = theme('item_list', array('items' => array_map('_captconnect_custom_link_events', $events)));

    $table['rows'][] = array(
      theme('image_style', array('path' => $row->uri, 'style_name' => $style)),
      l($row->title, 'node/' . $row->nid),
      $event_list,
      );
  }

  $output .= theme('table', $table);
  $pager = array('#theme' => 'pager', '#weight' => 50);
  $output .= drupal_render($pager);

  return $output;
}

/**
 * Helper function for linking events.
 */
function _captconnect_custom_link_events($a) {
  $instance_list = db_select('field_data_field_date_instance', 'd');
  $instance_list->condition('d.entity_id', $a['event_id']);
  $instance_list->join('node', 'n', 'n.nid = d.field_date_instance_target_id');
  $instance_list->addField('n', 'title');

  if (!variable_get('captconnect_custom_presenters_list_show_past', 0)) {
    $instance_list->join('field_data_field_date', 'id', 'id.entity_id = n.nid');
    $instance_list->condition('id.field_date_value2', gmdate('Y-m-d H:i:s', REQUEST_TIME), '>');
  }

  $instances = $instance_list->execute()->fetchCol();
  $class = array('event-name');
  if ($instances) {
    $ret = array(
     'data' => l($a['event'], 'node/' . $a['event_id'], array('attributes' => array('class' => array('event-name'))))
      . ' <span class="instance-list">'
      . implode(', ', $instances)
      . '</span>',
    'class' => array('scheduled'),
    );
  }
  else {
    $ret = array(
      'data' => l($a['event'], 'node/' . $a['event_id'], array('attributes' => array('class' => array('event-name')))),
      'class' => array('not-scheduled'),
      );
  }

  return $ret;
}

/**
 * Menu Callback
 * Show a list of Pending Anon Log Ins.
 */
function captconnect_custom_anon_pending() {
  // See if we are to do cleanup.
  if (isset($_GET['delete'])) {
    $clean_up = $_GET['delete'];
    drupal_set_message(t('Removing records older than @int days.',
      array('@int' => $clean_up)));
    // Make it in seconds.
    $clean_up = $clean_up * 86400;
  }
  else {
    $clean_up = FALSE;
  }

  // Get the existing records.
  $query = "SELECT ar.uid, ar.nid, n.title AS instance, en.nid AS enid, "
    . "en.title AS event, rn.realname, u.name, u.created, u.mail "
    . "FROM {captconnect_custom_anon_register} ar "
    . "LEFT JOIN {node} n ON n.nid = ar.nid "
    . "LEFT JOIN {realname} rn ON rn.uid = ar.uid "
    . "LEFT JOIN {users} u ON u.uid = ar.uid "
    . "LEFT JOIN field_data_field_related_events ev ON ev.entity_id = ar.nid "
    . "LEFT JOIN node en ON en.nid = ev.field_related_events_target_id "
    ;
  $result = db_query($query);

  $table = array(
    'header' => array(t('User'), t('Event'), t('Instance'), t('Created'), t('Email')),
    'rows' => array(),
    'attributes' => array('id' => 'anon-pending-table'),
    'empty' => t('No pending anonymous logins.'),
    );

  foreach ($result as $row) {
    if (is_null($row->name)) {
      if ($clean_up) {
        drupal_set_message(t('Deleting user @id', array('@id' => $row->uid)));
        db_delete('captconnect_custom_anon_register')
          ->condition('uid', $row->uid)
          ->execute();
      }
      else {
        drupal_set_message(t('User @uid is invalid.', array('@uid' => $row->uid)));
      }
    }
    else {
      $name = filter_xss((empty($row->realname) ? $row->name : $row->realname))
        . ' (' . $row->uid . ')';
      $table['rows'][] = array(
        l($name, 'user/' . $row->uid . '/edit'),
        l($row->event, 'node/' . $row->enid),
        l($row->instance, 'node/' . $row->nid),
        format_date($row->created),
        $row->mail,
        );
      if ($clean_up && ((REQUEST_TIME - $row->created) > $clean_up)) {
        drupal_set_message(t('Deleting user @id', array('@id' => $name)));
        db_delete('captconnect_custom_anon_register')
          ->condition('uid', $row->uid)
          ->execute();
      }
    }
  }

  return theme('table', $table);
}

function captconnect_custom_view_user_content($account) {
  $query = "SELECT type, COUNT(*) AS num FROM {node} "
    . "WHERE status = 1 AND uid = :uid "
    . "GROUP BY type ORDER BY type ";
  $result = db_query($query, array(':uid' => $account->uid));

  $table = array(
    'header' => array(
      ),
    'rows' => array(),
    'attributes' => array('style' => 'width:auto;'),
    'empty' => 'There is no content for ' . format_username($account),
    );
  $node_type_present = module_exists('node_type');
  $types = node_type_get_names();

  foreach ($result as $row) {
    $type = ($node_type_present ?
      l($types[$row->type], 'node/type/' . $row->type . '/' . $account->uid)
      : filter_xss($types[$row->type]));
    $table['rows'][] = array(
      $type,
      number_format($row->num, 0),
      );
  }
  return theme('table', $table);
}
