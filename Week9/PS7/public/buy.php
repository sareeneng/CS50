<?php
	
	require("../includes/config.php");
	
	if($_SERVER["REQUEST_METHOD"]=="GET")
	{
		render("buy_form.php");
	}
	else if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		$numShares = $_POST["numShares"];

		//First make sure that they entered a valid number
		if(!preg_match("/^\d+$/", $_POST["numShares"]))
			apologize("Please enter a non-negative integer");

		//Then verify that ticker actually exists
		$stock_info = lookup($_POST["ticker"]);
		if($stock_info === false)
			apologize("Could not find this ticker symbol");

		$price = $stock_info["price"];
		$symbol = $stock_info["symbol"];	//this will already be upper-case

		//Then verify that user has enough cash
		if($_SESSION["cash"] < $price * $_POST["numShares"])
			apologize("You do not have enough cash for this transaction");

		//If all above are met, then deduct cash from table, update SESSION[cash] and then add this stock to the table
		$_SESSION["cash"] = $_SESSION["cash"] - $price * $_POST["numShares"];
		query("UPDATE users SET cash = ? WHERE id=?",$_SESSION["cash"],$_SESSION["id"]);
		query("INSERT INTO ownedstocks (id, symbol, shares) VALUES(?,?,?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $symbol, $numShares);

		redirect("/");
	}
?>