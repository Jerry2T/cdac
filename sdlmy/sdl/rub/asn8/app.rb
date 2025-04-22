require 'sinatra'

# Configure Sinatra to accept connections from any host
set :bind, '0.0.0.0'

# Method to reverse the name
def reverse_name(first_name, last_name)
  "#{last_name} #{first_name}"
end

get '/' do
  erb :index
end

post '/reverse' do
  first_name = params[:first_name]
  last_name = params[:last_name]
  @reversed_name = reverse_name(first_name, last_name)
  erb :reverse
end