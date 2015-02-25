<?php
	
	require("../includes/config.php");
	
	if($_SERVER["REQUEST_METHOD"]=="GET")
	{
		//First get list of all the stocks that this person owns
		$owned_stocks = query("SELECT symbol from ownedstocks WHERE id=?",$_SESSION["id"]);

		render("sell_form.php", ["owned_stocks" => $owned_stocks]);
	}
	else if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		$symbol = $_POST["stock_selected"];

		$cash = $_SESSION["cash"];
		$price = lookup($symbol)["price"];
		$shares = query("SELECT shares from ownedstocks WHERE id=? AND symbol=?",$_SESSION["id"],$symbol)[0]["shares"];

		//First determine the amount of cash that will be gained from this transaction
		$_SESSION["cash"] = $_SESSION["cash"] + $price * $shares;
		//Update table accordingly
		query("UPDATE users SET cash = ? WHERE id = ?", $_SESSION["cash"], $_SESSION["id"]);
		query("DELETE from ownedstocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);
		redirect("/");
	}
?>