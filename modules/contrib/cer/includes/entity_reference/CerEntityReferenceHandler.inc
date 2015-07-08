<?php

/**
 * @file
 *  Contains the CerEntityReferenceHandler object.
 */

/**
 * @class
 *  Implements CerFieldHandler for Entity Reference fields.
 */
class CerEntityReferenceHandler extends CerFieldHandler {

  public function current() {
    $id = $this->items[$this->delta]['target_id'];

    $entities = entity_load($this->field->getTargetType(), (array) $id);
    return $entities[$id];
  }

  /**
   * Gets the ID of a referenceable entity.
   *
   * @return integer
   */
  protected function getEntityID($entity) {
    list($id, ,) = entity_extract_IDs($this->field->getTargetType(), $entity);
    return $id;
  }

  protected function validate($entity) {
    if (parent::validate($entity)) {
      $entityID = $this->getEntityID($entity);

      $handler = entityreference_get_selection_handler($this->field->fieldInfo(), $this->field->instanceInfo(), $this->field->instanceInfo('entity_type'), $this->entity);

      if (in_array($entityID, $handler->validateReferencableEntities((array) $entityID))) {
        return TRUE;
      }
      else {
        $this->logError('Cannot reference !that_link from !field_label on !this_link (disallowed by Entity Reference).', $entity);
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }

  public function contains($entity) {
    try {
      $entityID = $this->getEntityID($entity);

      foreach ($this->items as $item) {
        if ($item['target_id'] == $entityID) {
          return TRUE;
        }
      }
      return FALSE;
    }
    catch (EntityMalformedException $e) {
      return FALSE;
    }
  }

  public function add($entity) {
    if ($this->validate($entity)) {
      $this->items[] = array('target_id' => $this->getEntityID($entity));
      $this->write();
    }
  }

  public function delete($entity) {
    $entityID = $this->getEntityID($entity);

    foreach ($this->items as $delta => $item) {
      if ($item['target_id'] == $entityID) {
        unset($this->items[$delta]);
      }
    }
    $this->write();
  }

}
