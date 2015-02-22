#!/usr/bin/env php
<?php

    // ask user for an integer
    $n = readline("I'd like an integer please: "); 

    // analyze user's input
    if ($n > 0)
    {
        printf("You picked a positive number!\n");
    }
    else if ($n == 0)
    {
        printf("You picked zero!\n");
    }
    else
    {
        printf("You picked a negative number!\n");
    }

?>