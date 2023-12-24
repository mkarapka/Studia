# Mikołaj Karapka, lista 10, zadanie 1 - program implementujący klasę
# Collection
class Collection
  # zmienna przechowująca listę
  attr_accessor :array

  # konstruktor inicjalizujący kolekcję z podaną listą
  def initialize(array)
    @array = array
  end

  # metoda zwracająca długość kolekcji
  def len
    @array.length
  end

  # metoda zwracająca element kolekcji na podstawie indeksu
  def getInd(index)
    @array[index]
  end

  # metoda zamieniająca miejscami elementy o podanych indeksach
  def swap(i, j)
    x = @array[i]
    @array[i] = @array[j]
    @array[j] = x
  end

  # metoda dodająca wartość do kolekcji
  def push(value)
    @array.push(value)
  end

  # metoda zwracająca reprezentację kolekcji jako ciąg znaków
  def to_s
    @array.to_s
  end
end
