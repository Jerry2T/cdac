<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Shape Area Calculation</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

<h1>Shape Area Calculator</h1>
<form method="post">
    <div>
        <label for="triangle"><input type="radio" name="shape" value="triangle" id="triangle"> Triangle</label>
        <label for="square"><input type="radio" name="shape" value="square" id="square"> Square</label>
        <label for="circle"><input type="radio" name="shape" value="circle" id="circle"> Circle</label>
    </div>
    <div id="inputs">
        <!-- The inputs for the selected shape will go here -->
    </div>
    <input type="submit" name="submit" value="Calculate Area">
</form>

<?php
class Shape {
    public function calculateArea() {
        return 0;
    }
}

class Triangle extends Shape {
    private $base;
    private $height;
    public function __construct($base, $height) {
        $this->base = $base;
        $this->height = $height;
    }
    public function calculateArea() {
        return 0.5 * $this->base * $this->height;
    }
}

// Square class inherits Shape
class Square extends Shape {
    private $side;

    public function __construct($side) {
        $this->side = $side;
    }

    public function calculateArea() {
        return $this->side * $this->side;
    }
}

// Circle class inherits Shape
class Circle extends Shape {
    private $radius;

    public function __construct($radius) {
        $this->radius = $radius;
    }

    public function calculateArea() {
        return pi() * $this->radius * $this->radius;
    }
}

// Handle form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $shapeType = $_POST['shape'];

    if ($shapeType == "triangle" && isset($_POST['base']) && isset($_POST['height'])) {
        $base = $_POST['base'];
        $height = $_POST['height'];
        $shape = new Triangle($base, $height);
        $area = $shape->calculateArea();
        echo "<h2>Area of Triangle: $area</h2>";

    } elseif ($shapeType == "square" && isset($_POST['side'])) {
        $side = $_POST['side'];
        $shape = new Square($side);
        $area = $shape->calculateArea();
        echo "<h2>Area of Square: $area</h2>";

    } elseif ($shapeType == "circle" && isset($_POST['radius'])) {
        $radius = $_POST['radius'];
        $shape = new Circle($radius);
        $area = $shape->calculateArea();
        echo "<h2>Area of Circle: $area</h2>";
    }
}
?>

<script>
// JavaScript to show input fields based on selected shape
document.querySelectorAll('input[name="shape"]').forEach(function (element) {
    element.addEventListener('change', function () {
        const shape = this.value;
        const inputDiv = document.getElementById('inputs');
       
        if (shape == "triangle") {
            inputDiv.innerHTML = `
                Base: <input type="number" name="base" required><br>
                Height: <input type="number" name="height" required><br>
            `;
        } else if (shape == "square") {
            inputDiv.innerHTML = `
                Side: <input type="number" name="side" required><br>
            `;
        } else if (shape == "circle") {
            inputDiv.innerHTML = `
                Radius: <input type="number" name="radius" required><br>
            `;
        } else {
            inputDiv.innerHTML = '';
        }
    });
});
</script>

</body>
</html>


body {
  font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
  line-height: 1.6;
  margin: 0;
  padding: 20px;
  background-color: #f5f7fa;
  color: #333;
}

h1, h2 {
  color: #2c3e50;
  text-align: center;
}

h1 {
  margin-bottom: 30px;
  padding-bottom: 10px;
  border-bottom: 2px solid #3498db;
  max-width: 500px;
  margin-left: auto;
  margin-right: auto;
}

form {
  max-width: 500px;
  margin: 0 auto 30px;
  background: white;
  padding: 25px;
  border-radius: 8px;
  box-shadow: 0 3px 10px rgba(0, 0, 0, 0.1);
}

input[type="radio"] {
  margin-right: 8px;
  cursor: pointer;
}

input[type="number"] {
  width: 100%;
  padding: 10px;
  margin: 8px 0 15px;
  border: 1px solid #ddd;
  border-radius: 4px;
  font-size: 16px;
  box-sizing: border-box;
}

input[type="submit"] {
  display: block;
  width: 100%;
  padding: 12px;
  background: #3498db;
  color: white;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  font-size: 16px;
  font-weight: bold;
  transition: background 0.3s;
  margin-top: 20px;
}

input[type="submit"]:hover {
  background: #2980b9;
}

#inputs {
  margin: 15px 0;
  padding: 15px;
  background-color: #f8f9fa;
  border-radius: 5px;
  border-left: 3px solid #3498db;
}

h2 {
  margin-top: 20px;
  padding: 15px;
  background: white;
  border-radius: 8px;
  box-shadow: 0 3px 10px rgba(0, 0, 0, 0.1);
  max-width: 500px;
  margin-left: auto;
  margin-right: auto;
  color: #27ae60;
}

label {
  font-weight: bold;
  cursor: pointer;
  margin-right: 20px;
}
