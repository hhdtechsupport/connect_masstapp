<?php

/**
 * @file
 * Contains the CerUserReferenceField object.
 */
 
class CerUserReferenceField extends CerField {
  
  public function getHandler($entity) {
    return new CerUserReferenceHandler($this, $entity);
  }

  public function getTargetType() {
    return 'user';
  }

}
 