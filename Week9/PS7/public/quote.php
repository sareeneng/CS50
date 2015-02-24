<?php
	
	require("../includes/config.php");
	
	if($_SERVER["REQUEST_METHOD"]=="GET")
	{
		render("quote_form.php");
	}
	else if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		$stock = lookup($_POST["ticker"]);
		if($stock == false)
		{
			apologize("Invalid Ticker Symbol");
		}
		
		render("display_quote.php", $stock);
	}
?>