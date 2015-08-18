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
            <td background="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/pattern.png" valign="top" bgcolor="#E3E3DF">
            <!--[if gte mso 9]>
            <v:rect xmlns:v="urn:schemas-microsoft-com:vml" fill="true" stroke="false" style="mso-width-percent:1000;">
              <v:fill type="tile" src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/pattern.png" color="#E3E3DF" />
              <v:textbox inset="0,0,0,0">
            <![endif]-->
              <div>

                <table class="header">
                  <tr>
                    <td>

                      <table class="logos center">
                        <tr>
                          <td width="351" height="78" valign="bottom">
                            <img src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/capt_logo.png" width="350" height="80" alt="CAPT - SAMHSA's Center for the Application of Prevention Technologies">
                          </td>
                          <td width="250" height="78" valign="bottom">
                            <img src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/samhsa_logo.png" width="250" height="80" alt="SAMHSA - U.S. Substance Abuse and Mental Health Services Administration">
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>

                  <tr>
                    <td>

                      <table class="colorband">
                        <tr>
                          <td background="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png" bgcolor="#E4E3E1" width="580" height="6" valign="top">
                          <!--[if gte mso 9]>
                          <v:rect xmlns:v="urn:schemas-microsoft-com:vml" fill="true" stroke="false" style="width:580px;height:6px;">
                            <v:fill type="tile" src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png" color="#E4E3E1" />
                            <v:textbox inset="0,0,0,0">
                          <![endif]-->
                            <div>
                            </div>
                          <!--[if gte mso 9]>
                            </v:textbox>
                          </v:rect>
                          <![endif]-->
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>

                </table>

                <table class="banner center">
                  <tr>
                    <td background="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/banner.png" bgcolor="#567583" width="600" height="134" valign="top">
                    <!--[if gte mso 9]>
                    <v:rect xmlns:v="urn:schemas-microsoft-com:vml" fill="true" stroke="false" style="width:600px;height:134px;">
                      <v:fill type="tile" src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/banner.png" color="#567583" />
                      <v:textbox inset="0,0,0,0">
                    <![endif]-->
                      <div>
                        <div style="font-size: 36px; margin-top: 32px;">
                          <strong>CAPT</strong> <em style="font-weight: normal;">Connect</em>
                        </div>
                        <div style="font-size: 15px; text-transform: uppercase;">
                          Your access point for all CAPT virtual events
                        </div>
                      </div>
                    <!--[if gte mso 9]>
                      </v:textbox>
                    </v:rect>
                    <![endif]-->
                    </td>
                  </tr>
                </table>

                <table class="center">
                  <tr>
                    <td bgcolor="#FFFFFF">

                      <div style="padding: 15px; width: 550px">
                        <?php print $body ?>
                      </div>

                    </td>
                  </tr>
                </table>

                <table class="footer">
                  <tr>
                    <td>

                      <table class="colorband">
                        <tr>
                          <td background="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png" bgcolor="#E4E3E1" width="580" height="6" valign="top">
                          <!--[if gte mso 9]>
                          <v:rect xmlns:v="urn:schemas-microsoft-com:vml" fill="true" stroke="false" style="width:580px;height:6px;">
                          <v:fill type="tile" src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png" color="#E4E3E1" />
                          <v:textbox inset="0,0,0,0">
                          <![endif]-->
                            <div>
                            </div>
                          <!--[if gte mso 9]>
                          </v:textbox>
                          </v:rect>
                          <![endif]-->
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
                            <p><a href="http://dev.captconnect.edc.org">Terms</a> | <a href="http://dev.captconnect.edc.org">Privacy</a> | <a href="http://dev.captconnect.edc.org">Unsubscribe</a></p>
                            <p id="date">[site:current-date]</p>
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>
                </table>

              </div>
            <!--[if gte mso 9]>
              </v:textbox>
            </v:rect>
            <![endif]-->
            </td>
          </tr>
        </table>


      </div>
    </div>
  </body>
</html>
