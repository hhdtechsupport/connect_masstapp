<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<div class="top-header">
  <div class="top-header-container">
    <a href="http://www.samhsa.gov/capt" title="SAMHSA's Center for the Application of Prevention Technologies"><div class="capt-logo">CAPT</div></a>
    <a href="http://www.samhsa.gov" title="U.S. Substance Abuse and Mental Health Services Administration"><div class="samhsa-logo">SAMHSA</div></a>
  </div>
</div>

<div id="page">

  <header class="header" id="header" role="banner">
    <div class="header-blue">

          <?php print render($page['header']); ?>

          <?php if ($logo): ?>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
          <?php endif; ?>

          <?php if ($site_name || $site_slogan): ?>
            <div class="header__name-and-slogan" id="name-and-slogan">
              <?php if ($site_name): ?>
                <h1 class="header__site-name" id="site-name">
                  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="header__site-link" rel="home"><span><strong>CAPT</strong> <em>Connect</em></span></a>
                </h1>
              <?php endif; ?>
            </div>
          <?php endif; ?>

          <?php if ($secondary_menu): ?>
            <nav class="header__secondary-menu" id="secondary-menu" role="navigation">
              <?php print theme('links__system_secondary_menu', array(
                'links' => $secondary_menu,
                'attributes' => array(
                  'class' => array('links', 'inline', 'clearfix'),
                ),
                'heading' => array(
                  'text' => $secondary_menu_heading,
                  'level' => 'h2',
                  'class' => array('element-invisible'),
                ),
              )); ?>
            </nav>
          <?php endif; ?>

          <?php print render($page['highlighted']); ?>

    </div>
    <div class="header-photos">
      <div class="row-1 photo-1 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-1 photo-2 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-1 photo-3 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-1 photo-4 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-1 photo-5 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-1 photo-6 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-1 photo-7 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-1 photo-8 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-1 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-2 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-3 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-4 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-5 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-6 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-7 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
      <div class="row-2 photo-8 photos"><span class="photo-inner"></span><span class="photo-inner"></span></div>
    </div>

  </header>

  <div id="main">

    <div id="content" class="column" role="main">
      <a id="main-content"></a>
      <?php print $messages; ?>
      <?php if (_menu_site_is_offline()) {
        print '<div class="messages--error messages error">
                <h2 class="element-invisible">Error message</h2>
                CAPT Connect is currently undergoing maintenance, but should be back shortly. Only site administrators may log in using the form below. Thank you for your patience.</div>'; } ?>
      <?php print render($title_prefix); ?>
      <div id="title-section">
      <?php if ($title): ?>
        <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      </div>
      <?php print render($title_suffix); ?>
      <?php print render($page['help']); ?>
      <?php print render($tabs); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php print $feed_icons; ?>
    </div>

    <div id="navigation">

      <?php if ($main_menu): ?>
        <nav id="main-menu" role="navigation" tabindex="-1">
          <?php
          // This code snippet is hard to modify. We recommend turning off the
          // "Main menu" on your sub-theme's settings form, deleting this PHP
          // code block, and, instead, using the "Menu block" module.
          // @see https://drupal.org/project/menu_block
          print theme('links__system_main_menu', array(
            'links' => $main_menu,
            'attributes' => array(
              'class' => array('links', 'inline', 'clearfix'),
            ),
            'heading' => array(
              'text' => t('Main menu'),
              'level' => 'h2',
              'class' => array('element-invisible'),
            ),
          )); ?>
        </nav>
      <?php endif; ?>

      <?php print render($page['navigation']); ?>

    </div>

    <?php
      // Render the sidebars to see if there's anything in them.
      $sidebar_first  = render($page['sidebar_first']);
      $sidebar_second = render($page['sidebar_second']);
    ?>

    <?php if ($sidebar_first || $sidebar_second): ?>
      <aside class="sidebars">
        <?php print $sidebar_first; ?>
        <?php print $sidebar_second; ?>
      </aside>
    <?php endif; ?>

  </div>

</div>

<div class="bottom-footer">
  <div class="bottom-footer-container">
    <?php print render($page['footer']); ?>
    <?php print render($page['bottom']); ?>
  </div>
</div>
