<?php
$employees = [
    "John Doe", "Jane Smith", "Robert Brown", "Emily Davis", "Michael Johnson",
    "Sarah Wilson", "David Martinez", "Laura Clark", "James Rodriguez", "Emma Lewis",
    "Daniel Walker", "Olivia Hall", "Christopher Allen", "Sophia Young", "Matthew King",
    "Ava Wright", "Ethan Scott", "Isabella Green", "Alexander Adams", "Mia Baker"
];
$search_result = "";
$result_class = "";
if (isset($_POST['search_name'])) {
    $search_name = trim($_POST['search_name']);
    if (in_array($search_name, $employees)) {
        $search_result = "$search_name exists in the employee list.";
        $result_class = "success";
    } else {
        $search_result = "$search_name was not found in the employee list.";
        $result_class = "error";
    }
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Employee Search</title>
    <link rel="stylesheet" href="style.css">
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 20px;
            background-color: #f4f4f4;
        }
        h1 {
            color: #333;
            text-align: center;
            margin-bottom: 30px;
        }
        form {
            max-width: 500px;
            margin: 0 auto;
            background: white;
            padding: 20px;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
        }
        input[type="text"] {
            width: 70%;
            padding: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
            font-size: 16px;
        }
        button {
            padding: 10px 15px;
            background: #4c8fca;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }
        button:hover {
            background: #3a7dbd;
        }
        p {
            text-align: center;
            margin-top: 20px;
            font-size: 18px;
            padding: 10px;
            background: white;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
            max-width: 500px;
            margin-left: auto;
            margin-right: auto;
        }
        .success {
            color: #28a745;
        }
        .error {
            color: #dc3545;
        }
    </style>
</head>
<body>
    <h1>Search for an Employee</h1>
    <form method="post">
        <input type="text" name="search_name" placeholder="Enter employee name" required>
        <button type="submit">Search</button>
    </form>
    <?php if($search_result): ?>
        <p class="<?php echo $result_class; ?>"><?php echo $search_result; ?></p>
    <?php endif; ?>
</body>
</html>


