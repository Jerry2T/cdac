document.getElementById("registrationForm").addEventListener("submit", function(event) {
    let isValid = true;
    document.querySelectorAll(".error").forEach(el => el.textContent = "");

    let name = document.getElementById("name").value.trim();
    if (name.length < 3) {
        document.getElementById("nameError").textContent = "Name must be at least 3 characters.";
        isValid = false;
    }

    let email = document.getElementById("email").value.trim();
    let emailPattern = /^[a-zA-Z0-9._%+-]+@gmail\.com$/;
    if (!emailPattern.test(email)) {
        document.getElementById("emailError").textContent = "Enter a valid Gmail address.";
        isValid = false;
    }

    let password = document.getElementById("password").value;
    if (password.length < 6) {
        document.getElementById("passwordError").textContent = "Password must be at least 6 characters.";
        isValid = false;
    }

    if (!isValid) {
        event.preventDefault();
    }
});