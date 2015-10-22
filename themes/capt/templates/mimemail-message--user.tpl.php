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
<!-- mimemail-message__user.tpl.php -->
<html>
  <head>
    <title></title>
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
            <td style='background:"http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/pattern.png"'
              valign="top" bgcolor="#E3E3DF">
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
                          <td width="580">
                            <div style="font-size: 24px; margin-top: 20px; color: black;"><strong>CAPT</strong> <em style="font-weight: normal;">Connect</em></div>
                          </td>
                        </tr>
                      </table>

                    </td>
                  </tr>

                  <tr>
                    <td>

                      <table class="colorband">
                        <tr>
                          <td style='background:"http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png"'
                            bgcolor="#E4E3E1" width="580" height="6" valign="top">
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
                          <td style='background:"http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png"'
                            bgcolor="#E4E3E1" width="580" height="6" valign="top">
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
                          <td width="580">
                            <div style="text-align:left">
                              <p>Contacts for Questions/Issues: Technical Problems (<a href="mbiewener@edc.org">Matt Biewener</a>), Content and Materials Approval (<a href="madler@edc.org">Melanie Adler</a>)</p>
                            </div>
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
