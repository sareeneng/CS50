<?php

    require(__DIR__ . "/../includes/config.php");
    //$us_state_abbrevs = array('AL', 'AK', 'AS', 'AZ', 'AR', 'CA', 'CO', 'CT', 'DE', 'DC', 'FM', 'FL', 'GA', 'GU', 'HI', 'ID', 'IL', 'IN', 'IA', 'KS', 'KY', 'LA', 'ME', 'MH', 'MD', 'MA', 'MI', 'MN', 'MS', 'MO', 'MT', 'NE', 'NV', 'NH', 'NJ', 'NM', 'NY', 'NC', 'ND', 'MP', 'OH', 'OK', 'OR', 'PW', 'PA', 'PR', 'RI', 'SC', 'SD', 'TN', 'TX', 'UT', 'VT', 'VI', 'VA', 'WA', 'WV', 'WI', 'WY', 'AE', 'AA', 'AP');

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"]
   	$geo = $_GET["geo"];
    // First identify if it is a zip codes
   	
   	$geo_has_zip = false;
   	$geo_has_town = false;
   	$geo_has_state_abbrev = false;
   	

   	$geo_components = preg_split("/[\s,]+/",$geo);

   	$zip = "";
   	$state_abbrev = "";
   	$city = "";

   	foreach($geo_components as $geo_component)
   	{
   		//First check if it is a zip
   		if(preg_match("/^[0-9][0-9][0-9][0-9][0-9]/", $geo_component, $matches))
   		{
   			$zip=$matches[0];
   			$geo_has_zip=true;
   		}
   		else if(preg_match("/^[a-zA-Z][a-zA-Z]$/", $geo_component, $matches))
   		{
   			if(in_array($matches[0], $us_state_abbrevs))
   			{
   				$state_abbrev=$matches[0];
   				$geo_has_state_abbrev=true;
   			}
   		}
   		else
   		{
   			$geo_has_town = true;
   			$city = $city . $geo_component;
   		}	

   	}

   	$sql_query = "SELECT * FROM places WHERE ";
   	if($geo_has_zip)
   	{
   		$sql_query = $sql_query . "postal_code=" . $zip. " ";
   	}
   	if($geo_has_state_abbrev)
   	{
   		if($geo_has_zip)
   		{
   			$sql_query = $sql_query . "AND ";
   		}
   		$sql_query = $sql_query . "admin_code1=\"" . $state_abbrev . "\" ";
   	}
   	if($geo_has_town)
   	{
   		if($geo_has_zip or $geo_has_state_abbrev)
   		{
   			$sql_query = $sql_query . "AND ";
   		}
   		$sql_query = $sql_query . "place_name LIKE \"" . $city . "%\"";
   	}


   	$places = query($sql_query);





    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
