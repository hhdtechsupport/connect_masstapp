<?php

/**
 * @file
 *  Contains the CerTaxonomyTermReferenceHandler object.
 */

/**
 * @class
 *  Implements CerFieldHandler for Taxonomy Term Reference fields.
 */
class CerTaxonomyTermReferenceHandler extends CerFieldHandler {

  public function current() {
    return taxonomy_term_load($this->items[$this->delta]['tid']);
  }

  public function contains($term) {
    foreach ($this->items as $item) {
      if ($item['tid'] == $term->tid) {
        return TRUE;
      }
    }
    return FALSE;
  }

  public function add($term) {
    if ($this->validate($term)) {
      $this->items[] = array('tid' => $term->tid);
      $this->write();
    }
  }

  public function delete($term) {
    foreach ($this->items as $delta => $item) {
      if ($item['tid'] == $term->tid) {
        unset($this->items[$delta]);
      }
    }
    $this->write();
  }

}
