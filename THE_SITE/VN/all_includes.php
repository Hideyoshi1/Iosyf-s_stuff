
<?php
	//<script src="../../jquery-1.11.2.js"></script>
	//include "style/mystyle.css";
	
	if (!include "../styles.html")
	{
		echo"";
	}
	include "../compile.php"; 
	include "../../menus/menu3.php"; 
	include "../all.html"; 
	include "../restofit.html";
	
	if (file_exists('style/mystyle.css')) {
		include 'style/mystyle.css';
	}
	//if the file exists include
?>

