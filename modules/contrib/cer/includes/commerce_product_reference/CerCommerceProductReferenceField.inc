<?php

/**
 * @file
 * Contains the CerCommerceProductReferenceField object.
 */
 
class CerCommerceProductReferenceField extends CerField {

  public function getHandler($entity) {
    return new CerCommerceProductReferenceHandler($this, $entity);
  }

  public function getTargetType() {
    return 'commerce_product';
  }

  public function getTargetBundles() {
    $types = $this->instanceInfo('settings', 'referenceable_types');
    return ($types ? $types : parent::getTargetBundles());
  }

}
 