# Mikołaj Karapka, lista 8, zadanie 3 - program testujący klasę ONP

# Instrukcja uruchomienia programu
# System: Windows
# Użyte środowisko: ruby 3.2.2
# Polecenie uruchamiające program: ruby main.rb
require_relative 'onp'
class Main

  # testowanie programu
  puts "Test#1"
  lista = [4, 2, 8, '-', '*']
  puts "Dane wejściowe: " + lista.to_s
  wyrazy = ONP.new(lista)
  puts "Wynik: #{wyrazy.oblicz}"

  puts ""
  puts "Test#2"
  lista = [4, 2, 8, '-', '*', '+']
  puts "Dane wjeściowe: " + lista.to_s
  wyrazy = ONP.new(lista)
  puts "#{wyrazy.oblicz}"

  puts ""
  puts "Test#3"
  lista = [12, 13, "+", 3, "x", "-", "*", 2, "/"]
  puts "Dane wjeściowe: " + lista.to_s
  puts "Zmienna x = 1"
  klucz = {
    "x" => 1
  }
  wyrazy = ONP.new(lista, klucz)
  puts "Wynik: #{wyrazy.oblicz}"

  puts ""
  puts "Test#4"
  lista = [12, 13, "+", "y", "x", "-", "*", 2, "/"]
  puts "Dane wjeściowe: " + lista.to_s
  puts "Zmienna x = 1, y - niezadeklarowana"
  klucz = {
    "x" => 1
  }
  wyrazy = ONP.new(lista, klucz)
  puts "Wynik: #{wyrazy.oblicz}"

end
