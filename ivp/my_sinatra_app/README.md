# My Sinatra App

This is a simple Sinatra web application that accepts a user's first and last name and displays them in reverse order.

## Project Structure

```
my_sinatra_app
├── app.rb
├── views
│   ├── index.erb
│   └── reverse.erb
├── Gemfile
└── README.md
```

## Requirements

- Ruby
- Sinatra

## Setup

1. Clone the repository or download the project files.
2. Navigate to the project directory:
   ```
   cd my_sinatra_app
   ```
3. Install the required gems:
   ```
   bundle install
   ```

## Running the Application

To start the Sinatra server, run the following command in your terminal:

```
ruby app.rb
```

The application will be available at `http://localhost:4567`.

## Usage

1. Open your web browser and go to `http://localhost:4567`.
2. Enter your first and last name in the form.
3. Submit the form to see your names displayed in reverse order.