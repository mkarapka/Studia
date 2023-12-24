# def sol_add(element):
#     sol.append(element)
#     return element
# lst = [1,1,2,3,4,4,5,6,6,6,1,2,7,5,4,6]
# sol = []
# lst2 = [sol_add(element) for element in lst if element not in sol]
# print(lst2)
# print(sol)

import bs4
import requests
# def ret_links(url):
#     dane = bs4.BeautifulSoup(requests.get(url).text, 'html.parser')
#     return [ link.get('href') for link in dane.find_all('a')]
# url = "https://www.diki.pl/slownik-angielskiego?q=parent"
# res = requests.get(url)
# for i in ret_links(url):
#     print(i)


# lst = set()

# lst2 = [1,1,2,3,4,4,5,6,6,6,1,2,7,5,4,6]

# for elem in lst2:
#     lst.add(elem)
# print(lst)

link = "https://www.diki.pl/slownik-angielskiego?q=parent"
link = "https://skos.ii.uni.wroc.pl/"
res = requests.get(link)
dane = bs4.BeautifulSoup(res.text, 'html.parser')
import re

cos = dane.find_all(re.compile('([a-zA-Z]+.)*[a-zA-Z]+'))    
for i in cos:
    if "Python" in i.text:
        print(i.text)