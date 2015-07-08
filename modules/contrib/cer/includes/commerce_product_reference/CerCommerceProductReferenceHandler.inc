<?php

/**
 * @file
 * Contains the CerCommerceProductReferenceHandler object.
 */
 
class CerCommerceProductReferenceHandler extends CerFieldHandler {

  public function current() {
    return commerce_product_load($this->items[$this->delta]['product_id']);
  }

  protected function validate($product) {
    if (parent::validate($product)) {
      $matched = commerce_product_match_products($this->field->fieldInfo(), $this->field->instanceInfo(), '', 'contains', array($product->product_id), 0);

      if (array_key_exists($product->product_id, $matched)) {
        return TRUE;
      }
      else {
        $this->logError('Cannot reference !that_type !that_label from !field_label on !this_link (disallowed by Commerce Product Reference).', $product);
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }

  public function contains($product) {
    foreach ($this->items as $item) {
      if ($item['product_id'] == $product->product_id) {
        return TRUE;
      }
    }
    return FALSE;
  }

  public function add($product) {
    if ($this->validate($product)) {
      $this->items[] = array('product_id' => $product->product_id);
      $this->write();
    }
  }

  public function delete($product) {
    foreach ($this->items as $delta => $item) {
      if ($item['product_id'] == $product->product_id) {
        unset($this->items[$delta]);
      }
    }
    $this->write();
  }

}
