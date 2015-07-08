<?php

/**
 * @file
 * Contains the CerNodeReferenceField object.
 */
 
class CerNodeReferenceField extends CerField {
  
  public function getHandler($entity) {
    return new CerNodeReferenceHandler($this, $entity);
  }
  
  public function getTargetType() {
    return 'node';
  }

  public function getTargetBundles() {
    $bundles = array();

    $view = $this->fieldInfo('settings', 'view', 'view_name');
    if ($view) {
      $view = views_get_view($view);
      $view->set_display($this->fieldInfo('settings', 'view', 'view_display'));
      
      $bundle_key = $this->entityInfo('entity keys', 'bundle');
      if ($bundle_key && $handler = $view->display_handler->get_handler('filter', $bundle_key)) {
        $bundles = $handler->value;
      }
    }
    else {
      $bundles = $this->fieldInfo('settings', 'referenceable_types');
    }

    return ($bundles ? $bundles : parent::getTargetBundles());
  }

}
 