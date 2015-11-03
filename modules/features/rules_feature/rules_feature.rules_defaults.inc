<?php
/**
 * @file
 * rules_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function rules_feature_default_rules_configuration() {
  $items = array();
  $items['rules_assign_og_based_on_state_area_selected_if_not_capt_staff'] = entity_import('rules_config', '{ "rules_assign_og_based_on_state_area_selected_if_not_capt_staff" : {
      "LABEL" : "Assign OG based on state\\/area selected if not CAPT staff",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "views_rules", "og" ],
      "ON" : { "user_insert" : [], "user_update" : [] },
      "IF" : [
        { "AND" : [
            { "NOT data_is" : { "data" : [ "account:field-role" ], "value" : "111" } },
            { "user_has_role" : {
                "account" : [ "account" ],
                "roles" : { "value" : { "3" : "3", "4" : "4", "5" : "5", "6" : "6" } },
                "operation" : "OR"
              }
            }
          ]
        }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : {
              "type" : "taxonomy_term",
              "id" : [ "account:field-state-or-jurisdiction:parent:0:tid" ]
            },
            "PROVIDE" : { "entity_fetched" : { "region_fetched" : "Fetched Region" } }
          }
        },
        { "entity_query" : {
            "USING" : {
              "type" : "node",
              "property" : "title",
              "value" : [ "region-fetched:name" ],
              "limit" : "1"
            },
            "PROVIDE" : { "entity_fetched" : { "fetched_group" : "Group Fetched" } }
          }
        },
        { "VIEW LOOP" : {
            "VIEW" : "views_rules",
            "DISPLAY" : "views_rules_8",
            "ROW VARIABLES" : { "nid" : { "nid" : "Content: Nid" } },
            "DO" : [
              { "entity_fetch" : {
                  "USING" : { "type" : "node", "id" : [ "nid" ] },
                  "PROVIDE" : { "entity_fetched" : { "group_fetched_2" : "Fetched group 2" } }
                }
              },
              { "og_unsubscribe_user" : { "user" : [ "account" ], "group" : [ "group-fetched-2" ] } }
            ]
          }
        },
        { "og_subcribe_user" : { "user" : [ "account" ], "group" : [ "fetched-group:0" ] } }
      ]
    }
  }');
  $items['rules_delete_event_notifications_when_event_deleted'] = entity_import('rules_config', '{ "rules_delete_event_notifications_when_event_deleted" : {
      "LABEL" : "Delete event notifications when event deleted",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_delete--event" : { "bundle" : "event" } },
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "node:field-related-notifications:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
          }
        },
        { "entity_delete" : { "data" : [ "entity-fetched" ] } }
      ]
    }
  }');
  $items['rules_event_cancelation_remove_reg_flag_and_notify'] = entity_import('rules_config', '{ "rules_event_cancelation_remove_reg_flag_and_notify" : {
      "LABEL" : "Event cancelation - remove reg flag and notify",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules_conditional", "views_rules", "flag", "rules", "php", "mimemail" ],
      "ON" : { "flag_unflagged_registration" : [] },
      "DO" : [
        { "CONDITIONAL" : [
            {
              "IF" : { "entity_is_of_bundle" : {
                  "entity" : [ "flagged-node" ],
                  "type" : "node",
                  "bundle" : { "value" : { "instance" : "instance" } }
                }
              },
              "DO" : [
                { "CONDITIONAL" : [
                    {
                      "IF" : { "entity_is_of_bundle" : {
                          "entity" : [ "flagging" ],
                          "type" : "flagging",
                          "bundle" : { "value" : { "registration" : "registration" } }
                        }
                      },
                      "DO" : [
                        { "VIEW LOOP" : {
                            "VIEW" : "views_rules",
                            "DISPLAY" : "views_rules_1",
                            "USING" : { "nid_instance" : [ "flagged-node:nid" ] },
                            "ROW VARIABLES" : { "nid_event" : { "nid_event" : "Content: Nid" } },
                            "DO" : [
                              { "flag_unflagnode" : {
                                  "flag" : "participate",
                                  "node" : [ "flagged-node" ],
                                  "flagging_user" : [ "flagging_user" ],
                                  "permission_check" : "1"
                                }
                              },
                              { "VIEW LOOP" : {
                                  "VIEW" : "views_rules",
                                  "DISPLAY" : "views_rules_3",
                                  "USING" : { "nid_event" : [ "nid-event:nid" ] },
                                  "ROW VARIABLES" : { "node" : { "node" : "Content: Nid" } },
                                  "DO" : [
                                    { "CONDITIONAL" : [
                                        {
                                          "IF" : { "entity_is_of_bundle" : {
                                              "entity" : [ "node" ],
                                              "type" : "node",
                                              "bundle" : { "value" : { "notification" : "notification" } }
                                            }
                                          },
                                          "DO" : [
                                            { "CONDITIONAL" : [
                                                {
                                                  "IF" : { "data_is" : { "data" : [ "node:field-prevent-notification" ], "value" : "0" } },
                                                  "DO" : [
                                                    { "CONDITIONAL" : [
                                                        {
                                                          "IF" : { "data_is" : { "data" : [ "flagging-user" ], "value" : [ "site:current-user" ] } },
                                                          "DO" : [
                                                            { "mimemail" : {
                                                                "key" : "[site:current-date]",
                                                                "to" : [ "flagging-user:mail" ],
                                                                "subject" : "\\u003C?php print $node-\\u003Efield_email_subject[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E",
                                                                "body" : "\\u003Ctable cellpadding=\\u00220\\u0022 cellspacing=\\u00220\\u0022 border=\\u00220\\u0022 width=\\u0022100%\\u0022 class=\\u0022hide-ics\\u0022\\u003E\\r\\n  \\u003Ctr\\u003E\\r\\n    \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/pattern.png\\u0022 valign=\\u0022top\\u0022 bgcolor=\\u0022#E3E3DF\\u0022\\u003E\\r\\n      \\u003Cdiv\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022header\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022logos center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd width=\\u0022351\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/capt_logo.png\\u0022 width=\\u0022350\\u0022 height=\\u002280\\u0022 alt=\\u0022CAPT - SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                  \\u003Ctd width=\\u0022250\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/samhsa_logo.png\\u0022 width=\\u0022250\\u0022 height=\\u002280\\u0022 alt=\\u0022SAMHSA - U.S. Substance Abuse and Mental Health Services Administration\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022banner center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/banner.png\\u0022 bgcolor=\\u0022#567583\\u0022 width=\\u0022600\\u0022 height=\\u0022134\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n              \\u003Cdiv\\u003E\\r\\n  \\r\\n                \\u003C?php\\r\\n                  if (!empty($nid_event-\\u003Efield_banner_text)) {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $nid_event-\\u003Efield_banner_text[\\u0027und\\u0027][0][\\u0027value\\u0027] . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else if (!empty($nid_event-\\u003Efield_category)) {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $term-\\u003Ename . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 36px; margin-top: 32px;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 15px; text-transform: uppercase;\\u0022\\u003EYour access point for all CAPT virtual events\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                ?\\u003E\\r\\n\\r\\n              \\u003C\\/div\\u003E\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd bgcolor=\\u0022#FFFFFF\\u0022\\u003E\\r\\n\\r\\n              \\u003C?php print $node-\\u003Efield_email_body[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022footer\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022mailing center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd\\u003E\\r\\n                    \\u003Cp\\u003EMailing Address: SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u003Cbr\\u003EEducation Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313\\u003C\\/p\\u003E\\r\\n                    \\u003Cp\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003ETerms\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EPrivacy\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EUnsubscribe\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n                    \\u003Cp id=\\u0022date\\u0022\\u003E[site:current-date]\\u003C\\/p\\u003E \\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n      \\u003C\\/div\\u003E\\r\\n    \\u003C\\/td\\u003E\\r\\n  \\u003C\\/tr\\u003E\\r\\n\\u003C\\/table\\u003E",
                                                                "language" : [ "" ]
                                                              }
                                                            }
                                                          ]
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ]
                                            }
                                          ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              }
                            ]
                          }
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        }
      ]
    }
  }');
  $items['rules_event_followup_send_in_am'] = entity_import('rules_config', '{ "rules_event_followup_send_in_am" : {
      "LABEL" : "Event followup - send in AM",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [
        "views_rules",
        "rules_conditional",
        "rules",
        "php",
        "mimemail",
        "rules_scheduler"
      ],
      "DO" : [
        { "VIEW LOOP" : {
            "VIEW" : "views_rules",
            "DISPLAY" : "views_rules_9",
            "ROW VARIABLES" : { "instance" : { "instance" : "Content: Nid" } },
            "DO" : [
              { "VIEW LOOP" : {
                  "VIEW" : "views_rules",
                  "DISPLAY" : "views_rules_7",
                  "USING" : { "nid" : [ "instance:nid" ] },
                  "ROW VARIABLES" : { "uid" : { "uid" : "(flag) User uid" } },
                  "DO" : [
                    { "VIEW LOOP" : {
                        "VIEW" : "views_rules",
                        "DISPLAY" : "views_rules_1",
                        "USING" : { "nid_instance" : [ "instance:nid" ] },
                        "ROW VARIABLES" : { "nid_event" : { "nid_event" : "Content: Nid" } },
                        "DO" : [
                          { "VIEW LOOP" : {
                              "VIEW" : "views_rules",
                              "DISPLAY" : "views_rules_5",
                              "USING" : { "nid_event" : [ "nid-event:nid" ] },
                              "ROW VARIABLES" : { "node" : { "node" : "Content: Nid" } },
                              "DO" : [
                                { "CONDITIONAL" : [
                                    {
                                      "IF" : { "entity_is_of_bundle" : {
                                          "entity" : [ "node" ],
                                          "type" : "node",
                                          "bundle" : { "value" : { "notification" : "notification" } }
                                        }
                                      },
                                      "DO" : [
                                        { "CONDITIONAL" : [
                                            {
                                              "IF" : { "data_is" : { "data" : [ "node:field-prevent-notification" ], "value" : "0" } },
                                              "DO" : [
                                                { "CONDITIONAL" : [
                                                    {
                                                      "IF" : { "entity_is_of_bundle" : {
                                                          "entity" : [ "instance" ],
                                                          "type" : "node",
                                                          "bundle" : { "value" : { "instance" : "instance" } }
                                                        }
                                                      },
                                                      "DO" : [
                                                        { "CONDITIONAL" : [
                                                            {
                                                              "IF" : { "data_is_empty" : { "data" : [ "instance:field-related-material" ] } },
                                                              "DO" : [
                                                                { "CONDITIONAL" : [
                                                                    {
                                                                      "IF" : { "data_is_empty" : { "data" : [ "node:field-use-a-default-template" ] } },
                                                                      "DO" : [
                                                                        { "mimemail" : {
                                                                            "key" : "[site:current-date]",
                                                                            "to" : [ "uid:mail" ],
                                                                            "subject" : "\\u003C?php print $node-\\u003Efield_email_subject[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E",
                                                                            "body" : "\\u003Ctable cellpadding=\\u00220\\u0022 cellspacing=\\u00220\\u0022 border=\\u00220\\u0022 width=\\u0022100%\\u0022 class=\\u0022hide-ics\\u0022\\u003E\\r\\n  \\u003Ctr\\u003E\\r\\n    \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/pattern.png\\u0022 valign=\\u0022top\\u0022 bgcolor=\\u0022#E3E3DF\\u0022\\u003E\\r\\n      \\u003Cdiv\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022header\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022logos center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd width=\\u0022351\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/capt_logo.png\\u0022 width=\\u0022350\\u0022 height=\\u002280\\u0022 alt=\\u0022CAPT - SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                  \\u003Ctd width=\\u0022250\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/samhsa_logo.png\\u0022 width=\\u0022250\\u0022 height=\\u002280\\u0022 alt=\\u0022SAMHSA - U.S. Substance Abuse and Mental Health Services Administration\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022banner center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/banner.png\\u0022 bgcolor=\\u0022#567583\\u0022 width=\\u0022600\\u0022 height=\\u0022134\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n              \\u003Cdiv\\u003E\\r\\n  \\r\\n                \\u003C?php\\r\\n                  if (!empty($nid_event-\\u003Efield_banner_text)) {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $nid_event-\\u003Efield_banner_text[\\u0027und\\u0027][0][\\u0027value\\u0027] . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else if (!empty($nid_event-\\u003Efield_category)) {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $term-\\u003Ename . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 36px; margin-top: 32px;\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 15px; text-transform: uppercase;\\u0022\\u003EYour access point for all CAPT virtual events\\u003C\\/div\\u003E\\u003Cdiv\\u003E\\u0027 . $term . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                ?\\u003E\\r\\n\\r\\n              \\u003C\\/div\\u003E\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd bgcolor=\\u0022#FFFFFF\\u0022\\u003E\\r\\n\\r\\n              \\u003C?php print $node-\\u003Efield_email_body[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022footer\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022mailing center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd\\u003E\\r\\n                    \\u003Cp\\u003EMailing Address: SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u003Cbr\\u003EEducation Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313\\u003C\\/p\\u003E\\r\\n                    \\u003Cp\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003ETerms\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EPrivacy\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EUnsubscribe\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n                    \\u003Cp id=\\u0022date\\u0022\\u003E[site:current-date]\\u003C\\/p\\u003E \\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n      \\u003C\\/div\\u003E\\r\\n    \\u003C\\/td\\u003E\\r\\n  \\u003C\\/tr\\u003E\\r\\n\\u003C\\/table\\u003E",
                                                                            "language" : [ "" ]
                                                                          }
                                                                        }
                                                                      ]
                                                                    }
                                                                  ]
                                                                }
                                                              ]
                                                            },
                                                            { "ELSE" : [
                                                                { "mimemail" : {
                                                                    "key" : "[site:current-date]",
                                                                    "to" : [ "uid:mail" ],
                                                                    "subject" : "\\u003C?php print $node-\\u003Efield_email_subject[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E",
                                                                    "body" : "\\u003Ctable cellpadding=\\u00220\\u0022 cellspacing=\\u00220\\u0022 border=\\u00220\\u0022 width=\\u0022100%\\u0022 class=\\u0022hide-ics\\u0022\\u003E\\r\\n  \\u003Ctr\\u003E\\r\\n    \\u003Ctd background=\\u0022http:\\/\\/dev.captconnect.edc.org\\/sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/pattern.png\\u0022 valign=\\u0022top\\u0022 bgcolor=\\u0022#E3E3DF\\u0022\\u003E\\r\\n      \\u003Cdiv\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022header\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022logos center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd width=\\u0022351\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022http:\\/\\/dev.captconnect.edc.org\\/sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/capt_logo.png\\u0022 width=\\u0022350\\u0022 height=\\u002280\\u0022 alt=\\u0022CAPT - SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                  \\u003Ctd width=\\u0022250\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022http:\\/\\/dev.captconnect.edc.org\\/sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/samhsa_logo.png\\u0022 width=\\u0022250\\u0022 height=\\u002280\\u0022 alt=\\u0022SAMHSA - U.S. Substance Abuse and Mental Health Services Administration\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022http:\\/\\/dev.captconnect.edc.org\\/sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022banner center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd background=\\u0022http:\\/\\/dev.captconnect.edc.org\\/sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/banner.png\\u0022 bgcolor=\\u0022#567583\\u0022 width=\\u0022600\\u0022 height=\\u0022134\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n              \\u003Cdiv\\u003E\\r\\n  \\r\\n                \\u003C?php\\r\\n                  if (!empty($nid_event-\\u003Efield_banner_text)) {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $nid_event-\\u003Efield_banner_text[\\u0027und\\u0027][0][\\u0027value\\u0027] . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else if (!empty($nid_event-\\u003Efield_category)) {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $term-\\u003Ename . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 36px; margin-top: 32px;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 15px; text-transform: uppercase;\\u0022\\u003EYour access point for all CAPT virtual events\\u003C\\/div\\u003E\\u003Cdiv\\u003E\\u0027 . $term . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                ?\\u003E\\r\\n\\r\\n              \\u003C\\/div\\u003E\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd bgcolor=\\u0022#FFFFFF\\u0022\\u003E\\r\\n\\r\\n              \\u003C?php print $node-\\u003Efield_email_body[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022footer\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022http:\\/\\/dev.captconnect.edc.org\\/sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022mailing center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd\\u003E\\r\\n                    \\u003Cp\\u003EMailing Address: SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u003Cbr\\u003EEducation Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313\\u003C\\/p\\u003E\\r\\n                    \\u003Cp\\u003E\\u003Ca href=\\u0022http:\\/\\/dev.captconnect.edc.org\\u0022\\u003ETerms\\u003C\\/a\\u003E | \\u003Ca href=\\u0022http:\\/\\/dev.captconnect.edc.org\\u0022\\u003EPrivacy\\u003C\\/a\\u003E | \\u003Ca href=\\u0022http:\\/\\/dev.captconnect.edc.org\\u0022\\u003EUnsubscribe\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n                    \\u003Cp id=\\u0022date\\u0022\\u003E[site:current-date]\\u003C\\/p\\u003E \\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n      \\u003C\\/div\\u003E\\r\\n    \\u003C\\/td\\u003E\\r\\n  \\u003C\\/tr\\u003E\\r\\n\\u003C\\/table\\u003E",
                                                                    "language" : [ "" ]
                                                                  }
                                                                }
                                                              ]
                                                            }
                                                          ]
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ]
                                            }
                                          ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              ]
                            }
                          }
                        ]
                      }
                    }
                  ]
                }
              }
            ]
          }
        },
        { "schedule" : {
            "component" : "rules_event_followup_send_in_am",
            "date" : "Tomorrow 6am",
            "identifier" : "1"
          }
        }
      ]
    }
  }');
  $items['rules_event_registration_copy_profile_to_reg_flag_and_notify'] = entity_import('rules_config', '{ "rules_event_registration_copy_profile_to_reg_flag_and_notify" : {
      "LABEL" : "Event registration - copy profile to reg flag and notify",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules_conditional", "rules", "views_rules", "php", "mimemail", "flag" ],
      "ON" : { "flag_flagged_registration" : [] },
      "DO" : [
        { "CONDITIONAL" : [
            {
              "IF" : { "entity_is_of_bundle" : {
                  "entity" : [ "flagged-node" ],
                  "type" : "node",
                  "bundle" : { "value" : { "instance" : "instance" } }
                }
              },
              "DO" : [
                { "CONDITIONAL" : [
                    {
                      "IF" : { "entity_is_of_bundle" : {
                          "entity" : [ "flagging" ],
                          "type" : "flagging",
                          "bundle" : { "value" : { "registration" : "registration" } }
                        }
                      },
                      "DO" : [
                        { "data_set" : {
                            "data" : [ "flagging:field-first-name" ],
                            "value" : [ "flagging-user:field-first-name" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-last-name" ],
                            "value" : [ "flagging-user:field-last-name" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:og-group-ref" ],
                            "value" : [ "flagging-user:og-user-node" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-role-or-title" ],
                            "value" : [ "flagging-user:field-role-or-title" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-role" ],
                            "value" : [ "flagging-user:field-role" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-other-role" ],
                            "value" : [ "flagging-user:field-other-role" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-organization-name" ],
                            "value" : [ "flagging-user:field-organization-name" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-state-or-jurisdiction" ],
                            "value" : [ "flagging-user:field-state-or-jurisdiction" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-organizational-affiliation" ],
                            "value" : [ "flagging-user:field-organizational-affiliation" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-other-affiliation" ],
                            "value" : [ "flagging-user:field-other-affiliation" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-tribal-affiliation" ],
                            "value" : [ "flagging-user:field-tribal-affiliation" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-other-tribe" ],
                            "value" : [ "flagging-user:field-other-tribe" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-hispanic-or-latino" ],
                            "value" : [ "flagging-user:field-hispanic-or-latino" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-race-or-ethnicity" ],
                            "value" : [ "flagging-user:field-race-or-ethnicity" ]
                          }
                        },
                        { "data_set" : {
                            "data" : [ "flagging:field-primary-phone-number" ],
                            "value" : [ "flagging-user:field-primary-phone-number" ]
                          }
                        },
                        { "variable_add" : {
                            "USING" : { "type" : "text" },
                            "PROVIDE" : { "variable_added" : { "ics_class" : "ics_class" } }
                          }
                        },
                        { "CONDITIONAL" : [
                            {
                              "IF" : { "NOT data_is" : {
                                  "data" : [ "flagged-node:field-include-outlook-invitation" ],
                                  "value" : "1"
                                }
                              },
                              "DO" : [ { "data_set" : { "data" : [ "ics-class" ], "value" : "hide-ics" } } ]
                            }
                          ]
                        },
                        { "VIEW LOOP" : {
                            "VIEW" : "views_rules",
                            "DISPLAY" : "views_rules_1",
                            "USING" : { "nid_instance" : [ "flagged-node:nid" ] },
                            "ROW VARIABLES" : { "nid_event" : { "nid_event" : "Content: Nid" } },
                            "DO" : [
                              { "VIEW LOOP" : {
                                  "VIEW" : "views_rules",
                                  "DISPLAY" : "views_rules_2",
                                  "USING" : { "nid_event" : [ "nid-event:nid" ] },
                                  "ROW VARIABLES" : { "node" : { "node" : "Content: Nid" } },
                                  "DO" : [
                                    { "CONDITIONAL" : [
                                        {
                                          "IF" : { "entity_is_of_bundle" : {
                                              "entity" : [ "node" ],
                                              "type" : "node",
                                              "bundle" : { "value" : { "notification" : "notification" } }
                                            }
                                          },
                                          "DO" : [
                                            { "CONDITIONAL" : [
                                                {
                                                  "IF" : { "NOT data_is" : { "data" : [ "node:field-prevent-notification" ], "value" : "1" } },
                                                  "DO" : [
                                                    { "CONDITIONAL" : [
                                                        {
                                                          "IF" : { "data_is" : { "data" : [ "flagging-user" ], "value" : [ "site:current-user" ] } },
                                                          "DO" : [
                                                            { "mimemail" : {
                                                                "key" : "[site:current-date]",
                                                                "to" : [ "flagging-user:mail" ],
                                                                "subject" : "\\u003C?php print $node-\\u003Efield_email_subject[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E",
                                                                "body" : "\\u003Ctable cellpadding=\\u00220\\u0022 cellspacing=\\u00220\\u0022 border=\\u00220\\u0022 width=\\u0022100%\\u0022 class=\\u0022[ics-class:value]\\u0022\\u003E\\r\\n  \\u003Ctr\\u003E\\r\\n    \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/pattern.png\\u0022 valign=\\u0022top\\u0022 bgcolor=\\u0022#E3E3DF\\u0022\\u003E\\r\\n      \\u003Cdiv\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022header\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022logos center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd width=\\u0022351\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/capt_logo.png\\u0022 width=\\u0022350\\u0022 height=\\u002280\\u0022 alt=\\u0022CAPT - SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                  \\u003Ctd width=\\u0022250\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/samhsa_logo.png\\u0022 width=\\u0022250\\u0022 height=\\u002280\\u0022 alt=\\u0022SAMHSA - U.S. Substance Abuse and Mental Health Services Administration\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022banner center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/banner.png\\u0022 bgcolor=\\u0022#567583\\u0022 width=\\u0022600\\u0022 height=\\u0022134\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n              \\u003Cdiv\\u003E\\r\\n  \\r\\n                \\u003C?php\\r\\n                  if (!empty($nid_event-\\u003Efield_banner_text)) {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $nid_event-\\u003Efield_banner_text[\\u0027und\\u0027][0][\\u0027value\\u0027] . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else if (!empty($nid_event-\\u003Efield_category)) {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $term-\\u003Ename . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 36px; margin-top: 32px;\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 15px; text-transform: uppercase;\\u0022\\u003EYour access point for all CAPT virtual events\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                ?\\u003E\\r\\n\\r\\n              \\u003C\\/div\\u003E\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd bgcolor=\\u0022#FFFFFF\\u0022\\u003E\\r\\n\\r\\n              \\u003C?php print $node-\\u003Efield_email_body[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022footer\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022mailing center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd\\u003E\\r\\n                    \\u003Cp\\u003EMailing Address: SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u003Cbr\\u003EEducation Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313\\u003C\\/p\\u003E\\r\\n                    \\u003Cp\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003ETerms\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EPrivacy\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EUnsubscribe\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n                    \\u003Cp id=\\u0022date\\u0022\\u003E[site:current-date]\\u003C\\/p\\u003E \\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n      \\u003C\\/div\\u003E\\r\\n    \\u003C\\/td\\u003E\\r\\n  \\u003C\\/tr\\u003E\\r\\n\\u003C\\/table\\u003E",
                                                                "language" : [ "" ]
                                                              }
                                                            }
                                                          ]
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ]
                                            }
                                          ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              },
                              { "VIEW LOOP" : {
                                  "VIEW" : "views_rules",
                                  "DISPLAY" : "views_rules_4",
                                  "USING" : { "nid_event" : [ "nid-event:nid" ] },
                                  "ROW VARIABLES" : { "node" : { "node" : "Content: Nid" } },
                                  "DO" : [
                                    { "CONDITIONAL" : [
                                        {
                                          "IF" : { "entity_is_of_bundle" : {
                                              "entity" : [ "node" ],
                                              "type" : "node",
                                              "bundle" : { "value" : { "notification" : "notification" } }
                                            }
                                          },
                                          "DO" : [
                                            { "CONDITIONAL" : [
                                                {
                                                  "IF" : { "NOT data_is" : { "data" : [ "node:field-prevent-notification" ], "value" : "1" } },
                                                  "DO" : [
                                                    { "CONDITIONAL" : [
                                                        {
                                                          "IF" : { "php_eval" : { "code" : "$date1 = strtotime($flagged_node-\\u003Efield_date[\\u0027und\\u0027][0][\\u0027value2\\u0027]);\\r\\n$date2 = time();\\r\\n$datediff = floor(($date1 - $date2)\\/86400);\\r\\n\\r\\n$days = $node-\\u003Efield_days_before_event_to_send[\\u0027und\\u0027][0][\\u0027value\\u0027];\\r\\n\\r\\nif (($datediff \\u003C= $days) \\u0026\\u0026 ($datediff \\u003E= 0)) {\\r\\n  return TRUE;\\r\\n}" } },
                                                          "DO" : [
                                                            { "entity_fetch" : {
                                                                "USING" : { "type" : "node", "id" : [ "flagged-node:nid" ] },
                                                                "PROVIDE" : { "entity_fetched" : { "instance" : "Fetched entity" } }
                                                              }
                                                            },
                                                            { "mimemail" : {
                                                                "key" : "[site:current-date]",
                                                                "to" : [ "flagging-user:mail" ],
                                                                "subject" : "\\u003C?php print $node-\\u003Efield_email_subject[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E",
                                                                "body" : "\\u003Ctable cellpadding=\\u00220\\u0022 cellspacing=\\u00220\\u0022 border=\\u00220\\u0022 width=\\u0022100%\\u0022 class=\\u0022[ics-class:value]\\u0022\\u003E\\r\\n  \\u003Ctr\\u003E\\r\\n    \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/pattern.png\\u0022 valign=\\u0022top\\u0022 bgcolor=\\u0022#E3E3DF\\u0022\\u003E\\r\\n      \\u003Cdiv\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022header\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022logos center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd width=\\u0022351\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/capt_logo.png\\u0022 width=\\u0022350\\u0022 height=\\u002280\\u0022 alt=\\u0022CAPT - SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                  \\u003Ctd width=\\u0022250\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/samhsa_logo.png\\u0022 width=\\u0022250\\u0022 height=\\u002280\\u0022 alt=\\u0022SAMHSA - U.S. Substance Abuse and Mental Health Services Administration\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022banner center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/banner.png\\u0022 bgcolor=\\u0022#567583\\u0022 width=\\u0022600\\u0022 height=\\u0022134\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n              \\u003Cdiv\\u003E\\r\\n  \\r\\n                \\u003C?php\\r\\n                  if (!empty($nid_event-\\u003Efield_banner_text)) {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $nid_event-\\u003Efield_banner_text[\\u0027und\\u0027][0][\\u0027value\\u0027] . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else if (!empty($nid_event-\\u003Efield_category)) {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $term-\\u003Ename . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 36px; margin-top: 32px;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 15px; text-transform: uppercase;\\u0022\\u003EYour access point for all CAPT virtual events\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                ?\\u003E\\r\\n\\r\\n              \\u003C\\/div\\u003E\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd bgcolor=\\u0022#FFFFFF\\u0022\\u003E\\r\\n\\r\\n              \\u003C?php print $node-\\u003Efield_email_body[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022footer\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022mailing center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd\\u003E\\r\\n                    \\u003Cp\\u003EMailing Address: SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u003Cbr\\u003EEducation Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313\\u003C\\/p\\u003E\\r\\n                    \\u003Cp\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003ETerms\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EPrivacy\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EUnsubscribe\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n                    \\u003Cp id=\\u0022date\\u0022\\u003E[site:current-date]\\u003C\\/p\\u003E \\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n      \\u003C\\/div\\u003E\\r\\n    \\u003C\\/td\\u003E\\r\\n  \\u003C\\/tr\\u003E\\r\\n\\u003C\\/table\\u003E",
                                                                "language" : [ "" ]
                                                              }
                                                            }
                                                          ]
                                                        }
                                                      ]
                                                    }
                                                  ]
                                                }
                                              ]
                                            }
                                          ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              }
                            ]
                          }
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        }
      ]
    }
  }');
  $items['rules_event_reminder_send_in_am'] = entity_import('rules_config', '{ "rules_event_reminder_send_in_am" : {
      "LABEL" : "Event reminder - send in AM",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [
        "views_rules",
        "rules_conditional",
        "rules",
        "php",
        "mimemail",
        "rules_scheduler"
      ],
      "DO" : [
        { "VIEW LOOP" : {
            "VIEW" : "views_rules",
            "DISPLAY" : "views_rules_10",
            "ROW VARIABLES" : { "instance" : { "instance" : "Content: Nid" } },
            "DO" : [
              { "VIEW LOOP" : {
                  "VIEW" : "views_rules",
                  "DISPLAY" : "views_rules_7",
                  "USING" : { "nid" : [ "instance:nid" ] },
                  "ROW VARIABLES" : { "uid" : { "uid" : "(flag) User uid" } },
                  "DO" : [
                    { "VIEW LOOP" : {
                        "VIEW" : "views_rules",
                        "DISPLAY" : "views_rules_1",
                        "USING" : { "nid_instance" : [ "instance:nid" ] },
                        "ROW VARIABLES" : { "nid_event" : { "nid_event" : "Content: Nid" } },
                        "DO" : [
                          { "VIEW LOOP" : {
                              "VIEW" : "views_rules",
                              "DISPLAY" : "views_rules_4",
                              "USING" : { "nid_event" : [ "nid-event:nid" ] },
                              "ROW VARIABLES" : { "node" : { "node" : "Content: Nid" } },
                              "DO" : [
                                { "CONDITIONAL" : [
                                    {
                                      "IF" : { "entity_is_of_bundle" : {
                                          "entity" : [ "node" ],
                                          "type" : "node",
                                          "bundle" : { "value" : { "notification" : "notification" } }
                                        }
                                      },
                                      "DO" : [
                                        { "CONDITIONAL" : [
                                            {
                                              "IF" : { "data_is" : { "data" : [ "node:field-prevent-notification" ], "value" : "0" } },
                                              "DO" : [
                                                { "mimemail" : {
                                                    "key" : "[site:current-date]",
                                                    "to" : [ "uid:mail" ],
                                                    "subject" : "\\u003C?php print $node-\\u003Efield_email_subject[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E",
                                                    "body" : "\\u003Ctable cellpadding=\\u00220\\u0022 cellspacing=\\u00220\\u0022 border=\\u00220\\u0022 width=\\u0022100%\\u0022 class=\\u0022hide-ics\\u0022\\u003E\\r\\n  \\u003Ctr\\u003E\\r\\n    \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/pattern.png\\u0022 valign=\\u0022top\\u0022 bgcolor=\\u0022#E3E3DF\\u0022\\u003E\\r\\n      \\u003Cdiv\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022header\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022logos center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd width=\\u0022351\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/capt_logo.png\\u0022 width=\\u0022350\\u0022 height=\\u002280\\u0022 alt=\\u0022CAPT - SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                  \\u003Ctd width=\\u0022250\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/samhsa_logo.png\\u0022 width=\\u0022250\\u0022 height=\\u002280\\u0022 alt=\\u0022SAMHSA - U.S. Substance Abuse and Mental Health Services Administration\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022banner center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/banner.png\\u0022 bgcolor=\\u0022#567583\\u0022 width=\\u0022600\\u0022 height=\\u0022134\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n              \\u003Cdiv\\u003E\\r\\n  \\r\\n                \\u003C?php\\r\\n                  if (!empty($nid_event-\\u003Efield_banner_text)) {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $nid_event-\\u003Efield_banner_text[\\u0027und\\u0027][0][\\u0027value\\u0027] . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else if (!empty($nid_event-\\u003Efield_category)) {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $term-\\u003Ename . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else {\\r\\n                    $term = taxonomy_term_load($nid_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 36px; margin-top: 32px;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 15px; text-transform: uppercase;\\u0022\\u003EYour access point for all CAPT virtual events\\u003C\\/div\\u003E\\u003Cdiv\\u003E\\u0027 . $term . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                ?\\u003E\\r\\n\\r\\n              \\u003C\\/div\\u003E\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd bgcolor=\\u0022#FFFFFF\\u0022\\u003E\\r\\n\\r\\n              \\u003C?php print $node-\\u003Efield_email_body[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022footer\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022mailing center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd\\u003E\\r\\n                    \\u003Cp\\u003EMailing Address: SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u003Cbr\\u003EEducation Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313\\u003C\\/p\\u003E\\r\\n                    \\u003Cp\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003ETerms\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EPrivacy\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EUnsubscribe\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n                    \\u003Cp id=\\u0022date\\u0022\\u003E[site:current-date]\\u003C\\/p\\u003E \\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n      \\u003C\\/div\\u003E\\r\\n    \\u003C\\/td\\u003E\\r\\n  \\u003C\\/tr\\u003E\\r\\n\\u003C\\/table\\u003E",
                                                    "language" : [ "" ]
                                                  }
                                                }
                                              ]
                                            }
                                          ]
                                        }
                                      ]
                                    }
                                  ]
                                }
                              ]
                            }
                          }
                        ]
                      }
                    }
                  ]
                }
              }
            ]
          }
        },
        { "schedule" : {
            "component" : "rules_event_reminder_send_in_am",
            "date" : "Tomorrow 6am",
            "identifier" : "1"
          }
        }
      ]
    }
  }');
  $items['rules_launch_event'] = entity_import('rules_config', '{ "rules_launch_event" : {
      "LABEL" : "Launch event",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "flag" ],
      "ON" : { "flag_flagged_participate" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "flagged-node" ],
            "type" : "node",
            "bundle" : { "value" : { "instance" : "instance" } }
          }
        },
        { "data_is" : { "data" : [ "flagging-user" ], "value" : [ "site:current-user" ] } }
      ],
      "DO" : [ { "redirect" : { "url" : [ "flagged-node:field-link:url" ] } } ]
    }
  }');
  $items['rules_redirect_to_events_dashboard_if_trying_to_view_user'] = entity_import('rules_config', '{ "rules_redirect_to_events_dashboard_if_trying_to_view_user" : {
      "LABEL" : "Redirect to events dashboard if trying to view user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_view" : [] },
      "DO" : [ { "redirect" : { "url" : "events" } } ]
    }
  }');
  $items['rules_send_test_notification'] = entity_import('rules_config', '{ "rules_send_test_notification" : {
      "LABEL" : "Send test notification",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "php", "rules_conditional", "mimemail", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "entityform" ],
            "type" : "entityform",
            "bundle" : { "value" : { "notification_test" : "notification_test" } }
          }
        }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : {
              "type" : "text",
              "value" : "\\u003C?php $args = explode(\\u0027\\/\\u0027, current_path());\\r\\nreturn $args[1]; ?\\u003E"
            },
            "PROVIDE" : { "variable_added" : { "event" : "Event" } }
          }
        },
        { "data_convert" : {
            "USING" : { "type" : "integer", "value" : [ "event" ] },
            "PROVIDE" : { "conversion_result" : { "event_nid" : "Event nid" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "event-nid" ] },
            "PROVIDE" : { "entity_fetched" : { "fetched_event" : "Fetched event" } }
          }
        },
        { "CONDITIONAL" : [
            {
              "IF" : { "entity_is_of_bundle" : {
                  "entity" : [ "fetched-event" ],
                  "type" : "node",
                  "bundle" : { "value" : { "event" : "event" } }
                }
              },
              "DO" : [
                { "entity_fetch" : {
                    "USING" : {
                      "type" : "node",
                      "id" : [ "fetched-event:field-related-notifications:nid" ]
                    },
                    "PROVIDE" : { "entity_fetched" : { "fetched_event_notifications" : "Fetched event notifications" } }
                  }
                },
                { "CONDITIONAL" : [
                    {
                      "IF" : { "entity_is_of_bundle" : {
                          "entity" : [ "fetched-event-notifications" ],
                          "type" : "node",
                          "bundle" : { "value" : { "event_notifications" : "event_notifications" } }
                        }
                      },
                      "DO" : [
                        { "variable_add" : {
                            "USING" : { "type" : "integer", "value" : [ "" ] },
                            "PROVIDE" : { "variable_added" : { "notification_nid" : "Notification nid" } }
                          }
                        },
                        { "CONDITIONAL" : [
                            {
                              "IF" : { "data_is" : {
                                  "data" : [ "entityform:field-notification-type:name" ],
                                  "value" : "Event registration"
                                }
                              },
                              "DO" : [
                                { "data_set" : {
                                    "data" : [ "notification-nid" ],
                                    "value" : [ "fetched-event-notifications:field-event-registration:nid" ]
                                  }
                                }
                              ]
                            },
                            {
                              "ELSE IF" : { "data_is" : {
                                  "data" : [ "entityform:field-notification-type:name" ],
                                  "value" : "Event cancellation"
                                }
                              },
                              "DO" : [
                                { "data_set" : {
                                    "data" : [ "notification-nid" ],
                                    "value" : [ "fetched-event-notifications:field-event-cancellation:nid" ]
                                  }
                                }
                              ]
                            },
                            {
                              "ELSE IF" : { "data_is" : {
                                  "data" : [ "entityform:field-notification-type:name" ],
                                  "value" : "Event reminder"
                                }
                              },
                              "DO" : [
                                { "data_set" : {
                                    "data" : [ "notification-nid" ],
                                    "value" : [ "fetched-event-notifications:field-event-reminder:nid" ]
                                  }
                                }
                              ]
                            },
                            {
                              "ELSE IF" : { "data_is" : {
                                  "data" : [ "entityform:field-notification-type:name" ],
                                  "value" : "Event followup"
                                }
                              },
                              "DO" : [
                                { "data_set" : {
                                    "data" : [ "notification-nid" ],
                                    "value" : [ "fetched-event-notifications:field-event-followup:nid" ]
                                  }
                                }
                              ]
                            }
                          ]
                        },
                        { "entity_fetch" : {
                            "USING" : { "type" : "node", "id" : [ "notification-nid" ] },
                            "PROVIDE" : { "entity_fetched" : { "node" : "Nid" } }
                          }
                        },
                        { "mimemail" : {
                            "key" : "[site:current-date]",
                            "to" : [ "site:current-user:mail" ],
                            "subject" : "TEST: \\u003C?php print $node-\\u003Efield_email_subject[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E",
                            "body" : "\\u003Ctable cellpadding=\\u00220\\u0022 cellspacing=\\u00220\\u0022 border=\\u00220\\u0022 width=\\u0022100%\\u0022 class=\\u0022[ics-class:value]\\u0022\\u003E\\r\\n  \\u003Ctr\\u003E\\r\\n    \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/pattern.png\\u0022 valign=\\u0022top\\u0022 bgcolor=\\u0022#E3E3DF\\u0022\\u003E\\r\\n      \\u003Cdiv\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022header\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022logos center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd width=\\u0022351\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/capt_logo.png\\u0022 width=\\u0022350\\u0022 height=\\u002280\\u0022 alt=\\u0022CAPT - SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                  \\u003Ctd width=\\u0022250\\u0022 height=\\u002278\\u0022 valign=\\u0022bottom\\u0022\\u003E\\r\\n                    \\u003Cimg src=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/samhsa_logo.png\\u0022 width=\\u0022250\\u0022 height=\\u002280\\u0022 alt=\\u0022SAMHSA - U.S. Substance Abuse and Mental Health Services Administration\\u0022\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022banner center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/banner.png\\u0022 bgcolor=\\u0022#567583\\u0022 width=\\u0022600\\u0022 height=\\u0022134\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n              \\u003Cdiv\\u003E\\r\\n  \\r\\n                \\u003C?php\\r\\n                  if (!empty($fetched_event-\\u003Efield_banner_text)) {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $fetched_event-\\u003Efield_banner_text[\\u0027und\\u0027][0][\\u0027value\\u0027] . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else if (!empty($fetched_event-\\u003Efield_category)) {\\r\\n                    $term = taxonomy_term_load($fetched_event-\\u003Efield_category[\\u0027und\\u0027][0][\\u0027target_id\\u0027]);\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 24px; margin-top: 36px; line-height: 1;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 36px; opacity: 0.5;\\u0022\\u003E\\u0027 .  $term-\\u003Ename . \\u0027\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                  else {\\r\\n                    print \\u0027\\u003Cdiv style=\\u0022font-size: 36px; margin-top: 32px;\\u0022\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E\\u003Cstrong\\u003ECAPT\\u003C\\/strong\\u003E \\u003Cem style=\\u0022font-weight: normal;\\u0022\\u003EConnect\\u003C\\/em\\u003E\\u003C\\/a\\u003E\\u003C\\/div\\u003E\\u003Cdiv style=\\u0022font-size: 15px; text-transform: uppercase;\\u0022\\u003EYour access point for all CAPT virtual events\\u003C\\/div\\u003E\\u0027;\\r\\n                  }\\r\\n                ?\\u003E\\r\\n\\r\\n              \\u003C\\/div\\u003E\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022center\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd bgcolor=\\u0022#FFFFFF\\u0022\\u003E\\r\\n\\r\\n              \\u003C?php print $node-\\u003Efield_email_body[\\u0027und\\u0027][0][\\u0027value\\u0027]; ?\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n        \\u003Ctable class=\\u0022footer\\u0022\\u003E\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022colorband\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd background=\\u0022[site:url]sites\\/captconnect.edc.org\\/themes\\/capt\\/images\\/mail\\/colorband.png\\u0022 bgcolor=\\u0022#E4E3E1\\u0022 width=\\u0022580\\u0022 height=\\u00226\\u0022 valign=\\u0022top\\u0022\\u003E\\r\\n                    \\u003Cdiv\\u003E\\r\\n                    \\u003C\\/div\\u003E\\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n\\r\\n          \\u003Ctr\\u003E\\r\\n            \\u003Ctd\\u003E\\r\\n\\r\\n              \\u003Ctable class=\\u0022mailing center\\u0022\\u003E\\r\\n                \\u003Ctr\\u003E\\r\\n                  \\u003Ctd\\u003E\\r\\n                    \\u003Cp\\u003EMailing Address: SAMHSA\\u0027s Center for the Application of Prevention Technologies\\u003Cbr\\u003EEducation Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313\\u003C\\/p\\u003E\\r\\n                    \\u003Cp\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003ETerms\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EPrivacy\\u003C\\/a\\u003E | \\u003Ca href=\\u0022[site:url]\\u0022\\u003EUnsubscribe\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n                    \\u003Cp id=\\u0022date\\u0022\\u003E[site:current-date]\\u003C\\/p\\u003E \\r\\n                  \\u003C\\/td\\u003E\\r\\n                \\u003C\\/tr\\u003E\\r\\n              \\u003C\\/table\\u003E\\r\\n\\r\\n            \\u003C\\/td\\u003E\\r\\n          \\u003C\\/tr\\u003E\\r\\n        \\u003C\\/table\\u003E\\r\\n\\r\\n      \\u003C\\/div\\u003E\\r\\n    \\u003C\\/td\\u003E\\r\\n  \\u003C\\/tr\\u003E\\r\\n\\u003C\\/table\\u003E",
                            "language" : [ "" ]
                          }
                        }
                      ]
                    }
                  ]
                }
              ]
            }
          ]
        },
        { "entity_delete" : { "data" : [ "entityform" ] } }
      ]
    }
  }');
  $items['rules_update_notifications_and_event_relationships'] = entity_import('rules_config', '{ "rules_update_notifications_and_event_relationships" : {
      "LABEL" : "Update notifications and event relationships",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_conditional" ],
      "ON" : { "node_insert--event" : { "bundle" : "event" } },
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "event_notifications",
              "param_title" : "[node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "event_notifications_created" : "Created event notifications" } }
          }
        },
        { "data_set" : {
            "data" : [ "event-notifications-created:field-related-event" ],
            "value" : [ "node" ]
          }
        },
        { "entity_save" : { "data" : [ "event-notifications-created" ], "immediate" : "1" } },
        { "data_set" : {
            "data" : [ "node:field-related-notifications" ],
            "value" : [ "event-notifications-created" ]
          }
        },
        { "entity_save" : { "data" : [ "node" ], "immediate" : "1" } },
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "notification",
              "param_title" : "[node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "event_registration_created" : "Created event registration" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : "149" },
            "PROVIDE" : { "entity_fetched" : { "event_registration_template" : "Event registration template" } }
          }
        },
        { "CONDITIONAL" : [
            {
              "IF" : { "entity_is_of_bundle" : {
                  "entity" : [ "event-registration-template" ],
                  "type" : "node",
                  "bundle" : { "value" : { "template" : "template" } }
                }
              },
              "DO" : [
                { "data_set" : {
                    "data" : [ "event-registration-created:field-related-event" ],
                    "value" : [ "node" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-registration-created:field-use-a-default-template" ],
                    "value" : [ "event-registration-template" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-registration-created:field-email-subject" ],
                    "value" : [ "event-registration-template:field-email-subject" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-registration-created:field-email-body" ],
                    "value" : [ "event-registration-template:field-email-body" ]
                  }
                },
                { "entity_save" : { "data" : [ "event-registration-created" ], "immediate" : "1" } }
              ]
            }
          ]
        },
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "notification",
              "param_title" : "[node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "event_cancellation_created" : "Created event cancellation" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : "235" },
            "PROVIDE" : { "entity_fetched" : { "event_cancellation_template" : "Event cancellation template" } }
          }
        },
        { "CONDITIONAL" : [
            {
              "IF" : { "entity_is_of_bundle" : {
                  "entity" : [ "event-cancellation-template" ],
                  "type" : "node",
                  "bundle" : { "value" : { "template" : "template" } }
                }
              },
              "DO" : [
                { "data_set" : {
                    "data" : [ "event-cancellation-created:field-related-event" ],
                    "value" : [ "node" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-cancellation-created:field-use-a-default-template" ],
                    "value" : [ "event-cancellation-template" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-cancellation-created:field-email-subject" ],
                    "value" : [ "event-cancellation-template:field-email-subject" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-cancellation-created:field-email-body" ],
                    "value" : [ "event-cancellation-template:field-email-body" ]
                  }
                },
                { "entity_save" : { "data" : [ "event-cancellation-created" ], "immediate" : "1" } }
              ]
            }
          ]
        },
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "notification",
              "param_title" : "[node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "event_reminder_created" : "Created event reminder" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : "151" },
            "PROVIDE" : { "entity_fetched" : { "event_reminder_template" : "Event reminder template" } }
          }
        },
        { "CONDITIONAL" : [
            {
              "IF" : { "entity_is_of_bundle" : {
                  "entity" : [ "event-reminder-template" ],
                  "type" : "node",
                  "bundle" : { "value" : { "template" : "template" } }
                }
              },
              "DO" : [
                { "data_set" : {
                    "data" : [ "event-reminder-created:field-related-event" ],
                    "value" : [ "node" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-reminder-created:field-use-a-default-template" ],
                    "value" : [ "event-reminder-template" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-reminder-created:field-email-subject" ],
                    "value" : [ "event-reminder-template:field-email-subject" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-reminder-created:field-email-body" ],
                    "value" : [ "event-reminder-template:field-email-body" ]
                  }
                },
                { "entity_save" : { "data" : [ "event-reminder-created" ], "immediate" : "1" } }
              ]
            }
          ]
        },
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "notification",
              "param_title" : "[node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "event_followup_created" : "Created event followup" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : "186" },
            "PROVIDE" : { "entity_fetched" : { "event_followup_template" : "Event followup template" } }
          }
        },
        { "CONDITIONAL" : [
            {
              "IF" : { "entity_is_of_bundle" : {
                  "entity" : [ "event-followup-template" ],
                  "type" : "node",
                  "bundle" : { "value" : { "template" : "template" } }
                }
              },
              "DO" : [
                { "data_set" : {
                    "data" : [ "event-followup-created:field-related-event" ],
                    "value" : [ "node" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-followup-created:field-use-a-default-template" ],
                    "value" : [ "event-followup-template" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-followup-created:field-email-subject" ],
                    "value" : [ "event-followup-template:field-email-subject" ]
                  }
                },
                { "data_set" : {
                    "data" : [ "event-followup-created:field-email-body" ],
                    "value" : [ "event-followup-template:field-email-body" ]
                  }
                },
                { "entity_save" : { "data" : [ "event-followup-created" ], "immediate" : "1" } }
              ]
            }
          ]
        },
        { "data_set" : {
            "data" : [ "event-notifications-created:field-event-registration" ],
            "value" : [ "event-registration-created" ]
          }
        },
        { "data_set" : {
            "data" : [ "event-notifications-created:field-event-reminder" ],
            "value" : [ "event-reminder-created" ]
          }
        },
        { "data_set" : {
            "data" : [ "event-notifications-created:field-event-followup" ],
            "value" : [ "event-followup-created" ]
          }
        },
        { "data_set" : {
            "data" : [ "event-notifications-created:field-event-cancellation" ],
            "value" : [ "event-cancellation-created" ]
          }
        },
        { "entity_save" : { "data" : [ "event-notifications-created" ], "immediate" : "1" } }
      ]
    }
  }');
  $items['rules_update_notifications_title_if_event_title_changed'] = entity_import('rules_config', '{ "rules_update_notifications_title_if_event_title_changed" : {
      "LABEL" : "Update notifications title if event title changed",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update--event" : { "bundle" : "event" } },
      "IF" : [
        { "NOT data_is" : { "data" : [ "node:title" ], "value" : [ "node-unchanged:title" ] } }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "node:field-related-notifications:title" ],
            "value" : [ "node:title" ]
          }
        }
      ]
    }
  }');
  return $items;
}
