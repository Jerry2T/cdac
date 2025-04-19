function calculate() {    
    let name = document.getElementById("name").value;
    let age = parseInt(document.getElementById("age").value);
      
    let averageLifespan = 80;
    let weeksInYear = 52;      
    let yearsLeft = averageLifespan - age;
    let weeksLeft = yearsLeft * weeksInYear;    

    message += `You are ${age} years old. <br>`;
    message += `You may have approximately <strong>${weeksLeft}</strong> weeks left, assuming an average lifespan of ${averageLifespan} years.`;  
    document.getElementById("output").innerHTML = message;
  }
  