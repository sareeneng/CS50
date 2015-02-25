<form action="sell.php" method="post">
    <fieldset>
        <select class="form-group" name="stock_selected">
        	<?php
        		foreach($owned_stocks as $owned_stock)
        		{
        			print("<option>" . $owned_stock["symbol"] . "</option>");
        		}
        	?>
        </select>
        <div class = "form-group">
        	<button type="submit" class="btn btn-default">Submit</button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="logout.php">log out</a>
</div>
