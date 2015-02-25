<form action="change_password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="currPassword" placeholder="Current Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="newPassword" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="newPasswordConfirm" placeholder="Confirm Password" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Submit</button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="logout.php">Logout</a>
</div>
