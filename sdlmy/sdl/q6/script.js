alert("Welcome to the webpage!");

// Calculate the average number of weeks in a human lifetime (assuming 80 years)
const weeksInAYear = 52;
const avgLifetime = 80;
const totalWeeks = weeksInAYear * avgLifetime;
console.log("Average number of weeks in a human lifetime: " + totalWeeks);

// Store a string in a variable
const message = "Hello, this is a JavaScript example.";
console.log(message);

// Program that tells time of the day
const currentHour = new Date().getHours();
let timeOfDay;

if (currentHour < 12) {
    timeOfDay = "morning";
} else if (currentHour < 18) {
    timeOfDay = "afternoon";
} else {
    timeOfDay = "night";
}

console.log("Good " + timeOfDay + "!");
