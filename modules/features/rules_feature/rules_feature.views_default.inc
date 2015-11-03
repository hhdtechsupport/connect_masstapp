<?php
/**
 * @file
 * rules_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function rules_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'views_rules';
  $view->description = 'This view is used to create lists of events, date instances, and other content that can be iterated over in Rules.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Views rules';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_date_instance_target_id']['id'] = 'field_date_instance_target_id';
  $handler->display->display_options['relationships']['field_date_instance_target_id']['table'] = 'field_data_field_date_instance';
  $handler->display->display_options['relationships']['field_date_instance_target_id']['field'] = 'field_date_instance_target_id';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_date_instance_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'event' => 'event',
  );

  /* Display: Event parent */
  $handler = $view->new_display('views_rules', 'Event parent', 'views_rules_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid_instance',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'nid_event',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
  );

  /* Display: Event registration */
  $handler = $view->new_display('views_rules', 'Event registration', 'views_rules_2');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_event_registration_node']['id'] = 'reverse_field_event_registration_node';
  $handler->display->display_options['relationships']['reverse_field_event_registration_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_event_registration_node']['field'] = 'reverse_field_event_registration_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_event_target_id']['id'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['table'] = 'field_data_field_related_event';
  $handler->display->display_options['relationships']['field_related_event_target_id']['field'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['relationship'] = 'reverse_field_event_registration_node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_related_event_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'notification' => 'notification',
  );
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid_event',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'node',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
    'field_email_body' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Email body',
      'name' => 'field_email_body',
    ),
  );

  /* Display: Event cancellation */
  $handler = $view->new_display('views_rules', 'Event cancellation', 'views_rules_3');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_event_cancellation_node']['id'] = 'reverse_field_event_cancellation_node';
  $handler->display->display_options['relationships']['reverse_field_event_cancellation_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_event_cancellation_node']['field'] = 'reverse_field_event_cancellation_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_event_target_id']['id'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['table'] = 'field_data_field_related_event';
  $handler->display->display_options['relationships']['field_related_event_target_id']['field'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['relationship'] = 'reverse_field_event_cancellation_node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_related_event_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'notification' => 'notification',
  );
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid_event',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'node',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
    'field_email_body' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Email body',
      'name' => 'field_email_body',
    ),
  );

  /* Display: Event reminder */
  $handler = $view->new_display('views_rules', 'Event reminder', 'views_rules_4');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_event_reminder_node']['id'] = 'reverse_field_event_reminder_node';
  $handler->display->display_options['relationships']['reverse_field_event_reminder_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_event_reminder_node']['field'] = 'reverse_field_event_reminder_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_event_target_id']['id'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['table'] = 'field_data_field_related_event';
  $handler->display->display_options['relationships']['field_related_event_target_id']['field'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['relationship'] = 'reverse_field_event_reminder_node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_related_event_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'notification' => 'notification',
  );
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid_event',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'node',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
    'field_email_body' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Email body',
      'name' => 'field_email_body',
    ),
  );

  /* Display: Event followup */
  $handler = $view->new_display('views_rules', 'Event followup', 'views_rules_5');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_event_followup_node']['id'] = 'reverse_field_event_followup_node';
  $handler->display->display_options['relationships']['reverse_field_event_followup_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_event_followup_node']['field'] = 'reverse_field_event_followup_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_event_target_id']['id'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['table'] = 'field_data_field_related_event';
  $handler->display->display_options['relationships']['field_related_event_target_id']['field'] = 'field_related_event_target_id';
  $handler->display->display_options['relationships']['field_related_event_target_id']['relationship'] = 'reverse_field_event_followup_node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_event_registration_confirm_target_id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_related_event_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'notification' => 'notification',
  );
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid_event',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'node',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
    'field_email_body' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Email body',
      'name' => 'field_email_body',
    ),
  );

  /* Display: Date instance (AM) */
  $handler = $view->new_display('views_rules', 'Date instance (AM)', 'views_rules_6');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'instance' => 'instance',
  );
  /* Filter criterion: Content: Date -  start date (field_date) */
  $handler->display->display_options['filters']['field_date_value']['id'] = 'field_date_value';
  $handler->display->display_options['filters']['field_date_value']['table'] = 'field_data_field_date';
  $handler->display->display_options['filters']['field_date_value']['field'] = 'field_date_value';
  $handler->display->display_options['filters']['field_date_value']['default_date'] = 'today';
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'instance',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
  );

  /* Display: Date instance registrations */
  $handler = $view->new_display('views_rules', 'Date instance registrations', 'views_rules_7');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Flags: registration */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'registration';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Flags: User uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'flagging';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'flag_content_rel';
  /* Field: Field: First name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['relationship'] = 'flag_content_rel';
  /* Field: Field: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'instance' => 'instance',
  );
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => 'Content: Nid',
      'name' => 'nid',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'uid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'user',
      'label' => '(flag) User uid',
      'name' => 'uid',
    ),
    'field_first_name' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => '(flag) First name',
      'name' => 'field_first_name',
    ),
    'field_last_name' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => '(flag) Last name',
      'name' => 'field_last_name',
    ),
  );

  /* Display: Date instance (reminder) */
  $handler = $view->new_display('views_rules', 'Date instance (reminder)', 'views_rules_10');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_events_target_id']['id'] = 'field_related_events_target_id';
  $handler->display->display_options['relationships']['field_related_events_target_id']['table'] = 'field_data_field_related_events';
  $handler->display->display_options['relationships']['field_related_events_target_id']['field'] = 'field_related_events_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['id'] = 'field_related_notifications_target_id';
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['table'] = 'field_data_field_related_notifications';
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['field'] = 'field_related_notifications_target_id';
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['relationship'] = 'field_related_events_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_event_reminder_target_id']['id'] = 'field_event_reminder_target_id';
  $handler->display->display_options['relationships']['field_event_reminder_target_id']['table'] = 'field_data_field_event_reminder';
  $handler->display->display_options['relationships']['field_event_reminder_target_id']['field'] = 'field_event_reminder_target_id';
  $handler->display->display_options['relationships']['field_event_reminder_target_id']['relationship'] = 'field_related_notifications_target_id';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'field_event_reminder_target_id';
  $handler->display->display_options['fields']['nid_1']['label'] = 'Nid_1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'instance' => 'instance',
  );
  /* Filter criterion: Global: PHP */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = '$nid = $row->nid;
$node = node_load($nid);
$date1 = strtotime($node->field_date[\'und\'][0][\'value2\']);
$date2 = time();
$datediff = floor(($date1 - $date2)/(60*60*24));

$nid_1 = $row->nid_1;
$node_1 = node_load($nid_1);
$days = $node_1->field_days_before_event_to_send[\'und\'][0][\'value\'];

if($datediff != $days) {
return TRUE;
}';
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'instance',
    ),
    'nid_1' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => '(Content entity referenced from field_event_followup) Nid',
      'name' => 'nid_1',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
    'php' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'PHP',
      'name' => 'php',
    ),
    'php_1' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'PHP',
      'name' => 'php_1',
    ),
    'php_2' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'PHP',
      'name' => 'php_2',
    ),
  );

  /* Display: Date instance (followup) */
  $handler = $view->new_display('views_rules', 'Date instance (followup)', 'views_rules_9');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_events_target_id']['id'] = 'field_related_events_target_id';
  $handler->display->display_options['relationships']['field_related_events_target_id']['table'] = 'field_data_field_related_events';
  $handler->display->display_options['relationships']['field_related_events_target_id']['field'] = 'field_related_events_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['id'] = 'field_related_notifications_target_id';
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['table'] = 'field_data_field_related_notifications';
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['field'] = 'field_related_notifications_target_id';
  $handler->display->display_options['relationships']['field_related_notifications_target_id']['relationship'] = 'field_related_events_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_event_followup_target_id']['id'] = 'field_event_followup_target_id';
  $handler->display->display_options['relationships']['field_event_followup_target_id']['table'] = 'field_data_field_event_followup';
  $handler->display->display_options['relationships']['field_event_followup_target_id']['field'] = 'field_event_followup_target_id';
  $handler->display->display_options['relationships']['field_event_followup_target_id']['relationship'] = 'field_related_notifications_target_id';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'field_event_followup_target_id';
  $handler->display->display_options['fields']['nid_1']['label'] = 'Nid_1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'instance' => 'instance',
  );
  /* Filter criterion: Global: PHP */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = '$nid = $row->nid;
$node = node_load($nid);
$date1 = strtotime($node->field_date[\'und\'][0][\'value2\']);
$date2 = time();
$datediff = floor(($date2 - $date1)/(60*60*24));

$nid_1 = $row->nid_1;
$node_1 = node_load($nid_1);
$days = $node_1->field_days_after_event_to_send[\'und\'][0][\'value\'];

if($datediff != $days) {
return TRUE;
}';
  $handler->display->display_options['rules_parameter'] = array(
    'nid' => array(
      'enabled' => 1,
      'type' => 'integer',
      'label' => '(Content entity referenced from field_date_instance) Content: Nid',
      'name' => 'nid',
    ),
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'node',
      'label' => 'Content: Nid',
      'name' => 'instance',
    ),
    'nid_1' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => '(Content entity referenced from field_event_followup) Nid',
      'name' => 'nid_1',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
    'php' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'PHP',
      'name' => 'php',
    ),
    'php_1' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'PHP',
      'name' => 'php_1',
    ),
    'php_2' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'PHP',
      'name' => 'php_2',
    ),
  );

  /* Display: All OG groups */
  $handler = $view->new_display('views_rules', 'All OG groups', 'views_rules_8');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'resource_team' => 'resource_team',
  );
  $handler->display->display_options['rules_variables'] = array(
    'nid' => array(
      'enabled' => 1,
      'rendered' => 0,
      'type' => 'integer',
      'label' => 'Content: Nid',
      'name' => 'nid',
    ),
    'title' => array(
      'enabled' => 0,
      'rendered' => 0,
      'type' => '',
      'label' => 'Content: Title',
      'name' => 'title',
    ),
  );
  $export['views_rules'] = $view;

  return $export;
}
