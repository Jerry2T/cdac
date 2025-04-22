<?php
require_once '../config/config.php';
require_once '../src/Database.php';
require_once '../src/Complaint.php';

$db = new Database();
$conn = $db->connect();

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    // Display the homepage or redirect to another page
    echo "<h1>Welcome to the Complaint Management System</h1>";
    echo "<a href='submit_complaint.php'>Submit a Complaint</a> | <a href='view_complaints.php'>View Complaints</a>";
} else {
    // Handle other request methods if necessary
    http_response_code(405);
    echo "Method Not Allowed";
}
?>