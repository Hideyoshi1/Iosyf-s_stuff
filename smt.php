<?php
  session_start();
  $myfile = fopen($S.'.txt', "r") or die("Unable to open file!");
  if (1){
    while {$buff = fgetc($myfile,"r")}
      echo '<table>'; //use table style from before
      echo '<tr>';
      echo '<td>';
      if ($buff == '\n')
      {
        echo '</td>';
        echo '</tr>';
        echo '</table><table>'; //use table style from before
        echo '<tr>';
        echo '<td>';
      }
      echo $buff;
  }
  echo 
?>
