<?php
const FARMER_LIMIT = 15;
const COW_LIMIT = 10; 
const BUNNY_LIMIT = 8;
const COUNT_LIMIT = 50;
/**
 * Avadol Game Class 
 * set the history of recent fed element in the game
 * remove the element from fed list as per rule sets
 * set the game status as per rules
 */
class Avadol {
  private $is_famer_alive = true;
  private $current_turn = 0;
  private $current_fed ="";
  private $recent_feds = [];
  public $fed_details,$elemet_died = [];
  public $flash_message, $unset_cow, $unset_bunny = "";
  public $is_game_over = false;
  public $elements = ['farmer','cow1','cow2','bunny1','bunny2','bunny3','bunny4'];
  public function __construct(){
    //default elements will take from class declaration and store in session
    if (!isset($_SESSION['fed_details']['elements'])) {
      $_SESSION['fed_details']['elements'] = $this->elements;
      $_SESSION['fed_details']['turn'] = $this->current_turn;
    }else {
      $this->elements = $_SESSION['fed_details']['elements'];
      $this->current_turn = (int) $_SESSION['fed_details']['turn'];
      $this->fed_details = $_SESSION['fed_details']['fedding'];
    }
    if(isset($_SESSION['fed_details']['died'])){
      $this->elemet_died = $_SESSION['fed_details']['died'];
    }
  }
  /**
   * fed randomly to game elements set the details for next transaction process
   * @return boolean TRUE | FALSE
   */
  public function fedRandomly(){    
    $random_fed = array_rand($this->elements,1);
    $this->current_fed = $this->elements[$random_fed];
    $this->current_turn++;
    $_SESSION['fed_details']['turn'] = $this->current_turn;
    $_SESSION['fed_details']['fedding'][] = array('turn'=>$this->current_turn,$this->current_fed=>1);
    $_SESSION['fed_details']['fed_to'][] = $this->current_fed;    
    if($this->validateElements()){
      if($this->current_turn>=COUNT_LIMIT){
        $this->flash_message = 'Fed count is reach to its limit!!!';
        $this->is_game_over = true;
        return FALSE;
      }
    }
    return TRUE;
  }
  /**
   * set the game rules as per specification
   * check each elements of game is alive as per game rule
   * @return boolean TRUE|FALSE
   */
  private function validateElements(){
    if (!$this->isFarmerAlive()) {
      $this->flash_message = 'Farmer is died!!!';
      $this->is_game_over = true;
      return FALSE;
    }
    if(!$this->isCowFed()){
      $this->flash_message = $this->unset_cow.' is died!!!';
      return FALSE;
    }
    if (!$this->isBunnyFed()) {
      $this->flash_message = $this->unset_bunny.' is died!!!';
      return FALSE;
    }
    return true;
  }
  /**
   * farmer needs to be fed at least once every 15 turns.
   * if farmer doesnt fed in recent 15 turn then return false
   * @return boolean true|false
   */
  private function isFarmerAlive(){
    if (count($_SESSION['fed_details']['fed_to'])>FARMER_LIMIT) {
      $farmer_feds = $this->getRecentFed(FARMER_LIMIT);
      $farmer_key = array_search('farmer',$farmer_feds);
      $this->is_famer_alive  = $farmer_key ? true:false;
      unset($this->elements[$farmer_key]);
      $_SESSION['fed_details']['elements'] = $this->elements;
    }
    return $this->is_famer_alive;
  } 
  /**
   * check for cow to fed
   * if cow doen't fed recent 10 turns then remove respective cow from the fed list
   * @return boolean True|FALSE
   */
  private function isCowFed(){
    $cow_array = ['cow1'=>'Cow 1','cow2'=>'Cow 2'];
    if (count($_SESSION['fed_details']['fed_to'])>COW_LIMIT) {
      $cow_feds = $this->getRecentFed(COW_LIMIT);
      foreach ($cow_array as $key => $cow) {
        if (!in_array($key,$cow_feds) && in_array($key,$this->elements)) {
          $unset_key = array_search($key,$this->elements);
          $this->unset_cow = $cow;
          unset($this->elements[$unset_key]);
          $_SESSION['fed_details']['died'][$key] = 1;
          $_SESSION['fed_details']['elements'] = $this->elements;
          return false;
        }
      }
    }
    return true;
  }
  /**
   * check bunny is fed in recent turns
   * if bunny is not fed in recent 8 turn then remove bunny from fed list 
   * @return boolean true|false
   */
  private function isBunnyFed(){
    $bunny_array = ['bunny1'=>'bunny 1','bunny2'=>'bunny 2','bunny3'=>'bunny 3','bunny4'=>'bunny 4'];
    if (count($_SESSION['fed_details']['fed_to'])>BUNNY_LIMIT) {
      $bunny_feds = $this->getRecentFed(BUNNY_LIMIT);
      foreach ($bunny_array as $key => $bunny) {
        if (!in_array($key,$bunny_feds) && in_array($key,$this->elements)) {
          $unset_key = array_search($key,$this->elements);
          unset($this->elements[$unset_key]);
          $_SESSION['fed_details']['died'][$key] = 1;
          $this->unset_bunny = $bunny;
          $_SESSION['fed_details']['elements'] = $this->elements;        
          return false;
        }
      }
    }
    return true;
  }
  /**
   * Fetch the recent fed list based on limit provided
   * @param integer $limit
   * @return array feedlist
   */
  private function getRecentFed(int $limit){
    if (!empty($_SESSION['fed_details']['fed_to'])){
      $this->recent_feds = array_slice($_SESSION['fed_details']['fed_to'],-$limit,$limit,true);      
    }
    return $this->recent_feds;
  }

}
