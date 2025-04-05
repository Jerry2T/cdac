require 'net/smtp'

# Configuration
SMTP_SERVER = 'smtp.gmail.com'
SMTP_PORT = 587
USERNAME = 'tomjerryguest@gmail.com'
PASSWORD = 'tom4jerry$GuestAcc'
TO_EMAIL = 'jerryt2714@example.com'
FROM_EMAIL = 'tomjerryguest@gmail.com'
SUBJECT = 'Test Email from Ruby'
BODY = "Hello,\n\nThis is a test email sent from a Ruby script.\n\nBest,\nRuby Script"

# Construct email message
message = <<~MESSAGE_END
  From: Sender <#{FROM_EMAIL}>
  To: jerryt2714 <#{TO_EMAIL}>
  Subject: #{SUBJECT}

  #{BODY}
MESSAGE_END

# Send email
begin
  Net::SMTP.start(SMTP_SERVER, SMTP_PORT, 'localhost', USERNAME, PASSWORD, :plain) do |smtp|
    smtp.send_message(message, FROM_EMAIL, TO_EMAIL)
  end
  puts 'Email sent successfully!'
rescue StandardError => e
  puts "Failed to send email: #{e.message}"
end
