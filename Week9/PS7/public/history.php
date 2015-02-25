<?php
	require("../includes/config.php");

	$rows = query("SELECT * from history WHERE id=? ORDER BY timestamp DESC", $_SESSION["id"]);

	render("history_display.php", ["rows" => $rows]);

?>