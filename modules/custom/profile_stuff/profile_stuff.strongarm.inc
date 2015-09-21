<?php
/**
 * @file
 * profile_stuff.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function profile_stuff_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'realname_pattern';
  $strongarm->value = '[user:profile-main:field-first-name] [user:profile-main:field-last-name]';
  $export['realname_pattern'] = $strongarm;

  return $export;
}
