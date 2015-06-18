<?php
  if (isset($_Get["pname"])){
  	$Pass=password_hash($_Get["pname"], PASSWORD_BCRYPT);
  	echo $Pass;
  }else{
    echo "Use pname as a variable in the url example: http://localhost/THE_SITE/VNs.php?pname=2";
  }
?>
