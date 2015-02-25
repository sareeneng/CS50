<?php
	require("../includes/config.php");
	if($_SERVER["REQUEST_METHOD"]=="GET")
	{
		render("change_password_form.php");
	}
	else if($_SERVER["REQUEST_METHOD"]=="POST")
	{
		$rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
		$row = $rows[0];
		$pass_in_table = $row["hash"];
		//First verify that current password matches
		if($pass_in_table != crypt($_POST["currPassword"], $pass_in_table))
		{
			apologize("You did not enter your correct current password");
		}
		//Next verify that new password and confirm password match
		if($_POST["newPassword"] != $_POST["newPasswordConfirm"])
		{
			apologize("Your new passwords do not match");
		}

		//Finally, update users table 
		query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["newPassword"]), $_SESSION["id"]);
		redirect("/");
	}
?>