#!/usr/bin/env php
<?php

    $x = 2;
    printf("x is now %d\n", $x);
    printf("Cubing...\n");
    $x = cube($x); 
    printf("Cubed!\n");
    printf("x is now %d\n", $x);

    /**
     * Cubes argument.
     */
    function cube($n) 
    {
        return $n * $n * $n;
    }

?>