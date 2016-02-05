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
  dpm($args, "captconnect_custom_workflow_notify $op");
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
