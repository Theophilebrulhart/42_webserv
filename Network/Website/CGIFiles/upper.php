<?php

if (isset($_GET['string'])) {
    $string = $_GET['string'];
    $uppercaseString = strtoupper($string);
    echo $uppercaseString;
} else {
    echo "No string parameter provided.";
}

?>