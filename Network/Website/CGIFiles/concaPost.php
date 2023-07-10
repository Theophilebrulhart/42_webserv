<?php

if (isset($_POST['value1']) && isset($_POST['value2'])) {
    $value1 = $_POST['value1'];
    $value2 = $_POST['value2'];

    $concatenatedString = $value1 . $value2;

    echo "Concatenated string: " . $concatenatedString;
} else {
    echo "Invalid parameters.";
}

?>