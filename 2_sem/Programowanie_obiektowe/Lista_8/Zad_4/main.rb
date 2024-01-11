# Mikołaj Karapka, lista 8, zadanie 4 - program testujący klasy
# Jawna i Zaszyfrowane

# Instrukcja uruchomienia programu
# System: Windows
# Użyte środowisko: ruby 3.2.2
# Polecenie uruchamiające program: ruby main.rb

# importowanie klasy Jawna i Zaszyfrowane
require_relative 'jawna'
require_relative 'zaszyfrowane'
class Main

  # deklaracja przykładowych słowników
  key = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
    'u' => 'a'
  }
  key_1 = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
  }

  # deklaracja zmiennej typu Jawna i zaszyfrowanie jej dla podanego klucza
  puts "Szyfrowane"
  puts "Dane wjeściowe: "
  puts "Słowo: ruby"
  puts "Słownik = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
    'u' => 'a'
  }"
  print "Wyjście: "
  slowo = Jawna.new("ruby")
  szyfr = slowo.zawszyfruj(key)

  # wypisanie zaszyfrowanej wiadomości
  puts szyfr.to_s

  puts ""
  puts "Odszyfrowywanie"
  puts "Dane wjeściowe: "
  puts "Słowo: yaru"
  puts "Słownik = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
    'u' => 'a'
  }"
  print "Wyjście: "
  # odszyfrowanie danej zmiennej oraz jej wypisanie
  word = szyfr.odszyfruj(key)
  puts word.to_s

  puts ""
  puts "Szyfrowanie dla złego klucza"
  puts "Słowo: ruby"
  puts "Słownik (bez szyfrowania dla u) = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
  }"
  print "Wyjście: "
  slowo = Jawna.new("ruby")
  wrong = slowo.zawszyfruj(key_1)

  puts ""
  puts "Odszyfrowywanie dla złego klucza"
  puts "Słowo: ruby"
  puts "Słownik (bez zaszyfrowanego a) = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
  }"
  print "Wyjście: "
  word_2 = szyfr.odszyfruj(key_1)
end
