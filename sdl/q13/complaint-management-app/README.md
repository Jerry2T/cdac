# Complaint Management System

## Overview
The Complaint Management System is a web application designed to facilitate the submission, management, and viewing of complaints. Users can submit their complaints through a user-friendly interface, and administrators can view and manage these complaints efficiently.

## Project Structure
The project is organized into the following directories and files:

```
complaint-management-app
├── public
│   ├── index.php               # Entry point of the application
│   ├── submit_complaint.php     # Handles complaint submission
│   ├── view_complaints.php      # Displays submitted complaints
│   └── assets
│       ├── css
│       │   └── style.css        # CSS styles for the application
│       └── js
│           └── main.js          # JavaScript for client-side functionality
├── config
│   └── config.php               # Configuration settings, including DB connection
├── src
│   ├── Complaint.php            # Defines the Complaint class
│   └── Database.php             # Handles database connections and queries
└── README.md                    # Documentation for the project
```

## Setup Instructions
1. **Clone the Repository**
   Clone the repository to your local machine using:
   ```
   git clone <repository-url>
   ```

2. **Configure Database**
   - Navigate to the `config/config.php` file.
   - Update the database connection settings with your database credentials.

3. **Run the Application**
   - Ensure you have a local server environment (like XAMPP, WAMP, or MAMP) set up.
   - Place the project folder in the server's root directory (e.g., `htdocs` for XAMPP).
   - Access the application by navigating to `http://localhost/complaint-management-app/public/index.php` in your web browser.

## Usage
- **Submit a Complaint**: Navigate to the complaint submission page and fill out the form to submit a new complaint.
- **View Complaints**: Access the complaints viewing page to see a list of all submitted complaints.

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.