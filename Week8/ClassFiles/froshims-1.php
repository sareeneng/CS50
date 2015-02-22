<?php

    /**
     * froshims-1.php
     *
     * David J. Malan
     * malan@harvard.edu
     *
     * Implements a registration form for Frosh IMs.
     * Submits to register-1.php.
     *
     * Demonstrates Bootstrap (http://getbootstrap.com/).
     */

?>

<!DOCTYPE html>

<html>
    <head>
        <link href="bootstrap/css/bootstrap.min.css" rel="stylesheet"/>
        <title>Frosh IMs</title>
    </head>
    <body style="margin: 20px;">
        <h1>Register for Frosh IMs</h1>
        <form action="register-1.php" method="post">
            <fieldset>
                <label>Name</label>
                <input name="name" type="text"/>
                <label class="checkbox">
                    <input name="captain" type="checkbox"/> Captain?
                </label>
                <label class="radio">
                    <input name="gender" type="radio" value="F"/> Female
                </label>
                <label class="radio">
                    <input name="gender" type="radio" value="M"/> Male
                </label>
                <label>
                    <select name="dorm">
                        <option value=""></option>
                        <option value="Apley Court">Apley Court</option>
                        <option value="Canaday">Canaday</option>
                        <option value="Grays">Grays</option>
                        <option value="Greenough">Greenough</option>
                        <option value="Hollis">Hollis</option>
                        <option value="Holworthy">Holworthy</option>
                        <option value="Hurlbut">Hurlbut</option>
                        <option value="Lionel">Lionel</option>
                        <option value="Matthews">Matthews</option>
                        <option value="Mower">Mower</option>
                        <option value="Pennypacker">Pennypacker</option>
                        <option value="Stoughton">Stoughton</option>
                        <option value="Straus">Straus</option>
                        <option value="Thayer">Thayer</option>
                        <option value="Weld">Weld</option>
                        <option value="Wigglesworth">Wigglesworth</option>
                    </select>
                </label>
                <button class="btn btn-default" type="submit">Register</button>
            </fieldset>
        </form>
    </body>
</html>
