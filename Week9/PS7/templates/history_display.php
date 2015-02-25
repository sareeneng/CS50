<table class="table table-bordered">
<tr><td><b>Date/Time</b></td><td><b>Symbol</b></td><td><b>BUY/SELL</b></td><td><b>Shares</b></td><td><b>Price</b></td></tr>
<?php
	
	foreach($rows as $row)
	{
		print("<tr>");
		print("<td>" . $row["timestamp"] . "</td>");
		print("<td>" . $row["symbol"] . "</td>");
		print("<td>" . $row["buy_or_sell"] . "</td>");
		print("<td>" . $row["shares"] . "</td>");
		print("<td>" . number_format($row["price"],2) . "</td>");
		print("</tr>");
	}


?>
</table>
<div>
    <a href="logout.php">Log Out</a>
</div>
