<?php

class Entry {
	public $name, $time;
	public function __construct($name, $time) {
		$this->name = $name;
		$this->time = $time;
	}
}

function compare($e1, $e2) {
	if ($e1->score < $e2->score)
		return -1;
	else if ($e1->score > $e2->score)
		return 1;
	else
		return 0;
}

$infinity = 1000000000;
$scores_saved = 10;

$name = $_REQUEST['name'];
$time = $_REQUEST['time'];
$difficulty = $_REQUEST['difficulty'];
$entries = [];

if (!file_exists('highscores.txt')) {
	for ($i = 0; $i < 5 * $scores_saved; $i++) {
		$entries[] = new Entry('0', $infinity);
	}
} else {
	$data = file_get_contents('highscores.txt');
	$data = explode('\n', $data);
	foreach ($data as $line) {
		$line = explode(' ', $line);
		$entries[] = new Entry($line[0], $line[1]);
	}
}

if ($time < $entries[9 + 10 * $difficulty]) {
	$entries[9 + 10 * $difficulty] = new Entry($name, $time);

	for ($i = 10 * $difficulty; $i < 9 + 10 * $difficulty; $i++) {
		for ($j = $i + 1; $j < 10 + 10 * $difficulty; $j++) {
			if ($entries[$i]->time > $entries[$j]->time) {
				$tmp = $entries[$i];
				$entries[$i] = $entries[$j];
				$entries[$j] = $tmp;
			}
		}
	}

}

?>