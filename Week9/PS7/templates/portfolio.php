<table class="table table-bordered">
<tr><td><b>Ticker</b></td><td><b>Name</b></td><td><b>Shares</b></td><td><b>Price</b></td><td><b>Total</b></td></tr>
<?php
	foreach ($positions as $position)
	{
		
		print("<tr>");
		print("<td>" . $position["symbol"] . "</td>");
		print("<td>" . $position["name"] . "</td>");
		print("<td>" . $position["shares"] . "</td>");
		print("<td>$" . number_format($position["price"],2) . "</td>");
		print("<td>$" . number_format($position["shares"] * $position["price"], 2) . "</td>");
		print("</tr>");
	}
?>
<tr><td><b>CASH</b></td><td></td><td></td><td></td><td>$<?= number_format($cash[0]["cash"], 2)?></td></tr>
</table>


<div>
    <a href="logout.php">Log Out</a>
</div>
