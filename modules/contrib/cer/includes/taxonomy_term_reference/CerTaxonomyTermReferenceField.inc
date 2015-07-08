<?php

/**
 * @file
 * Contains the CerTaxonomyTermReferenceField object.
 */
 
class CerTaxonomyTermReferenceField extends CerField {

  public function getHandler($entity) {
    return new CerTaxonomyTermReferenceHandler($this, $entity);
  }

  public function getTargetType() {
    return 'taxonomy_term';
  }
  
  public function getTargetBundles() {
    $bundles = array();

    foreach ($this->fieldInfo('settings', 'allowed_values') as $item) {
      $bundles[] = $item['vocabulary'];
    }

    return $bundles;
  }

}
