<?php

/**
 * @file
 * Contains the CerFieldCollectionField object.
 */

class CerFieldCollectionField extends CerField {

  public function getHandler($entity) {
    return new CerFieldCollectionHandler($this, $entity);
  }

  public function getTargetType() {
    return 'field_collection_item';
  }

  public function createInnerEntity($owner) {
    $collection = entity_create('field_collection_item', array(
      'field_name' => $this->field,
    ));
    $collection->setHostEntity($this->entityType, $owner, entity_language($this->entityType, $owner), FALSE);
    $collection->save(TRUE);

    $this->getHandler($owner)->add($collection);

    return $collection;
  }

}
