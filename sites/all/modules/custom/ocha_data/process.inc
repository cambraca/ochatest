<?php

function _ocha_data_process_simple_table($data, $key, $id_field) {
  return array_reduce($data[$key], function($carry, $item) use ($id_field) {
    $carry[$item[$id_field]] = $item;
    unset($carry[$item[$id_field]][$id_field]);
    return $carry;
  }, []);
}
