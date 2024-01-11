# Mikołaj Karapka, lista 8, zadanie 3 - implementacja klasy ONP
class ONP
  # zmienne przechowujące liste i klucz
  attr_accessor :lista, :key


  def initialize(lista, key = nil)
    if key.nil?
      init_one_arg(lista)
    else
      init_two_arg(lista,key)
    end
  end

  # konstruktor przyjmujący argument i ustawiający liste
  def init_one_arg(lista)
    self.lista = lista
  end

  # konstruktor, który dodatkowo ustawia dany klucz
  def init_two_arg(lista, key)
    self.lista = lista
    self.key = key
  end

  # metoda do sprawdzania czy element listy jest operatorem
  def check(sign)
    if sign == '+' or sign == '-' or sign == '*' or sign == '/'
      return true
    else
      return false
    end
  end

  # wykonywanie danej operacji dla konkretnego operatora
  def operation(op, liczba_1, liczba_2)
    case op
    when '+'
      return liczba_1 + liczba_2
    when '-'
      return liczba_1 - liczba_2
    when '*'
      return liczba_1 * liczba_2
    when '/'
      return liczba_1 / liczba_2
    end
  end

  # metoda do wypisywania stosu
  def print_stos(result)
    print "Stos: "
    for i in 0..(result.length-1)
      if !check(result[i]) and result[i]
        print "#{result[i]}, "
      end
    end
    puts ""
  end

  # wyliczanie wyrażenia w postaci ONP
  def oblicz
    flag = true
    result = []
    long = lista.length
    i = 0
    while i < long
      # dodawanie do stotu kolejnych elementów
      if lista[i].class == String and !check(lista[i])
        if key[lista[i]].nil?
          flag = false
          break
        else
          lista[i] = key[lista[i]]
        end
      end
      result.append(lista[i])
      print_stos(result)

      # jeśli element jest operatorem to obliczamy dwa pierwsze
      # literały ze stosu
      if check(lista[i])

        # pobieranie operatora oraz dwóch zmiennych ze stosu
        op = result.pop()
        liczba_2 = result.pop()
        liczba_1 = result.pop()

        # i ich wyliczenie oraz ponowne dodanie do stosu
        begin
          liczba_wyk = operation(op, liczba_1, liczba_2)
          result.append(liczba_wyk)
        rescue
          print "Złe dane wejściowe!"
          end
      end
      i+=1
    end
    # zwrócenie wyniku
    if flag
      return result[0]
    else
      return "Nieznana zmienna"
    end
  end
end
