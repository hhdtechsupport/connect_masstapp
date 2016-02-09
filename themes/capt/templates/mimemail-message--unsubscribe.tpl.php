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
<!-- mimemail-message.tpl.php -->

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
    <div id="rootDiv" class="[ics-class:value]">
      <div id="subRootDiv">
      <!--[if gte mso 9]>
        <v:background xmlns:v="urn:schemas-microsoft-com:vml" fill="t">
          <v:fill type="tile" src="https://mlsvc01-prod.s3.amazonaws.com/4746e1d9401/37df6fba-b775-41f3-b9c4-9241d5818eb3.png"  color="#E2E1DE" />
        </v:background>
      <![endif]-->
        <div class="OuterBGColor" background="https://mlsvc01-prod.s3.amazonaws.com/4746e1d9401/37df6fba-b775-41f3-b9c4-9241d5818eb3.png"
        align="center">
          <table class="OuterBGColor" border="0" background="https://mlsvc01-prod.s3.amazonaws.com/4746e1d9401/37df6fba-b775-41f3-b9c4-9241d5818eb3.png"
            width="100%" cellspacing="0" cellpadding="0">
            <tbody>
              <tr>
                <td class="HideInMobile" rowspan="1" colspan="1">
                  <img height="5" vspace="0" border="0" hspace="0" width="1" alt="" src="https://static.ctctcdn.com/letters/images/1101116784221/S.gif">
                </td>
                <td class="MainWidth" valign="top" width="610" rowspan="1" colspan="1" align="center">
                  <div class="MaxMainWidth" align="center">
                    <table border="0" width="100%" cellspacing="0" cellpadding="0">
                      <tbody>
                        <tr>
                          <td class="BodyPadding" valign="top" rowspan="1" colspan="1" align="center">
                            <table border="0" width="100%" cellspacing="0" cellpadding="0">
                              <tbody>
                                <tr>
                                  <td class="TopMargin" valign="top" width="100%" rowspan="1" colspan="1" align="center">
                                    <table border="0" width="100%" cellspacing="0" cellpadding="0">
                                      <tbody>
                                        <tr>
                                          <td class="OuterText Logo" valign="top" rowspan="1" colspan="1" align="center">
                                            <table width="600" data-padding-converted="true" cellspacing="0" cellpadding="0" align="none">
                                              <tbody>
                                                <tr>
                                                  <td class="tdWrapper" width="1%" rowspan="1" colspan="1">
                                                    <div align="center">
                                                      <a shape="rect" href="https://captconnect.edc.org" alt="https://captconnect.edc.org" target="_blank">
                                                        <img class="LogoImg" vspace="0" border="0" hspace="0" height="58"width="600" alt="U.S. Substance Abuse and Mental Health Services Administration's (SAMHSA's) Center for the Application of Prevention Technologies (CAPT)" src="https://mlsvc01-prod.s3.amazonaws.com/4746e1d9401/b590dce0-7a2e-46ad-b0b0-6935da492bbc.png">
                                                      </a>
                                                    </div>
                                                  </td>
                                                </tr>
                                              </tbody>
                                            </table>
                                          </td>
                                        </tr>
                                      </tbody>
                                    </table>
                                    <table border="0" width="100%" cellspacing="0" cellpadding="0">
                                      <tbody>
                                        <tr>
                                          <td class="Image MainText" valign="top" rowspan="1" colspan="1" align="center">
                                            <table width="600" data-padding-converted="true" cellspacing="0" cellpadding="0" align="none">
                                              <tbody>
                                                <tr>
                                                  <td style="tdWrapper" width="1%" rowspan="1" colspan="1">
                                                    <div align="center">
                                                      <img class="Rainbow" vspace="0" border="0" hspace="0" width="600" src="https://mlsvc01-prod.s3.amazonaws.com/4746e1d9401/dbe019af-35e1-4106-bff9-885cd75a767c.png">
                                                    </div>
                                                  </td>
                                                </tr>
                                              </tbody>
                                            </table>
                                          </td>
                                        </tr>
                                      </tbody>
                                    </table>
                                  </td>
                                </tr>
                              </tbody>
                            </table>
                            <table class="BorderColor" bgcolor="transparent" border="0" width="100%" cellspacing="0" cellpadding="0">
                              <tbody>
                                <tr>
                                  <td class="BorderWidth" valign="top" width="100%" rowspan="1" colspan="1" align="center">
                                    <table class="InnerBGColor" bgcolor="#FFFFFF" border="0" width="100%" cellspacing="0" cellpadding="0">
                                      <tbody>
                                        <tr>
                                          <td class="EmailContainer" valign="top" width="100%" rowspan="1" colspan="1" align="center">
                                            <table border="0" width="100%" cellspacing="0" cellpadding="0">
                                              <tbody>
                                                <tr>
                                                  <td class="Image MainText" valign="top" rowspan="1" colspan="1" align="center">
                                                    <table width="600" data-padding-converted="true" cellspacing="0" cellpadding="0" align="none">
                                                      <tbody>
                                                        <tr>
                                                          <td class="tdWrapper" width="1%" rowspan="1" colspan="1">
                                                            <div align="center">
                                                              <a shape="rect" href="https://captconnect.edc.org" alt="https://captconnect.edc.org" target="_blank">
                                                                <img class="BannerImage" vspace="0" border="0" hspace="0" width="600" height="150" alt="CAPT Connect: Your Access Point for All CAPT Virtual Events" src="https://mlsvc01-prod.s3.amazonaws.com/4746e1d9401/9714f8df-8d17-471e-b7de-206d52de96c1.png">
                                                              </a>
                                                            </div>
                                                          </td>
                                                        </tr>
                                                      </tbody>
                                                    </table>
                                                  </td>
                                                </tr>
                                              </tbody>
                                            </table>
                                            <table>
                                              <tbody>
                                                <tr>
                                                  <td id="Body">
                                                    <?php print $body; ?>
                                                  </td>
                                                </tr>
                                              </tbody>
                                            </table>
                                            <table border="0" width="100%" cellspacing="0" cellpadding="0">
                                              <tbody>
                                                <tr>
                                                  <td class="Image MainText" valign="top" rowspan="1" colspan="1" align="center">
                                                    <table class="OneColumnMobile" width="600" data-padding-converted="true" cellspacing="0" cellpadding="0" align="none">
                                                      <tbody>
                                                        <tr>
                                                          <td class="tdWrapper"  width="1%" rowspan="1" colspan="1">
                                                            <div align="center" class="RainbowTopWrapper">
                                                              <img class="Rainbox" vspace="0" border="0" name="ACCOUNT.IMAGE.176" hspace="0" width="600" src="https://mlsvc01-prod.s3.amazonaws.com/4746e1d9401/dbe019af-35e1-4106-bff9-885cd75a767c.png">
                                                            </div>
                                                          </td>
                                                        </tr>
                                                      </tbody>
                                                    </table>
                                                  </td>
                                                </tr>
                                              </tbody>
                                            </table>
                                          </td>
                                        </tr>
                                      </tbody>
                                    </table>
                                  </td>
                                </tr>
                              </tbody>
                            </table>
                            <table border="0" width="100%" cellspacing="0" cellpadding="0">
                              <tbody>
                                <tr>
                                  <td class="BottomMargin" valign="top" width="100%" rowspan="1" colspan="1" align="center">
                                    <table border="0" width="100%" cellspacing="0" cellpadding="0">
                                      <tbody>
                                        <tr>
                                          <td class="MailingText" valign="top" rowspan="1" colspan="1" align="center">
                                            <div>
                                              <span style="font-size: 9pt !important;">Mailing Address: Education Development Center<br>43 Foundry Avenue, Waltham, MA 02453<br><a shape="rect" href="https://captconnect.edc.org/terms" linktype="1" alt="https://captconnect.edc.org/terms" target="_blank">Terms of Use</a> | <a shape="rect" href="http://www.samhsa.gov/privacy" linktype="1" alt="http://www.samhsa.gov/privacy" target="_blank">Privacy Policy</a></span>
                                            </div>
                                          </td>
                                        </tr>
                                      </tbody>
                                    </table>
                                  </td>
                                </tr>
                              </tbody>
                            </table>
                          </td>
                        </tr>
                      </tbody>
                    </table>
                  </div>
                </td>
                <td class="HideInMobile" rowspan="1" colspan="1">
                  <img height="5" vspace="0" border="0" hspace="0" width="1" alt="" src="https://static.ctctcdn.com/letters/images/1101116784221/S.gif">
                </td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
  </body>
</html>
