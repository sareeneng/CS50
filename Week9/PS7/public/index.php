<?php

    // configuration
    require("../includes/config.php");

    $positions = [];
    $sql_query = "SELECT * FROM `ownedstocks` WHERE id=" . $_SESSION["id"];
	$rows = query($sql_query);

	$cash_assoc_array = query("SELECT cash FROM `users` WHERE id=" . $_SESSION["id"]);
	$_SESSION["cash"] = $cash_assoc_array[0]["cash"];


	$positions = [];
	foreach ($rows as $row) 
	{
		$stock = lookup($row["symbol"]);
		if ($stock !== false)
   		{
        	$positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
        	];
    	}
	}
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);
?>