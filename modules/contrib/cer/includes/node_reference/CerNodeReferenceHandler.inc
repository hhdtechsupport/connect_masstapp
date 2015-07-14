<?php

/**
 * @file
 * Contains the CerNodeReferenceHandler object.
 */
 
class CerNodeReferenceHandler extends CerFieldHandler {

  public function current() {
    return node_load($this->items[$this->delta]['nid']);
  }
  
  protected function validate($node) {
    if (parent::validate($node)) {
      $options = array(
        'ids' => array(
          $node->nid,
        ),
      );

      if (array_key_exists($node->nid, node_reference_potential_references($this->field->fieldInfo(), $options))) {
        return TRUE;
      }
      else {
        $this->logError('Cannot reference !that_link from !field_label on !this_link (disallowed by Node Reference).', $node);
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }

  public function contains($node) {
    foreach ($this->items as $item) {
      if ($item['nid'] == $node->nid) {
        return TRUE;
      }
    }
    return FALSE;
  }
  
  public function add($node) {
    if ($this->validate($entity)) {
      $this->items[] = array('nid' => $node->nid);
      $this->write();
    }
  }
  
  public function delete($node) {
    foreach ($this->items as $delta => $item) {
      if ($item['nid'] == $node->nid) {
        unset($this->items[$delta]);
      }
    }
    $this->write();
  }

}
