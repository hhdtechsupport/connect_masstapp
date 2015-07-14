<?php

/**
 * @class
 * Contains the CerFieldCollectionHandler object.
 */
 
class CerFieldCollectionHandler extends CerFieldHandler {

  public function current() {
    return field_collection_item_load($this->items[$this->delta]['value']);
  }

  public function contains($collection) {
    foreach ($this->items as $item) {
      if ($item['value'] == $collection->item_id) {
        return TRUE;
      }
    }
    return FALSE;
  }

  public function add($collection) {
    if ($this->validate($collection)) {
      $this->items[] = array(
        'value' => $collection->item_id,
        'revision_id' => $collection->revision_id,
      );
      $this->write();
    }
  }

  public function delete($collection) {
    foreach ($this->items as $delta => $item) {
      if ($item['value'] == $collection->item_id) {
        unset($this->items[$delta]);
      }
    }
    $this->write();
  }

}
