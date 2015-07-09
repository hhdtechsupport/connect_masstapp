<?php
/**
 * @file
 * Adminstrative functions for CAPTConnect.
 */

/**
 * Main settings form.
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

  $form['#theme'] = 'captconnect_custom_admin_settings';

  return system_settings_form($form);
}

/**
 * Theme the Main settings form.
 */

/**
 * Theme the Settings form.
 */
function theme_captconnect_custom_admin_settings($variables) {
  $css = '#captconnect-custom-admin-settings {font-size: 100%;}
  ';
  drupal_add_css($css, 'inline');

    $output = '';

  $form = $variables['form'];

  $rows = array();

  $style = 'vertical-align: top; white-space: normal';

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_login_page_title']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_request_password_text']), 'style' => $style),
    );


  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_other_flag']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_proxy_display']), 'style' => $style),
    );

  $output .= theme('table', array(
    'rows' => $rows,
    'attributes' => array('id' => 'captconnect-custom-admin-settings'),
    ));

  $output .= drupal_render_children($form);
  return $output;
}
