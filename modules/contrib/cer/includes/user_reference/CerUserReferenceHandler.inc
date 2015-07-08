<?php

/**
 * @file
 * Contains the CerUserReferenceHandler object.
 */
 
class CerUserReferenceHandler extends CerFieldHandler {

  public function current() {
    return user_load($this->items[$this->delta]['uid']);
  }

  protected function validate($account) {
    if (parent::validate($account)) {
      $options = array(
        'ids' => array(
          $account->uid,
        ),
      );
      
      if (array_key_exists($account->uid, user_reference_potential_references($this->field->fieldInfo(), $options))) {
        return TRUE;
      }
      else {
        $this->logError('Cannot reference !that_type !that_label from !field_label on !this_link (disallowed by User Reference).', $account);
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }

  public function contains($account) {
    foreach ($this->items as $item) {
      if ($item['uid'] == $account->uid) {
        return TRUE;
      }
    }
    return FALSE;
  }

  public function add($account) {
    if ($this->validate($account)) {
      $this->items[] = array('uid' => $account->uid);
      $this->write();
    }
  }

  public function delete($account) {
    foreach ($this->items as $delta => $item) {
      if ($item['uid'] == $account->uid) {
        unset($this->items[$delta]);
      }
    }
    $this->write();
  }

}
