# Searchmate

## Wprowadzenie
Searchmate to aplikacja, która ułatwia wyszukiwanie w przeglądarce wprowadzonych fraz, obliczanie prostych wyrażeń matematycznych oraz przesyłanie zapytań do GPT. Program działa w tle i wyłącza się, gdy traci aktywność. Jest dostępny zarówno dla systemów operacyjnych Linux, jak i Windows.

## Klasy

### MainWindow
Klasa MainWindow, dziedziczy po QWidget i konfiguruje aplikację. Zawiera pasek wyszukiwania i logikę obsługującą sugestie oraz wykonywanie zapytań. Wygląd aplikacji jest zdefiniowany za pomocą arkuszy stylów CSS. Wszystko jest realizowane z użyciem mechanizmu sygnałów i slotów PyQt6.

### SkillLoader
Ta klasa odpowiada za dodawanie nowych klas, które będą wykonywały określone działania w interfejsie graficznym. Te działania nazywamy 'umiejętnościami' danej klasy.

### Skill
Klasa Skill to abstrakcyjna klasa bazowa dla wszystkich "umiejętności" w systemie. Każda umiejętność musi implementować metody run i suggestion, które odpowiadają za wykonanie umiejętności i generowanie sugestii przed jej wykonaniem. Metody te przyjmują zapytanie użytkownika jako argument i zwracają słownik z typem widgetu i wiadomością do wyświetlenia lub None, jeśli operacja jest niemożliwa do wykonania.

### MathSkill
Konkretnie, ta umiejętność pozwala na przetwarzanie i ewaluację wyrażeń matematycznych. Użytkownik wprowadza ciąg znaków reprezentujący pewne działanie matematyczne (na przykład "math 2+2"), a ta klasa przetwarza ten ciąg i zwraca wynik. Wykorzystuje do tego bibliotekę cexprtk, która umożliwia ewaluację wyrażeń matematycznych zapisanych jako ciągi znaków.

### WebSkill

Ta specyficzna umiejętność służy do uruchamiania przeglądarki internetowej i wykonywania wyszukiwania w Google na podstawie wprowadzonego przez użytkownika zapytania. Klasa WebSkill używa do tego modułu webbrowser z biblioteki standardowej Pythona.

### GptSkill

Ta konkretna umiejętność umożliwia interakcje z modelem GPT stworzonym przez OpenAI. Klasa ta korzysta z modułu openai i konkretnie, na podstawie wprowadzonego przez użytkownika zapytania, przesyła żądanie do modelu GPT, a następnie zwraca uzyskaną odpowiedź.

### Config

Klasa Config w module Searchmate zarządza konfiguracją aplikacji, w tym obsługą plików konfiguracyjnych w formacie INI za pomocą modułu configparser z biblioteki standardowej Pythona. W szczególności, ta klasa jest odpowiedzialna za pobieranie klucza API dla modułu OpenAI z pliku konfiguracyjnego.


## Instalacja 

#### Instalacja z użyciem poetry:

```shell 
poetry install
```
#### Instalacja z użyciem pip:

```shell
pip install -e
```

## Uruchomienie programu

#### Za pomocą poetry:

```shell
poetry run python -m searchmate
```

#### Za pomocą pip:

```shell
python -m searchmate
```

## Korzystanie z programu

Aby obliczyć wyrażenie matematyczne w aplikacji Searchmate, należy wpisać najpierw słowo "math", a następnie wyrażenie matematyczne, które chcemy obliczyć. Na przykład: "math 2+2". Jeżeli chcemy zadać pytanie do modelu języka GPT, należy wpisać "gpt", a potem swoje pytanie. Ważne, aby wprowadzić swój klucz API do pliku konfiguracyjnego, by móc korzystać z tej funkcji.

W przypadku wprowadzenia dowolnej innej frazy, program uruchomi przeglądarkę i wyświetli stronę z wynikami wyszukiwania dla wprowadzonego zapytania.

## Linki

### Repozytorium na Github
https://github.com/mkalitka/searchmate

### Automatyczna dokumentacja
https://mkalitka.github.io/searchmate/

## 
