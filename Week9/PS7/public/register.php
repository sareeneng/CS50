<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]) or $_POST["confirmation"]!=$_POST["password"])
        {
            apologize("Your passwords don't match");
        }

        if(query("INSERT INTO users (username, hash, cash) VALUES(?,?,10000.00)",$_POST["username"], crypt($_POST["password"])) === false)
        {
            apologize("Username already exists");
        }

        $rows = query("SELECT LAST_INSERT_ID() as id");
        $id = $rows[0]["id"];

        $_SESSION["id"] = $id;

        // redirect to portfolio
        redirect("/");
    }

?>