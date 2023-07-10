<?php

if (isset($_GET['num1']) && isset($_GET['operator']) && isset($_GET['num2'])) {
    $num1 = $_GET['num1'];
    $operator = $_GET['operator'];
    $num2 = $_GET['num2'];
 

    // Perform the arithmetic operation based on the operator
    switch ($operator) {
        case '+':
            $result = $num1 + $num2;
            break;
        case '-':
            $result = $num1 - $num2;
            break;
        case '*':
            $result = $num1 * $num2;
            break;
        case '/':
            $result = $num1 / $num2;
            break;
        default:
            echo "Invalid operator.";
            exit;
    }

    echo "Result: " . $result;
} else {
    echo "Invalid parameters.";
}

?>