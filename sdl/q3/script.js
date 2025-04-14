document.getElementById("regForm").addEventListener("submit", function(event){
    event.preventDefault();
    let isValid = true;
    let firstname=document.getElementById("firstname").value.trim();
    
    if(firstname.length == ""){
        document.getElementById("firstname").style.borderColor = "red";
        document.getElementById("firstNameError").innerText = "First Name is required";
        isValid = false;
    }else{
        document.getElementById("firstNameError").innerText = "";
    }

    let lastName = document.getElementById("lastName").value.trim();
    if(firstname.length == ""){
        document.getElementById("lastName").style.borderColor = "red";
        document.getElementById("lastNameError").innerText = "Last Name is required";
        isValid = false;
    }else{
        document.getElementById("lastNameError").innerText = "";
    }

    let email = document.getElementById("email").value.trim();
    let emailpattern = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
    if(email.length == ""){
        document.getElementById("email").style.borderColor = "red";
        document.getElementById("emailError").innerText = "Email is required";
        isValid = false;
    }else if (!emailPattern.test(email)) {
        document.getElementById("email").style.borderColor = "red";
        document.getElementById("emailError").innerText = "Enter a valid email";
        isValid = false;
    } else {
        document.getElementById("emailError").innerText = "";
    }

    let password = document.getElementById("password").value;
    if (password.length < 6) {
        document.getElementById("password").style.borderColor = "red";
        document.getElementById("passwordError").innerText = "Password must be at least 6 characters";
        isValid = false;
    } else {
        document.getElementById("passwordError").innerText = "";
    }

    let dob = document.getElementById("dob").value;
    if (dob === "") {
        document.getElementById("dobError").innerText = "Date of Birth is required";
        isValid = false;            
    } else {
        document.getElementById("dobError").innerText = "";
    }
    if (isValid) {
        alert("Registration Successful!");
    }
});