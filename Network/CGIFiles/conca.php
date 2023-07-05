<?php

if (isset($_GET['value1']) && isset($_GET['value2'])) {
    $value1 = $_GET['value1'];
    $value2 = $_GET['value2'];

    $concatenatedString = $value1 . $value2;

    echo "Concatenated string: " . $concatenatedString;
} else {
    echo "Invalid parameters.";
}

?>