<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
 #print_r($node);
?>

<?php /*?><div id="wrap">

  <header id="header" class="clearfix" role="banner">
<?php
       echo l(t('Login'), 'user', array('attributes' => array('class' => array('about-link'))));
       ?>
    <div>
    
      <?php if ($logo): ?>
       <div id="logo">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
        </div>
      <?php endif; ?>
      <hgroup id="sitename">
        <h2><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php //print $site_name; ?></a></h2>
        <p><?php if ($site_slogan): ?><?php print $site_slogan; ?><?php endif; ?></p><!--site slogan-->
      </hgroup>
      
    </div>
    <nav id="navigation" class="clearfix" role="navigation">
      <div id="main-menu">
        <?php 
			
		  if (module_exists('i18n')) {
            $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
          } else {
            $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
          }
          print drupal_render($main_menu_tree);
        ?>
      </div>
    </nav><!-- end main-menu -->
  </header><?php */?>
  <!--Header Start--> 
  <div id="header-outer">
  <header id="header-inn" class="clearfix" role="banner">
    <div class="topmain-a">
      <?php if ($logo): ?>
      <div class="logo"> <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a> </div>
      <?php endif; ?>
     <div class="search-box">   
      <div class="login">
        <?php
      echo l(t('Login'), 'user', array('attributes' => array('class' => array('about-link'))));
       ?>
      </div>
      <div class="clear"></div>
      <div class="top-search">
        <?php print render(drupal_get_form('search_block_form')); ?>
      </div>
     </div>
      
    </div>
  </header>
  <div id="nav-bar">
    <div id="nav-bar-inn">
      <nav id="navigation" class="clearfix" role="navigation">
        <div id="main-menu">
          <?php 
          if (module_exists('i18n')) {
            $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
          } else {
            $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
          }
          print drupal_render($main_menu_tree);
        ?>
        </div>
      </nav>
    </div>
  </div>
</div>
<!--Header End-->   
  <?php print render($page['header']); ?>

  <?php print render($page['secondary_content']); ?>

  <div id="container">
  <div id="container-inn">
  <div id="container-sub">
  <div class="main-content">
  <?php
      $link_title = variable_get('link_title');
      
      $tree = menu_tree_all_data('menu-primary-links');
      foreach ($tree as $branch){
          if ($branch['link']['title'] == $link_title){
            $childtree = $branch['below'];
            break;
          }
        }      
    
    ?>
    <?php if ($page['content_top']): ?><div id="content_top"><?php print render($page['content_top']); ?></div><?php endif; ?>
    <?php print render($title_prefix); ?>
    <?php if ($title): ?><h1 class="page-title"><?php print $title; ?></h1><?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php if ($page['sidebar_first'] || $childtree!=""):?>
    <div class="sub-content">
    <?php endif;?>   
    <div <?php if ($page['sidebar_first'] || $childtree!=""):?>class="ctn-left" <?php else:?> class="ctn-full" <?php endif;?>>
    <?php print $messages; ?>
    
    <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper clearfix"><?php print render($tabs); ?></div><?php endif; ?>
    <?php print render($page['help']); ?>
    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
    <?php print render($page['content']); ?>
    </div>
    <?php if ($page['sidebar_first'] || $childtree!=""):?>
    <div class="ctn-right">    
    <?php print render($page['sidebar_first']); ?>
    </div>
    <?php if ($page['sidebar_first'] || $childtree!=""):?>
      </div>
     <?php endif;?>
    <?php endif;?>
  </div>  
   <!-- 
    <section id="post-content" role="main">
    
  </section>  -->
  
  
   
  
  
  </div>
  <div class="search"><?php print render($page['footer']) ?></div>    
  </div></div>
  <?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third'] || $page['footer_fourth']): ?>
    <div id="footer-saran" class="clearfix">
     <div id="footer-wrap">
      <?php if ($page['footer_first']): ?>
      <div class="footer-box"><?php print render($page['footer_first']); ?></div>
      <?php endif; ?>
      <?php if ($page['footer_second']): ?>
      <div class="footer-box"><?php print render($page['footer_second']); ?></div>
      <?php endif; ?>
      <?php if ($page['footer_third']): ?>
      <div class="footer-box"><?php print render($page['footer_third']); ?></div>
      <?php endif; ?>
      <?php if ($page['footer_fourth']): ?>
      <div class="footer-box remove-margin"><?php print render($page['footer_fourth']); ?></div>
      <?php endif; ?>
     </div>
    </div>
    <div class="clear"></div>
  <?php endif; ?>
  
  <!--END footer -->
<div id="copyright">
  <div id="copyright-inn"> 
  <?php
      echo l(t('Home'), '', array('attributes' => array('class' => array('about-link'))));
       ?>/
      <?php
      echo l(t('About Us'), 'about-us', array('attributes' => array('class' => array('about-link'))));
       ?> /
       <?php
      echo l(t('Prevention in MA '), 'prevention-ma', array('attributes' => array('class' => array('about-link'))));
       ?> /
       <?php
      echo l(t('Prevention Tools '), 'prevention-tools', array('attributes' => array('class' => array('about-link'))));
       ?>/
        <?php
      echo l(t('Resource Library '), 'resource-library', array('attributes' => array('class' => array('about-link'))));
       ?>/
        <?php
      echo l(t('Funding Opportunities'), 'funding-opportunities', array('attributes' => array('class' => array('about-link'))));
       ?>/
        <?php
      echo l(t('Events '), 'events', array('attributes' => array('class' => array('about-link'))));
       ?><br/>
  <div class="edclogo" ><?php print render($page['footerlogo']); ?></div>
  <div class="edcaddress" ><?php print render($page['footeraddress']); ?></div>
  </div>
  
</div>
