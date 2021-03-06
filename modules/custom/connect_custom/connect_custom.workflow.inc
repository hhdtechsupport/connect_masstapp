<?php
/**
 * @file
 * Workflow actions for captconnect_custom.
 */

/**
 * Implements hook_workflow().
 *
 * @param $op
 *   The current workflow operation: 'transition permitted', 'transition pre' or 'transition post'.
 * @param $old_state
 *   The state ID of the current state.
 * @param $new_state
 *   The state ID of the new state.
 * @param $node
 *   The node whose workflow state is changing.
 * @param $force
 *   The caller indicated that the transition should be forced. (bool).
 *   This is only available on the "pre" and "post" calls.
 */
function connect_custom_workflow($op, $old_state, $new_state, $node, $force = FALSE) {
  global $user;
  switch ($op) {
    case 'transition permitted':
      switch ($node->type) {
        case 'event':
        case 'portal':
          // Don't show the current state.
          if ($old_state == $new_state) {
            return FALSE;
          }

          // If the node is new, it may not be totally complete.
          // We'll just wait for the next time through.
          // Strangely, even if is_new is FALSE, og_group_ref is empty.
          // This is only if is_new is set at all.
          if (isset($node->is_new) /*&& $node->is_new*/) {
            return TRUE;
          }

          if ($node->type == 'event'
          && in_array($new_state, array_filter(variable_get('captconnect_custom_check_fields_states', array())))) {
            // We want to see if some event fields are filled in, and alert if not.
            $fields_to_check = array_filter(variable_get('captconnect_custom_check_fields', array()));

            $event = entity_metadata_wrapper('node', $node);
            $missing_a_field = FALSE;
            foreach ($fields_to_check as $field_name) {
              $value = $event->$field_name->value();
              if (empty($value)) {
                $info = field_info_instance('node', $field_name, 'event');
                drupal_set_message(t('"@field" is empty.',
                  array('@field' => $info['label'])),
                  'error', FALSE);
                $missing_a_field = TRUE;
              }
            }

            // If something is missing, prevent the transition.
            if ($missing_a_field) {
              drupal_set_message(variable_get('captconnect_custom_check_fields_msg',
                'This needs to be corrected in order to publish this Event.'),
                'error', FALSE);
              // Let admins and site maintainers do it anyway.
              return user_access('administer group');
            }
          }

          // Get the node's team group value(s).
          $groups = field_get_items('node', $node, 'og_group_ref');

          if (empty($groups)) {
            $types = node_type_get_names();
            $msg = variable_get('captconnect_custom_missing_group_msg',
              'This @type needs to belong to a group.');
            drupal_set_message(t($msg, array('@type' => $types[$node->type])), 'error', FALSE);
            return FALSE;
          }
          else {
            foreach ($groups as $group) {
              // See if the current user is a member of the node's group.
              if (og_is_member('node', $group['target_id'], 'user')) {
                return TRUE;
              }
            }
            // Nope the user is not in any of the node's groups.
            return FALSE;
          }
      }
    }
}
