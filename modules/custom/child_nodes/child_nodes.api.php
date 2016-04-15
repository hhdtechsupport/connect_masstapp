<?php
/**
 * Implements hook_child_nodes_button().
 *
 * Decide whether or not to show the "Create xxx" button.
 */
function hook_child_nodes_button($node, $child_type) {
  // Get the node's group value.
  $gid = array_pop(array_pop(field_get_items('node', $node, 'og_group_ref')));

  // See if the current user is a member of the node's group.
  return og_is_member($gid, 'user');
}