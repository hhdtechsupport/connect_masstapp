<?php

/**
 * @file
 * Default theme implementation to format an HTML mail.
 *
 * Copy this file in your default theme folder to create a custom themed mail.
 * Rename it to mimemail-message--[module]--[key].tpl.php to override it for a
 * specific mail.
 *
 * Available variables:
 * - $recipient: The recipient of the message
 * - $subject: The message subject
 * - $body: The message body
 * - $css: Internal style sheets
 * - $module: The sending module
 * - $key: The message identifier
 *
 * @see template_preprocess_mimemail_message()
 */
?>

<?php $base_url = $GLOBALS['base_url']; ?>

<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <?php if ($css): ?>
    <style type="text/css">
      <!--
      <?php print $css ?>
      -->
    </style>
    <?php endif; ?>
  </head>
  <body id="mimemail-body" <?php if ($module && $key): print 'class="'. $module .'-'. $key .'"'; endif; ?>>
    <div id="center">
      <div id="main">

        <table cellpadding="0" cellspacing="0" border="0" width="100%" class="[ics-class:value]">
          <tr>
            <td background="http://masstapp-ta.edc.org/sites/masstapp-ta.edc.org/files/page-images/pattern.png" valign="top" bgcolor="#E3E3DF">
              <div>

                <table class="header">
                  <tr>
                    <td>

                      <table class="logos center">
                        <tr>
                          <td width="351" height="78" valign="bottom">
                            <img src="http://masstapp-ta.edc.org/sites/masstapp-ta.edc.org/files/page-images/capt_logo.png" width="350" height="80" alt="CAPT - SAMHSA's Center for the Application of Prevention Technologies" title="CAPT - SAMHSA's Center for the Application of Prevention Technologies">
                          </td>
                          <td width="250" height="78" valign="bottom">
                            <img src="http://masstapp-ta.edc.org/sites/masstapp-ta.edc.org/files/page-images/samhsa_logo.png" width="250" height="80" alt="SAMHSA - U.S. Substance Abuse and Mental Health Services Administration" title="SAMHSA - U.S. Substance Abuse and Mental Health Services Administration">
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>

                  <tr>
                    <td>

                      <table class="colorband">
                        <tr>
                          <td background="http://masstapp-ta.edc.org/sites/masstapp-ta.edc.org/files/page-images/colorband.png" bgcolor="#E4E3E1" width="580" height="6" valign="top">
                            <div>
                            </div>
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>

                </table>

                <table class="banner center">
                  <tr>
                    <td background="http://masstapp-ta.edc.org/sites/masstapp-ta.edc.org/files/page-images/banner.png" bgcolor="#567583" width="600" height="134" valign="top">
                      <div>

                        <?php
                          if (!empty($nid_event->field_banner_text)) {
                            print '<div style="font-size: 24px; margin-top: 36px; line-height: 1;"><strong>CAPT</strong> <em style="font-weight: normal;">Connect</em></div><div style="font-size: 36px; opacity: 0.5;">' .  $nid_event->field_banner_text['und'][0]['value'] . '</div>';
                          }
                          else if (!empty($nid_event->field_category)) {
                            $term = taxonomy_term_load($nid_event->field_category['und'][0]['target_id']);
                            print '<div style="font-size: 24px; margin-top: 36px; line-height: 1;"><strong>CAPT</strong> <em style="font-weight: normal;">Connect</em></div><div style="font-size: 36px; opacity: 0.5;">' .  $term->name . '</div>';
                          }
                          else {
                            print '<div style="font-size: 36px; margin-top: 32px;"><strong>CAPT</strong> <em style="font-weight: normal;">Connect</em></div><div style="font-size: 15px; text-transform: uppercase;">Your access point for all CAPT virtual events</div>';
                          }
                        ?>

                      </div>
                    </td>
                  </tr>
                </table>

                <table class="center content">
                  <tr>
                    <td bgcolor="#FFFFFF">
                      <div style="padding: 25px"><?php print $body; ?></div>
                    </td>
                  </tr>
                </table>

                <table class="footer">
                  <tr>
                    <td>

                      <table class="colorband">
                        <tr>
                          <td background="http://masstapp-ta.edc.org/sites/masstapp-ta.edc.org/files/page-images/colorband.png" bgcolor="#E4E3E1" width="580" height="6" valign="top">
                            <div>
                            </div>
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>

                  <tr>
                    <td>

                      <table class="mailing center">
                        <tr>
                          <td>
                            <p>Mailing Address: SAMHSA's Center for the Application of Prevention Technologies<br>Education Development Center, Inc. | 43 Foundry Ave | Waltham, MA 02453-8313</p>
                            <p><a href="<?php print $base_url; ?>/terms-of-use">Terms of Use</a> | <a href="http://www.samhsa.gov/privacy">SAMHSA Privacy Policy</a></p>
                            <p class="unsubscribe">You are receiving this message because you have a user account at CAPT Connect.<br>If you no longer wish to receive such notifications, you must <a href="<?php print $base_url; ?>/user">log in and cancel your account to unsubscribe</a>.</p>                          </td>
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>
                </table>

              </div>
            </td>
          </tr>
        </table>



      </div>
    </div>
  </body>
</html>
