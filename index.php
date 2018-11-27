<?php
// ini_set('display_errors',1);
// error_reporting(E_ALL);
session_start();
include_once('class.avadol.inc');
include_once('game_logic.php');
?>
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8" />
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <title>AVADOL Farm Game</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <!-- Latest compiled and minified CSS -->
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
  <link rel="stylesheet" href="css/style.css">
  <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
  <!-- Latest compiled and minified JavaScript -->
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
</head>
<body>
<div class="container">
  <?php if(isset($flash_message)):?>
  <div class="alert alert-danger alert-dismissible">
    <a href="#" class="close" data-dismiss="alert" aria-label="close">&times;</a>
    <?php print $flash_message;?>
  </div>
  <?php endif; ?>
  <form action="<?php print $_SERVER['PHP_SELF'];?>" method="post">
    <div class="">
      <button type="submit" class="btn btn-primary" name="btn_fed" value="1" <?php print !empty($is_game_over)? 'disabled':''; ?> >Click to Fed</button> 
      <button type="submit" class="btn btn-secondary" name="btn_reset" value="1">Reset Game</button>
    </div> 
  </form>
  <p> Fed Details </p>
  <div class="table-responsive">
    <table class="table table-hover table-bordered">
      <thead>
        <tr>
          <th>Round</th>
          <th class="<?php print isset($farmer)? 'bg-primary text-white': ''?>">Famer</th>
          <th class="<?php print isset($cow1)? 'bg-secondary text-white': ''?>">Cow 1</th>
          <th class="<?php print isset($cow2)? 'bg-danger text-white': ''?>">Cow 2</th>
          <th class="<?php print isset($bunny1)? 'bg-warning text-white': ''?>">Bunny 1</th>
          <th class="<?php print isset($bunny2)? 'bg-info text-white': ''?>">Bunny 2</th>
          <th class="<?php print isset($bunny3)? 'bg-success text-white': ''?>">Bunny 3</th>
          <th class="<?php print isset($bunny4)? 'bg-dark text-white': ''?>">Bunny 4</th>
        </tr>
      </thead>
      <tbody>
        <?php foreach ($round as $key =>$element):?>
          <tr>
            <td><?php echo $element['turn'];?></td>
            <td class="<?php print isset($farmer)? 'bg-primary text-white': ''?>"><?php echo (isset($element['farmer'])) ?? null; ?></td>
            <td class="<?php print isset($cow1)? 'bg-secondary text-white': ''?>"><?php echo (isset($element['cow1'])) ?? null; ?></td>
            <td class="<?php print isset($cow2)? 'bg-danger text-white': ''?>"><?php echo (isset($element['cow2'])) ?? null; ?></td>
            <td class="<?php print isset($bunny1)? 'bg-warning text-white': ''?>"><?php echo (isset($element['bunny1'])) ?? null; ?></td>
            <td class="<?php print isset($bunny2)? 'bg-info text-white': ''?>"><?php echo (isset($element['bunny2'])) ?? null; ?></td>
            <td class="<?php print isset($bunny3)? 'bg-success text-white': ''?>"><?php echo (isset($element['bunny3'])) ?? null; ?></td>
            <td class="<?php print isset($bunny4)? 'bg-dark text-white': ''?>"><?php echo (isset($element['bunny4'])) ?? null; ?></td>
          </tr>
        <?php endforeach;?>
      </tbody>
    </table>
  </div>
</div> 
</body>
</html>