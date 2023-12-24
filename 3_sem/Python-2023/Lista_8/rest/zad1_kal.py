import asyncio
import aiohttp
import json
import prywatne

async def fetch(method, session, url, headers=None, params=None):
    async with session.request(method, url, headers=headers, params=params) as response:
        return await response.json()

async def main():
    weather_headers = {
        "X-RapidAPI-Key": prywatne.Keys.get_key_1(),
        "X-RapidAPI-Host": "weatherapi-com.p.rapidapi.com",
    }
    weather_params = [
        {"q": "Warsaw"}, {"q": "London"}, {"q": "Paris"}, {"q": "Berlin"},
        {"q": "Madrid"}, {"q": "Rome"}, {"q": "Moscow"},
        {"q": "Kiev"}, {"q": "Budapest"}, {"q": "Prague"},
    ]
    weather_url = "https://weatherapi-com.p.rapidapi.com/current.json"

    async with aiohttp.ClientSession() as session:
        tasks = [fetch("GET", session, weather_url, weather_headers, p) for p in weather_params]
        return await asyncio.gather(*tasks)

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    result = loop.run_until_complete(main())
    print(json.dumps(result, indent=2))
