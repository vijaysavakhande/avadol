<?php
$round = [];
//check is fed button is pressed
if (isset($_POST['btn_fed'])) {
  $avadol = new Avadol();
  $avadol->fedRandomly();
  $round = $avadol->fed_details;
  $flash_message = ($avadol->flash_message) ?? null;
  $is_game_over = $avadol->is_game_over;
  $dead_elements = !empty($avadol->elemet_died)? $avadol->elemet_died :  null;
  if(isset($dead_elements)){
    extract($dead_elements);
  }
}
//check is reset button is pressed
if (isset($_POST['btn_reset'])) {
  session_destroy();
}