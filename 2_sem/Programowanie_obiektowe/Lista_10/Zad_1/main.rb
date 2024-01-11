# Mikołaj Karapka, lista 10, zadanie 1 - program testujący klasę Collection
# i Sorter

#Instrukcja uruchomienia programu
#System: Windows
#Użyte środowisko: ruby 3.2.2
#Polecenie uruchamiające program: ruby main.rb

# Szybsza metoda - insertion sort
require_relative 'sorter'
require_relative 'collection'
class Main
  array = Collection.new([1,4,9,3,21,12,54,34,12,4,2,3,18])
  array_1 = Collection.new([2,14,5,7,6,12,48,3,4,8,7,19,17,16])
  array2 = Sorter.new

  puts "Sortowanie przez wstawianie:"
  puts "Lista liczb na wejściu: #{array.to_s}"
  puts "Wynik: #{array2.insertion_sort(array)}"

  puts
  puts "Sortowanie bąbelkowe:"
  puts "Lista liczb na wejściu: #{array_1.to_s}"
  puts "Wynik: #{array2.bubbleSort(array_1)}"
end
