require 'sinatra'

get '/' do
  erb :index
end

post '/reverse' do
  first_name = params[:first_name]
  last_name = params[:last_name]
  @reversed_name = "#{last_name} #{first_name}"
  erb :reverse
end