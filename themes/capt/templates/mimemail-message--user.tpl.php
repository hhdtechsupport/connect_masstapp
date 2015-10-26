<!-- mimemail-message__user.tpl.php -->

<html>
  <head>
    <title></title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <style type="text/css">
      <?php print $css; ?>

      .main {
        width: 580px;
      }

      .footer {
        background-color: #e4e3e1;
        width: 580px;
      }

      .footer p {
        margin-top: 0;
        padding: 0 12px 1em 12px;
        width: 556px;
      }

      .message-body p,
      .message-body {
        padding: 15px;
        width: 550px;
      }
    </style>
  </head>
  <body id="mimemail-body">
    <div id="center">
      <div id="main">
        <img src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/banner.png"
          alt="background" style="width: 580px;"/>
        <br />
        <img src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png"
          style="width: 580px; margin-top: 0;">

        <div class="message-body">
          <?php print $body ?>
        </div>

        <img src="http://dev.captconnect.edc.org/sites/captconnect.edc.org/themes/capt/images/mail/colorband.png"
          style="width: 580px;">
        <div class="footer">
          <p>Contacts for Questions/Issues: Technical Problems (<a href="mailto:mbiewener@edc.org">Matt Biewener</a>), Content and Materials Approval (<a href="mailto:madler@edc.org">Melanie Adler</a>)</p>
        </div>
      </div>
    </div>
  </body>
</html>
