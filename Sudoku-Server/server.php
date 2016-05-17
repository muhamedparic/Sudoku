<?php
$difficulty = $_REQUEST['difficulty'];

$grid = file_get_contents($difficulty . '.txt');
unlink($difficulty . '.txt');
echo $grid;
shell_exec('./server ' . $difficulty);
?>