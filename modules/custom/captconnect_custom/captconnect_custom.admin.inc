<?php
/**
 * @file
 * Adminstrative functions for CAPTConnect.
 */
 
function captconnect_custom_admin_settings($form, $form_state) {
  global $user;
  $form = array();
  $noyes = array(t('No'), t('Yes'));

  $form['captconnect_custom_login_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t("'Log in' page title"),
    '#default_value' => variable_get('captconnect_custom_login_page_title', 'Log in'),
    );

  $form['captconnect_custom_request_password_text'] = array(
    '#type' => 'textfield',
    '#title' => t("'Request a new password' link text"),
    '#default_value' => variable_get('captconnect_custom_request_password_text', 'Request a new password'),
    );

  $flags = db_query("SELECT name, title FROM {flag}")->fetchAllKeyed();
  $form['captconnect_custom_other_flag'] = array(
    '#type' => 'radios',
    '#options' => $flags,
    '#title' => t("Flag to use when registering for someone else"),
    '#default_value' => variable_get('captconnect_custom_other_flag', 'registration'),
    );

  $form['captconnect_custom_proxy_display'] = array(
    '#type' => 'radios',
    '#options' => array('node' => t('Node'), 'registration' => t('Registration Page')),
    '#title' => t("Where to display the 'Register someone else' button"),
    '#default_value' => variable_get('captconnect_custom_proxy_display', 'registration'),
    );

  return system_settings_form($form);
}
