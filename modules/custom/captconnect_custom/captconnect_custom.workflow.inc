<?php
/**
 * @file
 * Workflow actions for captconnect_custom.
 */

/**
 * Implements hook_workflow_notify().
 *
 * Events may have an Approvers list to override normal workflow
 * notifications. This function will check for them and override
 * the list of email addresses if they are present.
 *
 * @param $op - The operation (columns, users, tokens).
 * @param $args - The arguments for this call.
 *    - may be:
 *      'columns' - the current list of table headings.
 *      'users' - The current list of users.
 *      'node' - The current node for getting groups focus.
 *      'state' - The state the node is moving to.
 *      'tokens' - The list of tokens for emails.
 *
 * @return none - Modify the list by reference.
 */
function captconnect_custom_workflow_notify($op, &$args) {
//  dpm($args, "captconnect_custom_workflow_notify $op");
  switch ($op) {
    case 'users':
      // We only care about Events here.
      $node = $args['node'];
      if ($node->type == 'event') {
        $event = entity_metadata_wrapper('node', $node);

        // Skip if there are no approvers.
        if ($event->field_no_approver->value() == FALSE) {
          $approver_list = array();
          foreach ($event->field_approver->value() as $account) {
            $approver_list[$account->uid] = $account;
          }
          if (!empty($approver_list)) {
            // We have approvers listed in the node, so change the email list.
            dpm($approver_list, 'approver list');
            $args['users'] = $approver_list;
          }
        }
      }

      break;
  }
}
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
function captconnect_custom_workflow($op, $old_state, $new_state, $node, $force = FALSE) {
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

          // Let admins and site maintainers do it.
          if (user_access('administer group')) {
            return TRUE;
          }

          // Get the node's team group value(s).
          $groups = field_get_items('node', $node, 'og_group_ref');

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
