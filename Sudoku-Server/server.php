<?php
$difficulty = $_REQUEST['difficulty'];

if (file_exists($difficulty . '.txt')) {
	$grid = file_get_contents($difficulty . '.txt');
	unlink($difficulty . '.txt');
	echo $grid;
	shell_exec('server ' . $difficulty);
} else {
	shell_exec('server ' . $difficulty);
	$grid = file_get_contents($difficulty . '.txt');
	unlink($difficulty . '.txt');
	echo $grid;
	shell_exec('server ' . $difficulty);
}
?>