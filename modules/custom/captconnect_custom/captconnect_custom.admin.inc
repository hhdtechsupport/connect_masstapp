<?php
/**
 * @file
 * Adminstrative functions for CAPTConnect.
 */
 
function captconnect_custom_admin_settings($form, $form_state) {
  global $user;
  $form = array();
  $noyes = array(t('No'), t('Yes'));

  $form['login_page_title'] = array(
    '#type' => 'textfield',
    '#title' => "'Log in' page title",
    '#default_value' => variable_get('login_page_title', 'Log in'),
    );

  $form['request_password_text'] = array(
    '#type' => 'textfield',
    '#title' => "'Request a new password' link text",
    '#default_value' => variable_get('request_password_text', 'Request a new password'),
    );

  return system_settings_form($form);
}
