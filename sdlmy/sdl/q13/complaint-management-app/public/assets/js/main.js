document.addEventListener('DOMContentLoaded', function() {
    const complaintForm = document.getElementById('complaintForm');
    
    complaintForm.addEventListener('submit', function(event) {
        event.preventDefault();
        
        const title = document.getElementById('title').value;
        const description = document.getElementById('description').value;

        if (title === '' || description === '') {
            alert('Please fill in all fields.');
            return;
        }

        const formData = new FormData(complaintForm);

        fetch('submit_complaint.php', {
            method: 'POST',
            body: formData
        })
        .then(response => response.json())
        .then(data => {
            if (data.success) {
                alert('Complaint submitted successfully!');
                complaintForm.reset();
            } else {
                alert('Error submitting complaint: ' + data.message);
            }
        })
        .catch(error => {
            console.error('Error:', error);
            alert('An error occurred while submitting the complaint.');
        });
    });
});