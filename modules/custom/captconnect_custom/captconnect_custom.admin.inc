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
    '#default_value' => variable_get('captconnect_custom_request_password_text',
      'Request a new password'),
    );

  $flags = db_query("SELECT name, title FROM {flag}")->fetchAllKeyed();
  $form['captconnect_custom_other_flag'] = array(
    '#type' => 'radios',
    '#options' => $flags,
    '#title' => t("Flag to use when registering for someone else"),
    '#default_value' => variable_get('captconnect_custom_other_flag', 'registration'),
    );

  $form['captconnect_custom_proxy_register_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Text for "Register another" button'),
    '#default_value' => variable_get('captconnect_custom_proxy_register_text', 'Register Someone Else'),
    );

  $lead_time_values = array(0, 60, 300, 600, 900, 1200, 1800, 2700, 3600, 5400, 7200);
  $lead_time_labels = array_map('format_interval', $lead_time_values);
  $form['captconnect_custom_participate_lead_time'] = array(
    '#type' => 'radios',
    '#options' => array_combine($lead_time_values, $lead_time_labels),
    '#title' => t('Show a "participate" flag lead time'),
    '#default_value' => variable_get('captconnect_custom_participate_lead_time', 1800),
    '#description' => t('After this much time before the start of an event, show a "Participate" link.'),
    );

  $form['captconnect_custom_login_dest'] = array(
    '#type' => 'textfield',
    '#title' => t('Login destination'),
    '#default_value' => variable_get('captconnect_custom_login_dest', 'events'),
    '#description' => t('This is where a user will end up after logging in.'),
    ); /* */

  $form['captconnect_custom_registrations_link_instance'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#title' => t('Link the Instance name on the Registrations page.'),
    '#default_value' => variable_get('captconnect_custom_registrations_link_instance', 1),
    );

  $styles_list = image_styles();
  $styles = array();
  foreach ($styles_list as $style => $info) {
    $styles[$style] = $info['label'];
  }
  $form['captconnect_custom_presenters_list_style'] = array(
    '#type' => 'radios',
    '#options' => $styles,
    '#title' => t('Image style for Presenter image on the Presenters List page.'),
    '#default_value' => variable_get('captconnect_custom_presenters_list_style', 'thumbnail'),
    );

  $form['captconnect_custom_presenters_list_limit'] = array(
    '#type' => 'radios',
    '#options' => array(5 => 5, 10 => 10, 15 => 15, 20 => 20, 25 => 25, 50 => 50),
    '#title' => t('Number of presenters per page on the Presenters List.'),
    '#default_value' => variable_get('captconnect_custom_presenters_list_limit', 10),
    );

  $form['captconnect_custom_presenters_list_show_past'] = array(
    '#type' => 'radios',
    '#options' => $noyes,
    '#title' => t('Show past instances on the Presenters List page.'),
    '#default_value' => variable_get('captconnect_custom_presenters_list_show_past', 1),
    );

  $form['captconnect_custom_account_check_interval'] = array(
    '#type' => 'radios',
    '#options' => array(
      0 => t('Always'),
      1209600 => t('2 weeks'),
      2592000 => t('1 month'),
      5184000 => t('2 months'),
      7776000 => t('3 months'),
      15552000 => t('6 months'),
      31536000 => t('1 year'),
      ),
    '#title' => t('Ask users to check their accounts this often.'),
    '#default_value' => variable_get('captconnect_custom_account_check_interval', 7776000),
    '#description' => t('If the user has not updated their information in this
      length of time, force them to do so.<br>If the value is "always," we will
      not prevent them from going to other pages.'),
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
    array('data' => drupal_render($form['captconnect_custom_proxy_register_text']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_login_dest']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_registrations_link_instance']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_participate_lead_time']), 'style' => $style),
    array('data' => "&nbsp;", 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_presenters_list_style']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_presenters_list_limit']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_presenters_list_show_past']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_account_check_interval']), 'style' => $style),
    );

  $output .= theme('table', array(
    'rows' => $rows,
    'attributes' => array('id' => 'captconnect-custom-admin-settings'),
    ));

  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Message texts form.
 */
function captconnect_custom_message_texts($form, $form_state) {
  global $user;
  $form = array();
  $noyes = array(t('No'), t('Yes'));

  $form['captconnect_custom_registration_successful'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Registration Successful'),
    '#default_value' => variable_get('captconnect_custom_registration_successful',
      'You are now registered for "@title" on @when.'),
    '#description' => t('When the anonymous registration process succeeds, this message is displayed.')
      . '<br/>'
      . t('You may use these tokens:')
      . '<ul>'
      . '<li>' . t('@title - the title of the event.') . '</li>'
      . '<li>' . t('@when - the title (date and time) of the instance.') . '</li>'
      . '</ul>',
    );

  $form['captconnect_custom_registration_failed'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Registration Failed'),
    '#default_value' => variable_get('captconnect_custom_registration_failed',
      'Your registration for "@title" failed; please try again now that you are logged in.'),
    '#description' => t('If the anonymous registration fails, display this message.')
      . '<br/>'
      . t('You may use these tokens:')
      . '<ul>'
      . '<li>' . t('@title - the title of the event.') . '</li>'
      . '</ul>',
    );

  $form['captconnect_custom_must_change_password'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Must Change Password'),
    '#default_value' => variable_get('captconnect_custom_must_change_password',
      'In order to continue on this site, you need to change your password.'),
    '#description' => t('This message is displayed when an account is initially
      logged into in the anonymous registration process'),
    );

  $form['captconnect_custom_completion_email_anon'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Completion Email Sent (Anonymous)'),
    '#default_value' => variable_get('captconnect_custom_completion_email_anon',
      'An email has been sent with a link to complete the registration process.'),
    '#description' => t('This message is displayed when an account is created
      in the anonymous registration process'),
    );

  $form['captconnect_custom_completion_email_normal'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Completion Email Sent (Normal)'),
    '#default_value' => variable_get('captconnect_custom_completion_email_normal',
      'A welcome message with further instructions has been sent to your e-mail address.'),
    '#description' => t('This message is displayed when an account is created
      in the manual registration process'),
    );

  $form['captconnect_custom_reset_pass_head'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Reset password heading'),
    '#default_value' => variable_get('captconnect_custom_reset_pass_head',
      'Reset Password'),
//    '#description' => t(''),
    );

  $form['captconnect_custom_reset_pass_welcome'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Reset password explanation'),
    '#default_value' => variable_get('captconnect_custom_reset_pass_welcome',
      'Click on this button to log in to the site and change your password. '
      . 'This will also complete your registration for "@event" on @instance.'),
    '#description' => t('This text is displayed when a user has been invited to
      log in during the anonymoous registration process.')
      . '<br/>'
      . t('You may use these tokens:')
      . '<ul>'
      . '<li>' . t('@title - the title of the event.') . '</li>'
      . '<li>' . t('@when - the title (date and time) of the instance.') . '</li>'
      . '</ul>',
    );

  $form['captconnect_custom_anon_login'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Login invitation'),
    '#default_value' => variable_get('captconnect_custom_anon_login',
      'If you already have an account, please <a href="!login_url">Log In</a> to complete your registration.'),
    '#description' => t('When an anonymous user tries to register, this message
      is shown to invite a login rather than account creation.')
      . '<br/>'
      . t('You may use these tokens:')
      . '<ul>'
      . '<li>' . t('!login_url - the URL for logging in.') . '</li>'
      . '</ul>'
    );

  $form['captconnect_custom_anon_register'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Register invitation'),
    '#default_value' => variable_get('captconnect_custom_anon_register',
      'If you do not have an account, please <a href="!create_url">create an account</a> to complete your registration.'),
    '#description' => t('When an anonymous user tries to register, this message
      is shown to invite an account creation rather than a login.')
      . '<br/>'
      . t('You may use these tokens:')
      . '<ul>'
      . '<li>' . t('!create_url - the URL for creating an account.') . '</li>'
      . '</ul>'
    );

  $form['captconnect_custom_proxy_registered'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Successful proxy registration'),
    '#default_value' => variable_get('captconnect_custom_proxy_registered',
      '@user is now @action "@event" at @time.'),
    '#description' => t('When someone is registered or participated by someone
      else (proxy), this message indicates that the registration has succeeded.')
      . '<br/>'
      . t('You may use these tokens:')
      . '<ul>'
      . '<li>' . t('@event - the title of the event.') . '</li>'
      . '<li>' . t('@user - the name of the person.') . '</li>'
      . '<li>' . t('@time - the instance title (date and time).') . '</li>'
      . '<li>' . t('@action - the action taken.') . '</li>'
      . '</ul>',
    );

  $form['captconnect_custom_proxy_failed'] = array(
    '#type' => 'textarea',
    '#rows' => 1,
    '#title' => t('Unsuccessful proxy registration'),
    '#default_value' => variable_get('captconnect_custom_proxy_failed',
      'Flagging for @user for "@event" at @time failed.'),
    '#description' => t('When someone is registered or participated by someone else (proxy), this message indicates that the registration has failed.')
      . '<br/>'
      . t('You may use these tokens:')
      . '<ul>'
      . '<li>' . t('@event - the title of the event.') . '</li>'
      . '<li>' . t('@user - the name of the person.') . '</li>'
      . '<li>' . t('@time - the instance title (date and time).') . '</li>'
      . '<li>' . t('@action - the action taken.') . '</li>'
      . '</ul>',
    );

  $form['captconnect_custom_event_full'] = array(
    '#type' => 'textfield',
    '#maxlength' => 256,
    '#title' => t('Event is full'),
    '#default_value' => variable_get('captconnect_custom_event_full',
      'We are sorry, but this event is full. You may try registering for another time or date.'),
    '#description' => t('When someone tries to register for an event that is '
      . 'already at capacity, this message is displayed '
      . '<br />'
      . 'and the registration is denied.')
    );

  $form['captconnect_custom_login_email_help'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Account Email Help'),
    '#default_value' => variable_get('captconnect_custom_login_email_help',
      "A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used to alert you to upcoming events, those for which you have registered, and other communications."),
    '#description' => t('When someone edits or adds a user account, '
      . 'this text will be displayed below the "Email" field.'),
    );

  $form['captconnect_custom_account_check_msg'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Account Check Reminder'),
    '#default_value' => variable_get('captconnect_custom_account_check_msg',
      "Check your personal information, please."),
    '#description' => t("When someone logs in, check if it's been a while."),
    );

  $form['#theme'] = 'captconnect_custom_message_texts';

  return system_settings_form($form);
}

/**
 * Form theme.
 */
function theme_captconnect_custom_message_texts(&$variables) {
  $css = '#captconnect-custom-message-texts {font-size: 100% !important;}
    #captconnect-custom-message-texts textarea,
    #captconnect-custom-message-texts input {font-family: "Courier New", Courier, monospace; width: 95%}
    #captconnect-custom-message-texts .grippie {width: 95%;}
    #captconnect-custom-message-texts input#edit-submit {font-family: inherit; width: auto;}
    ';
  drupal_add_css($css, 'inline');

  $output = '';

  $form = $variables['form'];

  $rows = array();

  $style = 'vertical-align: top; white-space: normal';

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_registration_successful']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_registration_failed']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_must_change_password']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_event_full']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_completion_email_anon']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_completion_email_normal']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_reset_pass_head']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_reset_pass_welcome']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_proxy_registered']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_proxy_failed']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_anon_login']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_anon_register']), 'style' => $style),
    );

  $rows[] = array(
    array('data' => drupal_render($form['captconnect_custom_login_email_help']), 'style' => $style),
    array('data' => drupal_render($form['captconnect_custom_account_check_msg']), 'style' => $style),
    );

  $output .= theme('table', array(
    'rows' => $rows,
    'attributes' => array('id' => 'captconnect-custom-message-texts'),
    ));

  $output .= drupal_render_children($form);
  return $output;
}
