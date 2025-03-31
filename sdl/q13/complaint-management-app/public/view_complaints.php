<?php
require_once '../config/config.php';
require_once '../src/Database.php';
require_once '../src/Complaint.php';

$db = new Database();
$complaints = $db->query("SELECT * FROM complaints");

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="assets/css/style.css">
    <title>View Complaints</title>
</head>
<body>
    <h1>Submitted Complaints</h1>
    <table>
        <thead>
            <tr>
                <th>ID</th>
                <th>Title</th>
                <th>Description</th>
                <th>Date Submitted</th>
            </tr>
        </thead>
        <tbody>
            <?php if ($complaints): ?>
                <?php foreach ($complaints as $complaint): ?>
                    <tr>
                        <td><?php echo htmlspecialchars($complaint['id']); ?></td>
                        <td><?php echo htmlspecialchars($complaint['title']); ?></td>
                        <td><?php echo htmlspecialchars($complaint['description']); ?></td>
                        <td><?php echo htmlspecialchars($complaint['date_submitted']); ?></td>
                    </tr>
                <?php endforeach; ?>
            <?php else: ?>
                <tr>
                    <td colspan="4">No complaints found.</td>
                </tr>
            <?php endif; ?>
        </tbody>
    </table>
    <a href="submit_complaint.php">Submit a new complaint</a>
</body>
</html>