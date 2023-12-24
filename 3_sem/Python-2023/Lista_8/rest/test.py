import aiohttp
import prywatne

async def fetch(method, session, url, headers=None, params=None):
    async with session.request(method, url, headers=headers, params=params) as response:
        return await response.json()

async def main():
    headers = [
        {
            "X-RapidAPI-Key": prywatne.ApiKey,
            "X-RapidAPI-Host": "api-basketball.p.rapidapi.com",
        },
        {
            "X-RapidAPI-Key": prywatne.ApiKey,
            "X-RapidAPI-Host": "moviesdatabase.p.rapidapi.com"
        }
    ]

    params = [
        [
            {"search": "Australia"}, {"search": "Austria"},
            {"search": "Belgium"}, {"search": "Brazil"},
            {"search": "Bulgaria"}, {"search": "Canada"},
            {"search": "China"}, {"search": "Croatia"},
            {"search": "Czech Republic"}, {"search": "USA"},
        ],
        [
            {"titleType": "movie", "page": 1, "limit": 2},
            {"titleType": "movie", "page": 2, "limit": 2},
            {"titleType": "movie", "page": 3, "limit": 2},
            {"titleType": "movie", "page": 4, "limit": 2}
        ]
    ]

    urls = ["https://api-basketball.p.rapidapi.com/countries", "https://moviesdatabase.p.rapidapi.com/titles/"]  # replace with your actual URLs

    async with aiohttp.ClientSession() as session:
        for i in range(2):
            for param in params[i]:
                response = await fetch('GET', session, urls[i], headers[i], param)
                # process the response