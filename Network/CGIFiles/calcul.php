<?php

if (isset($_GET['num1']) && isset($_GET['num2']) && isset($_GET['operator'])) {
    $num1 = $_GET['num1'];
    $num2 = $_GET['num2'];
    $operator = $_GET['operator'];

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