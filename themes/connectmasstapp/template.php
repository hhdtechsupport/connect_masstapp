<?php
/**
 * Implements hook_html_head_alter().
 * This will overwrite the default meta character type tag with HTML5 version.
 */
function connectmasstapp_html_head_alter(&$head_elements) {
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8'
  );
}

/**
 * Insert themed breadcrumb page navigation at top of the node content.
 */
function connectmasstapp_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  //print_r($breadcrumb);
  $breadcrumb[] = drupal_get_title();

   if (arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
    $breadcrumb = array();
    $breadcrumb[] = l(t('Home'), '<front>');
    $breadcrumb[] = l(t('Resource Library'), 'resource-library/all');

    $tid = arg(2);

    if ($term = taxonomy_term_load($tid)) {
      $uri = entity_uri('taxonomy_term', $term);
      $breadcrumb[] = l($term->name, $uri['path'], $uri['options']);
    }
  }


   if (arg(0) == 'search') {
    unset($breadcrumb[1]); unset($breadcrumb[2]);
   }

   if (arg(0) == 'connectmasstapp-archives' || arg(0) == 'upcoming-events') {
    unset($breadcrumb[3]);
   }
   if (arg(0) == 'resource-library' && arg(1) == 'all') {
    $breadcrumb[2]="All";
   }


  if (count($breadcrumb) > 0) {
     $lastitem = sizeof($breadcrumb);
     $title = drupal_get_title();
     $crumbs = '<ul class="breadcrumbs">';
     $a=0;
     foreach($breadcrumb as $value) {
     $a++;
         if ($a!=$lastitem){
          $crumbs .= '<li>'. $value . ' ' . '</li>';
         }
         else{
              $crumbs .= '<li class="current"><a href="javascript:void(0);">'.ucwords($value).'</a></li>';
         }

     }
     $crumbs .= '</ul>';
   return $crumbs;
   }
   else {
     return t("Home");
   }

}

/**
 * Override or insert variables into the html template.
 */
 //add body classes based on url
function connectmasstapp_preprocess_html(&$vars) {
     $path = drupal_get_path_alias($_GET['q']);
     $aliases = explode('/', $path);

  foreach($aliases as $alias) {
    $vars['classes_array'][] = drupal_clean_css_identifier($alias);
  }
}

function connectmasstapp_process_html(&$vars) {
  // Hook into color.module
  if (module_exists('color')) {
    _color_html_alter($vars);
  }
 }
/**
 * Override or insert variables into the page template.
 */
function connectmasstapp_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
 * Override or insert variables into the page template.
 */
function connectmasstapp_preprocess_page(&$vars) {
  if (isset($vars['node'])) {
    $node = $vars['node'];
  }
  else {
    $node = (object) array('type' => '_none');
  }

  variable_del('link_title');
  if ($node->type=='staff_member') {
    variable_set('link_title','About Us');
  }
  else if($node->type=='grantee') {
    variable_set('link_title','Prevention in MA');
  }
  else if($node->type=='resource_library') {
    variable_set('link_title','Prevention Tools');
  }
  else if($node->type=='event') {
    variable_set('link_title','Events');
  }
  else {
    $menuParent = menu_get_active_trail();
    $link_title = isset($menuParent[1]['link_title']) ? $menuParent[1]['link_title'] : t('Unknown');
    variable_set('link_title',$link_title);
  }

  if (isset($vars['main_menu'])) {
    $vars['main_menu'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('links', 'main-menu', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['main_menu'] = FALSE;
  }
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_menu'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('links', 'secondary-menu', 'clearfix'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['secondary_menu'] = FALSE;
  }
  // use tpl php for prevention planning pages
  if (isset($node)) {
    if ($node->type == 'prevention_planning_page' || $node->type == 'prevention_planning_step' || $node->type == 'prevention_planning_task' || $node->type == 'prevention_planning_tool') {
      $vars['theme_hook_suggestion'] = 'page__prevention_planning';
    }
  }
}

/**
 * Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
 */
function connectmasstapp_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="tabs primary clearfix">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="tabs secondary clearfix">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }
  return $output;
}

/**
 * Override or insert variables into the node template.
 */
function connectmasstapp_preprocess_node(&$variables) {
  unset($variables['content']['links']['node']);

  $node = $variables['node'];

  //$block = module_invoke('block', 'block_view', '2');
   //print_r($variables['teaser']);

  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
}

function connectmasstapp_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id = 'webform_client_form_151') {
      $form['actions']['submit']['#attributes']['class'][] = 'webform-submit';
  }

  if ($form_id == 'user-register-form') {
  }

  if (isset($form_state['view']) && $form_state['view']->name == 'upcoming_events') {
    $form['field_in_person_meeting_webinar_value']['#options']['All'] = t('All');
  }

/*
  if ($form_id == 'search_block_form') {
    $form['search_block_form']['#value'] = 'Search by Topic';
    $form['search_block_form']['#attributes']['onblur'] = "if (this.value == '') {this.value = 'Search by Topic';}";
    $form['search_block_form']['#attributes']['onfocus'] = "if (this.value == 'Search by Topic') {this.value = '';}";
  }
  */
}

/**
 * Add javascript files for front-page jquery slideshow.
 */
 /* Removed by Nancy. 
if (drupal_is_front_page()) {
  drupal_add_js(drupal_get_path('theme', 'connectmasstapp') . '/js/sliding_effect.js');

  // Get Home Banners
  $homebanners = '';
  $nodes = node_load_multiple(array(), array('type' => 'home_page_banners'));

  foreach ($nodes as $key=>$val) {
    $uri = $nodes[$key]->field_image[und][0]['uri'];
    $url_image = url(variable_get('file_directory_path', conf_path() .'/files/').file_uri_target($uri), array('absolute'=>true));
    $homebanners.='<img src="'.$url_image.'"/>';
  }
  variable_set('homebanners',$homebanners);
} */

// Add JS to create classes for Overview boxes
function connectmasstapp_preprocess_views_view(&$vars) {
  if (isset($vars['view'])) {
    $view = $vars['view'];
    if ($view->name == 'guidance_for_prevention_planning' || $view->name == 'moapc_planning_tool') {
      drupal_add_js(drupal_get_path('theme', 'connectmasstapp') . '/js/steps.js');
    }
  }
}
?>
