<?php

$infinity = 1000000000;
$scores_saved = 10;

if (!file_exists('highscores.txt')) {
	$fout = fopen('highscores.txt', 'w');

	for ($i = 0; $i < 5 * $scores_saved; $i++) {
		fwrite($fout, '0 ' . $infinity . '\n');
	}

	fclose($fout);
}

$response = file_get_contents('highscores.txt');

echo $response;
?>