<?php

if (isset($_POST['string'])) {
    $string = $_POST['string'];
    $uppercaseString = strtoupper($string);
    echo $uppercaseString;
} else {
    echo "No string parameter provided.";
}

?>