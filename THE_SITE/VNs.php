<html>
	<head>
		<title>BLOG</title>
		<link rel="stylesheet" type="text/css" href="mystyle.css">
	</head>
	
	<body>
		<div id ="MAIN">
		<?php
			session_start();
			if ((isset($_SESSION["us"]))){
			}
			else
			{
				header('Location: Blog.php');
			}
			function next_page() {
				$_SESSION["page"]=intval($_GET['page_num']);
			}
			if (isset($_GET['page_num'])) {
				if ($_GET['page_num']<1){
					header('Location: VNs.php?page_num=1');
				}
				next_page();
			}else
				$_SESSION["page"]=1;
			include "menus/menu.php";
			echo 	"<br>";
			$servername = "localhost";
			$username = "root";
			$password = "";
			$i = 0;
			if (!mysql_connect($servername, $username, $password)) {
				//echo 'Could not connect to mysql<br>';
				exit;
			}else{
				//echo 'connected to '.$servername.'<br>';
			}
			mysql_select_db('iosyf') or die('Could not select database');
			$page = ($_SESSION["page"]);
			
			echo "<div id='pages'>";
			$result3 = mysql_query("SELECT COUNT(*) FROM VN;");
			if (!$result3) {
				echo 'Could not run query: 5' . mysql_error();
				exit;
			}
			else{
				$pages_text = "<br>";
				$pages_text .= "<br>";
				$pages_text .= "<div id='all_buttons'>";
				$row = mysql_fetch_array($result3);
				$row[0] = intval((int)$row[0])/10;
				if ($page>ceil($row[0])){
					header('Location: VNs.php?page_num='.ceil($row[0]));
				}
				if ($page<5){
					$page=1;
				}else{
					$page-=4;
				}
				if ($_SESSION["page"]<=5){
					$pages_text .= "<a style='color:orange; text-decoration:none;'><div id='page_button'><</div></a>";
				}else{
					$pages_text .= "<a href='VNs.php?page_num=".($page-5)."' style='color:red; text-decoration:none;'><div id='page_button'><</div></a>";
				}
				if ($_SESSION["page"]==1){
					$pages_text .= "<a style='color:orange; text-decoration:none;'><div id='page_button'><<</div></a>";
				}else{
					$pages_text .= "<a href='VNs.php?page_num=1' style='color:red; text-decoration:none;'><div id='page_button'><<</div></a>";
				}
				for ($counter=1;;$counter+=1, $page++){
					if ($page==$_SESSION["page"]){
						$pages_text .= "<a style='color:orange; text-decoration:none;'><div id='page_button'>".$page."</div></a>";
						$page_num=$page;
					}else{
						if($page>ceil($row[0])){
							$pages_text .= "<a style='color:orange; text-decoration:none;'><div id='page_button'>".$page."</div></a>";
						}else{
							$pages_text .= "<a href='VNs.php?page_num=".$page."' style='color:red; text-decoration:none;'><div id='page_button'>".$page."</div></a>";
						}
					}
					if (($counter>=5)){
						break;
					}
				}
				if ($_SESSION["page"]==ceil($row[0])){
					$pages_text .= "<a style='color:orange; text-decoration:none;'><div id='page_button'>>></div></a>";
				}else{
					$pages_text .= "<a href='VNs.php?page_num=".($page_num+5)."' style='color:red; text-decoration:none;'><div id='page_button'>>></div></a>";
				}
				if ($_SESSION["page"]<=ceil($row[0])){
					$pages_text .= "<a style='color:orange; text-decoration:none;'><div id='page_button'>></div></a>";
				}else{
					$pages_text .= "<a href='VNs.php?page_num=".ceil($row[0])."' style='color:red; text-decoration:none;'><div id='page_button'>></div></a>";
				}
				
				$pages_text .= "</div>";
				echo $pages_text;
			}
			$page = ($_SESSION["page"]);
			$result = mysql_query("SELECT UID,name,description FROM VN ORDER BY UID DESC LIMIT ".(($page-1)*10).",10");// VERY IMPORTANT
			if (!$result) {
				echo 'Could not run query: 1' . mysql_error();
				exit;
			}
			else{
				echo"<br>";
				echo"<br>";
				while($row = mysql_fetch_array($result)){
					echo "<br>";
					echo "<div id = 'box'>";
					echo "<div id = 'box2'>";
					echo $row['name'];
					echo "</div>";
					echo "<a href='VN/".$row['UID']."'><img src = 'VN/".$row['UID']."/resources/thumbnail.png'></a>";
					echo "<div id = box3>";
					$id=$row['UID'];
					$result2 = mysql_query("SELECT name,IDVN
					FROM vnxtags,tags
					WHERE IDVN='$id' AND UID=IDtags");// VERY IMPORTANT
					if (!$result2) {
						echo 'Could not run query: 2' . mysql_error();
						exit;
					}
					else{
						echo "TAGS:";
						while($row2 = mysql_fetch_array($result2)){
							echo " <a href>".$row2['name']."</a>";
						}
						echo"\n\n";
					}
					
					echo "ARTISTS: ";
					$result2 = mysql_query("SELECT username 
					FROM users,makers_of_the_vn
					WHERE IDVN='$id' AND users.UID=IDusers");// VERY IMPORTANT
					if (!$result2) {
						echo 'Could not run query: 3' . mysql_error();
						exit;
					}
					else{
						while($row2 = mysql_fetch_array($result2)){
							echo " <a href>".$row2['username']."</a>";
						}
						echo"\n\n";
					}
					
					echo "LANGUAGE: ";
					$result2 = mysql_query("SELECT name 
					FROM languages,vnxlanguages
					WHERE IDVN='$id' AND languages.UID=IDlanguages");// VERY IMPORTANT
					if (!$result2) {
						echo 'Could not run query: 4' . mysql_error();
						exit;
					}
					else{
						while($row2 = mysql_fetch_array($result2)){
							echo " <a href>".$row2['name']."</a>";
						}
						echo"\n\n";
					}
					
					echo "DESCRIPTION: ".$row['description'];
					echo "</div>";
					echo "</div>";
				}
			}
			
			echo $pages_text;
			echo "</div>";
			echo '<div id="go_to">';
			echo '<input id="go_to_val" type="text" value="'.ceil($row[0]).'" onkeydown="if (event.keyCode == 13) document.getElementById(\'go_to_button\').click()"/></input>';
			echo '<input id="go_to_button" type="button" value="Go" onclick="go_to_page()"></input>';
			echo '</div>';
			mysql_free_result($result);
		?>
		<br>
		</div>
	</body>
</html>
<script>
	function setColor(element, color){
		element.style.backgroundColor = color;
	}
	function IsNumeric(input)
	{
		return (input - 0) == input && (''+input).trim().length > 0;
	}
	function go_to_page(){
		num = document.getElementById("go_to_val").value;
		if (!IsNumeric(num)) {
			setColor(document.getElementById("go_to_val"), "red");
			return;
		}else{
			setColor(document.getElementById("go_to_val"), "white");
		}
		window.location.href = "VNs.php?page_num="+num;
	}
</script>
