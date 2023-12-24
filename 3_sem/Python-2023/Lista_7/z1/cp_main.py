from threading import Thread
from queue import Queue
import bs4
import requests


def return_senteces(text, word):
    def end_of_sentence(index, text):
        for let in range(index, len(text) - 1):
            if text[let] == "." or text[let] == "\n":
                end = let
                return end
        return len(text) - 1

    def start_of_sentence(index, text):
        for let in range(index, 0, -1):
            if text[let] == "." or text[let] == "\n":
                start = let
                return start
        return 0

    sentences = []
    index = -1

    while True:
        index = text.find(word, index + 1)
        if index == -1:
            break
        end = end_of_sentence(index, text)
        start = start_of_sentence(index, text)
        sentences.append(text[start + 1 : end])

    if sentences:
        return sentences
    return False


def crawl(start_page, distance, action):
    visited = set()

    def process_page(url, step):

        if step == distance:
            return

        def return_thread(page, step):
            yield from process_page(page, step)

        if url not in visited:
            visited.add(url)
            try:
                doc = requests.get(url)
                data = bs4.BeautifulSoup(doc.text, "html.parser")
                text = data.body.get_text()

                next_pages = [
                    Thread(target=return_thread, args=(link.get("href"), step + 1))
                    for link in data.find_all("a")
                    if link.get("href") is not None
                    and link.get("href").startswith("http")
                ]

                yield (url, action(text))

                for page in next_pages:
                    page.start()

                for page in next_pages:
                    page.join()

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
print_result(host, 3, lambda tekst: return_senteces(tekst, "Python"))
