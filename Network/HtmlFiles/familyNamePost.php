
    <?php
        for ($i = 1; $i <= 25; $i++) {
            $name = isset($_POST["name{$i}"]) ? $_POST["name{$i}"] : '';
            if (!empty($name)) {
                $formattedName = ucfirst(strtolower($name));
                echo "name {$i}: {$formattedName} \n";
            }
        }
    ?>

