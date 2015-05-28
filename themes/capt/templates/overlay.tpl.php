<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://api.drupal.org/api/drupal/modules!overlay!overlay.tpl.php/7
 * @see https://drupal.org/node/1728148
 */
?>


<div id="page">
  <header class="header" id="header" role="banner">
    <?php print render($page['header']); ?>
    <?php print render($page['highlighted']); ?>
  </header>

  <div id="main">

    <div id="content" class="column" role="main">
      <a id="main-content"></a>
      <?php print $messages; ?>
      <?php print render($page['help']); ?>
      <?php print render($title_prefix); ?>

      <?php print render($tabs); ?>

      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
    </div>

    <div id="navigation">
      <?php print render($page['navigation']); ?>
    </div>

  </div>

</div>
