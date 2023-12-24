from bs4 import BeautifulSoup
from requests import get, exceptions
from re import compile

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
                doc = get(url)
                data = BeautifulSoup(doc.text, "html.parser")
                text = (data.find("body")).find_all(compile('([a-zA-Z]+.)*[a-zA-Z]+'))
                
                next_pages = [link.get("href") for link in data.find_all("a") \
                    if link.get("href") is not None and link.get("href").startswith("http")]
                
                for page in next_pages:
                    yield from process_page(page, step + 1)
                yield (url, check_txt(text))
                
            except exceptions.SSLError:
                print(f"SSL failed for {url}. Skipping this page.")
                
    return process_page(start_page, 0)

for url, wynik in crawl("https://ii.uni.wroc.pl//", 2, lambda tekst: 'Python' in tekst):
    print(url, wynik)