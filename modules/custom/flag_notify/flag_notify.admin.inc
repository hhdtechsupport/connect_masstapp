<?php
/**
 * @file
 * Adminstrative functions for Flag Notify.
 */

/**
 * Main settings form.
 */
function flag_notify_admin_settings($form, $form_state, $flag = NULL) {
  dpm($flag, 'working flag');
  global $user;
  $form = array('#flag' => $flag);
  $noyes = array(t('No'), t('Yes'));

  $all_flags = flag_get_flags();

  $form['flag_notify_flag_message_' . $flag->name] = array(
    '#type' => 'textarea',
    '#size' => 8,
    '#title' => t('"@msg" email template', array('@msg' => $flag->flag_long)),
    '#default_value' => variable_get('flag_notify_flag_message_' . $flag->name, 'Thanks'),
    );

  $form['flag_notify_unflag_message_' . $flag->name] = array(
    '#type' => 'textarea',
    '#size' => 8,
    '#title' => t('"@msg" email template', array('@msg' => $flag->unflag_long)),
    '#default_value' => variable_get('flag_notify_unflag_message_' . $flag->name, 'Thanks'),
    );

  $roles = array('-1' => t('Author')) + user_roles(TRUE);
  unset ($roles[DRUPAL_AUTHENTICATED_RID]);
  foreach ($roles as $rid => $name) {
    $roles[$rid] = ucwords($name);
  }

  $form['flag_notify_flag_roles_' . $flag->name] = array(
    '#type' => 'checkboxes',
    '#options' => $roles,
    '#title' => t('Roles to notify'),
    '#default_value' => variable_get('flag_notify_flag_roles_' . $flag->name, array()),
    '#description' => t('Send the notification only to the people in these roles.'),
    );

  if (module_exists('og')) {
    $form['flag_notify_flag_group_' . $flag->name] = array(
      '#type' => 'radios',
      '#options' => $noyes,
      '#title' => t('Restrict to OG group'),
      '#default_value' => variable_get('flag_notify_flag_group_' . $flag->name, 0),
      '#description' => t('Send the notification only to the roles selected
        within the same OG group as the content being flagged.'),
      );
  }

  $form['tokens'] = array(
    '#theme' => 'token_tree_link',
    '#token_types' => array('node', 'flag', 'flagging'),
    );

  $form['#theme'] = 'flag_notify_admin_settings';

//  dpm($form, 'form');
  return system_settings_form($form);
}

/**
 * Theme the Main settings form.
 */

/**
 * Theme the Settings form.
 */
function theme_flag_notify_admin_settings($variables) {
  $css = '#flag-notify-settings {font-size: 100%;}
    table th, table td {width: 49%;}
    .description {white-space: normal !important;}
    ';
  drupal_add_css($css, 'inline');

  $output = '';

  $form = $variables['form'];
  $flag = $form['#flag'];

  $rows = array();

  $style = 'vertical-align: top; white-space: normal';

  $rows[] = array(
    array('data' => drupal_render($form['flag_notify_flag_roles_' . $flag->name]), 'style' => $style),
    array('data' => drupal_render($form['flag_notify_flag_group_' . $flag->name]), 'style' => $style),
    );

  $output .= theme('table', array(
    'rows' => $rows,
    'attributes' => array('id' => 'flag-notify-admin-settings'),
    ));

  $output .= drupal_render_children($form);
  return $output;
}
