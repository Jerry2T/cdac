<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>PHP Array Example</title>
</head>
<body>
  <h1>PHP Array: Sort and Sum</h1>
  <form method="post">
    <label for="numbers">Enter numbers (comma-separated):</label>
    <input type="text" id="numbers" name="numbers" placeholder="e.g. 5, 2, 8, 1, 7" required>
    <button type="submit">Submit</button>
  </form>

  <?php  
  if ($_SERVER["REQUEST_METHOD"] == "POST") {      
      $input = $_POST['numbers'];
      $numbers = explode(',', $input);      
      $numbers = array_map('intval', $numbers);      
      sort($numbers);   
      $sum = array_sum($numbers);
      
      echo "<h2>Sorted Numbers:</h2>";
      echo "<p>" . implode(', ', $numbers) . "</p>";
      echo "<h2>Sum of Numbers:</h2>";
      echo "<p>$sum</p>";
  }
  ?>
</body>
</html>
