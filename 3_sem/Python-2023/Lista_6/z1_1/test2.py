import bs4
import requests

def crawl(start_page, distance, action):
    visited = set()

    def vis_add(url):
        visited.add(url)
        return url

    def process_page(url, step):
        if step == distance:
            return
        if url not in visited:
            doc = requests.get(url)
            data = bs4.BeautifulSoup(doc.text, "html.parser")
            next_pages = [vis_add(link.get("href")) for link in data.find_all("a") \
                if link.get("href") is not None]
            return next_pages

    for i in process_page(start_page, 0):
        action(i)

crawl("https://hackr.io/blog", 4, lambda url: print(url))