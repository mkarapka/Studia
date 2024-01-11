# Mikołaj Karapka, lista 10, zadanie 1 - program implementujący klasę
# Sorter
require_relative 'collection'
class Sorter

  # metoda implementująca sortowanie przed wstawianie
  def insertion_sort(collection)
    n = collection.len
    for i in 0..n - 1

      # zmienna, która będziemy porównywać
      check = collection.getInd(i)
      j = i - 1
      p = i

      # przechodzimy pętlą po liście uporządkowanej
      while j >= 0

        # jeśli zmienna check jest mniejsza od sprawdzanej zmiennej,
        # to je zamieniamy
        if check < collection.getInd(j)
          collection.swap(p,j)
          p -= 1
        else

          # w przeciwnym razie kończymy działanie pętli
          break
        end
        j -= 1
      end
    end
    collection
  end

  # metoda implementująca sortowanie bąbelkowe
  def bubbleSort(array)
    for i in 0..array.len-2
      for j in 0..array.len-2
        if array.getInd(j) > array.getInd(j+1)
        array.swap(j,j+1)
        end
      end
    end
   array
  end
end

