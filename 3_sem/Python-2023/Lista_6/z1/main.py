import re
import bs4
import requests
import time
def crawl(start_page, distance, action):
    visited = set()

    def process_page(url, step):
        if step == distance:
            return

        def check_txt(text):
            for i in text:
                if action(i.text):
                    return True
            return False

        if url not in visited:
            visited.add(url)
            try:
                doc = requests.get(url)
                data = bs4.BeautifulSoup(doc.text, "html.parser")
                text = (data.find("body")).find_all(
                    re.compile("([a-zA-Z]+.)*[a-zA-Z]+"))

                next_pages = [
                    link.get("href")
                    for link in data.find_all("a")
                    if link.get("href") is not None
                    and link.get("href").startswith("http")]

                yield (url, check_txt(text))
                for page in next_pages:
                    yield from process_page(page, step + 1)
                
            except requests.exceptions.SSLError:
                print(f"SSL failed for {url}. Skipping this page.")

    return process_page(start_page, 0)

def print_result(host, distance, action):
    try:
        for url, wynik in crawl(host, distance, action):
            print(url, wynik)
    except KeyboardInterrupt:
        print("Program interrupted by user.")

host = "https://ii.uni.wroc.pl//"
start = time.time()
print_result(host, 2, lambda tekst: "Python" in tekst)
end = time.time()
print(f"Time: {end - start}")