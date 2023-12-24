import requests

url = "https://moviesdatabase.p.rapidapi.com/titles/tt0944947"

headers = {
	"X-RapidAPI-Key": prywatne.ApiKey,
	"X-RapidAPI-Host": "moviesdatabase.p.rapidapi.com"
}

response = requests.get(url, headers=headers)

print(response.json())