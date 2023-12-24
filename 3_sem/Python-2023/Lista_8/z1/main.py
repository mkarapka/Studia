import asyncio
import aiohttp
import json
from prywatne import API_KEY


async def fetch(session, method, url, params, headers):
    async with session.request(method, url, headers=headers, params=params) as response:
        return await response.json()


async def main(urls, headers, params):
    async with aiohttp.ClientSession() as session:
        res = []
        for url, header, param in zip(urls, headers, params):
            tasks = [fetch(session, "GET", url, p, header) for p in param]
            res.append(await asyncio.gather(*tasks))
        return res


urls = (
    "https://api-basketball.p.rapidapi.com/countries",
    "https://moviesdatabase.p.rapidapi.com/titles/",
)

headers = (
    {
        "X-RapidAPI-Key": API_KEY,
        "X-RapidAPI-Host": "api-basketball.p.rapidapi.com",
    },
    {
        "X-RapidAPI-Key": API_KEY,
        "X-RapidAPI-Host": "moviesdatabase.p.rapidapi.com",
    },
)

params = [
    (
        {"search": "Australia"},
        {"search": "Austria"},
        {"search": "Belgium"},
        {"search": "Brazil"},
        {"search": "Poland"},
        {"search": "Canada"},
        {"search": "China"},
        {"search": "Croatia"},
        {"search": "Czech Republic"},
        {"search": "USA"},
    ),
    (
        {"titleType": "movie", "page": 1, "limit": 2},
        {"titleType": "movie", "page": 2, "limit": 2},
        {"titleType": "movie", "page": 3, "limit": 2},
    ),
]


args = [urls, headers, params]
if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    result = loop.run_until_complete(main(*args))
    print(json.dumps(result, indent=2))
