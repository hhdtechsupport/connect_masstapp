<?php
/**
 * @file
 * profile_stuff.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function profile_stuff_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_profile2_type().
 */
function profile_stuff_default_profile2_type() {
  $items = array();
  $items['demographics'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "demographics",
    "label" : "Demographic Information",
    "weight" : "-2",
    "data" : { "registration" : 1, "use_page" : 0 },
    "rdf_mapping" : []
  }');
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "main",
    "label" : "Contact Information",
    "weight" : "0",
    "data" : { "registration" : 1, "use_page" : 0 },
    "rdf_mapping" : []
  }');
  return $items;
}
