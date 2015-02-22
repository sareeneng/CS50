<?php

    $table = [];
    $size = 0;

    function check($word)
    {
        global $table;
        return isset($table[strtolower($word)]);
    }

    function load($dictionary)
    {
        global $size;
        global $table;

        foreach(file($dictionary) as $word)
        {
            $table[chop($word)] = true;
            $size++;
        }
        return true;
    }

    function size()
    {
        global $size;
        return $size;
    }

    function unload()
    {
        return true;
    }

?>
