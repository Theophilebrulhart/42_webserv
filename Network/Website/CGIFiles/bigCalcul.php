<!DOCTYPE html>
<html>
<head>
    <title>Calculator</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            text-align: center;
        }

        h1 {
            color: #333;
        }

        form {
            display: inline-block;
            background-color: #fff;
            border: 1px solid #ccc;
            border-radius: 5px;
            padding: 20px;
            margin-top: 20px;
        }

        input[type="text"], select {
            padding: 10px;
            width: 200px;
            margin-right: 10px;
            border: 1px solid #ccc;
            border-radius: 3px;
        }

        button {
            padding: 10px 20px;
            background-color: #4CAF50;
            color: #fff;
            border: none;
            border-radius: 3px;
            font-size: 16px;
            cursor: pointer;
        }

        .result {
            margin-top: 20px;
            font-size: 24px;
            color: #333;
        }

        .calculator-image {
            margin-top: 20px;
            text-align: center;
        }

        .calculator-image img {
            max-width: 100%;
            height: auto;
        }

    </style>
</head>
<body>
    <h1>Calculator</h1>
    
    <form method="get" action="<?php echo $_SERVER['PHP_SELF']; ?>">
        <input type="text" name="num1" placeholder="Enter number 1" required>
        <input type="text" name="num2" placeholder="Enter number 2" required>
        <select name="operator">
            <option value="add">Addition (+)</option>
            <option value="subtract">Subtraction (-)</option>
            <option value="multiply">Multiplication (*)</option>
            <option value="divide">Division (/)</option>
        </select>
        <button type="submit" name="calculate">Calculate</button>
    </form>

    <?php
    if (isset($_GET['calculate'])) {
        $num1 = $_GET['num1'];
        $num2 = $_GET['num2'];
        $operator = $_GET['operator'];

        switch ($operator) {
            case 'add':
                $result = $num1 + $num2;
                break;
            case 'subtract':
                $result = $num1 - $num2;
                break;
            case 'multiply':
                $result = $num1 * $num2;
                break;
            case 'divide':
                if ($num2 != 0) {
                    $result = $num1 / $num2;
                } else {
                    echo "<p class='result'>Error: Division by zero is not allowed.</p>";
                }
                break;
            default:
                echo "<p class='result'>Invalid operator.</p>";
                break;
        }

        if (isset($result)) {
            echo "<p class='result'>Result: $result</p>";
        }
    }
    ?>

    <div class="calculator-image">
        <img src="https://menshaircuts.com/wp-content/uploads/2021/12/mustache-styles-western.jpg" alt="Mustache Image">
    </div>


</body>
</html>