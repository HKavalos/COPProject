require "uri"
require "net/http"
require 'json'



url = URI("https://api.igdb.com/v4/games/")

https = Net::HTTP.new(url.host, url.port)
https.use_ssl = true



request = Net::HTTP::Post.new(url)
request["Client-ID"] = "raqhcbhj0vo1hngc82hom7f7d54zp8"
request["Authorization"] = "Bearer f3o1bbtxm26sd4gq3ci06eugayd128"
request["Content-Type"] = "application/json"
request["Cookie"] = "__cfduid=dd91ed6451babd79469936dfd983802bd1617112942"

outfile = "games.csv"
file = File.open(outfile,'w') 
file.write("ID,Name,Rating,Genres,Platforms,Companies\n")
min = 0
max = 0
genres_ = ""
platforms_ = ""
companies_ = ""
while min <= 200000
	max = min + 500
	query = "fields name,genres.name, platforms.name, aggregated_rating, involved_companies.company.name; where id > #{min} & id <= #{max}; limit 500;"
	request.body = query
	#p query
	response = https.request(request)
	res = response.read_body
	data = JSON.parse(res)
	data.each do |d|
		genres = d["genres"]
		if genres
			genres.each do |g|
				genres_ = genres_ + g["name"] + ":"	
			end
		end
		platforms = d["platforms"]
		if platforms
			platforms.each do |p|
				platforms_ = platforms_ + p["name"] + ":"
			end
		end
		companies = d["involved_companies"]
		if companies
			companies.each do |c|
				companies_ = companies_ + c["company"]["name"] + ":"
			end
		end
		rating = d["aggregated_rating"]
		if rating == ""
			rating = "0"
		end
		d["name"].gsub!("\"","\'")
		game_name = "\"#{d["name"]}\""
		genres = "\"#{genres_[0,genres_.length-1]}\""
		platform_names = "\"#{platforms_[0,platforms_.length-1]}\""
		company_names = "\"#{companies_[0,companies_.length-1]}\""
		#file.write("#{d["id"]},#{game_name},#{d["aggregated_rating"]},#{genres},#{platform_names},#{company_names}")
		if d["id"] != ""
			file.puts("#{d["id"]},#{game_name},#{d["aggregated_rating"].to_f.round(2)},#{genres},#{platform_names},#{company_names}")
		end
		genres_ = ""
		platforms_ = ""
		companies_ = ""
	end
	min += 500
end
file.close
