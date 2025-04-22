<?php
require_once '../config/config.php';
require_once '../src/Database.php';
require_once '../src/Complaint.php';

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $title = trim($_POST['title']);
    $description = trim($_POST['description']);

    if (!empty($title) && !empty($description)) {
        $database = new Database();
        $db = $database->getConnection();

        $complaint = new Complaint($db);
        $complaint->title = $title;
        $complaint->description = $description;

        if ($complaint->create()) {
            echo "Complaint submitted successfully.";
        } else {
            echo "Unable to submit complaint. Please try again.";
        }
    } else {
        echo "Please fill in all fields.";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Submit Complaint</title>
    <link rel="stylesheet" href="assets/css/style.css">
</head>
<body>
    <h1>Submit a Complaint</h1>
    <form action="submit_complaint.php" method="post">
        <label for="title">Title:</label>
        <input type="text" id="title" name="title" required>
        
        <label for="description">Description:</label>
        <textarea id="description" name="description" required></textarea>
        
        <button type="submit">Submit</button>
    </form>
</body>
</html>