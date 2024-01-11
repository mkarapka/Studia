# Mikołaj Karapka, lista 8, zadanie 1 i 3 - implementacja klasy Function
class Function
  # zmienna przechowująca obiekt typu Proc
  attr_accessor :fun

  # konstruktor przyjmujący jako argument obiekt typu Proc i ustawiający
  # zmienną fun
  def initialize(fun)
    self.fun = fun
  end

  # metoda do zwaracania wartości funkcji dla danego x
  def value(x)
    begin
      return fun.call(x)
    rescue
      "Dany x nie należy do dziedziny funkcji!"
    end
  end

  # metoda używająca bisekcji, zwracająca miejsce zerowe dla danej funkcji
  def zero(a, b, precision)
    # Przypisanie wartości dla krańców przedziału
    f_a = value(a)
    f_b = value(b)

    # Jeżeli dwie wartości są większe od zera, to zwracamy nil
    return nil if f_a * f_b > 0

    # Wykonuj dopóki |b-a| jest większe od danej dokładności
    while (b - a).abs > precision
      # Ustawiamy środkowy x dla przedziału [a,b]
      c = (a + b) / 2.0
      f_c = value(c)

      # Jeśli f(a) * f(c) jest <= 0, to ustawiamy koniec przedziału dla c,
      # w przeciwnym razie początek na c
      if f_a * f_c <= 0
        b = c
        f_b = f_c
      else
        a = c
        f_a = f_c
      end
    end

    return c
  end

  # zwracanie przybliżonego pola pod wykresem, używając metedody trapezów
  def field(a,b)

    # ustawienie dokładności
    n = 1000.0
    x_delta = (b-a)/n
    x_0 = a
    # wyliczenie pierwszego trapezu
    sum = (value(a) + value(b))/2.0
    # i pozostałych

    for i in 1..(n-1)
      x_0 += x_delta
      sum = sum + value(x_0)
    end
    # zwrócenie wyniku
    return x_delta * sum
  end

  # oblicznie wartości (przybliżonej) pochodnej w punkcie x
  def deriv(x)

    # ustawienie dokładności
    h = 0.000001

    # i wyliczenie wartości podstawiając pod wzór (f(x+h) - f(x))/h
    f_x = value(x)
    f_x_h = value(x+h)
    result = (f_x_h - f_x)/h
    return result
  end

  # metoda wypisująca wykres funkcji dla przedziału [a,b] w konsoli
  def print_f(a,b)
    # ustawienie skoku dla x i y oraz początkowego y na 10
    pop_space = (a.abs).div(10)
    step_x = (b-a)/100.0
    step_y = 0.5
    current_x = a
    ceil = 10

    # funkcja, która wypisuje wartość górnej i dolnej współrzednej y
    def print_val(val,start,step_x)
      while (start + step_x) * start > 0
        print ' '
        start += step_x
      end
      puts "|#{val}"
    end
    # podzielenie odcinka [a,b] na 100 oraz odcinka [-10,10] na 40 punktów
    print_val(10,a,step_x)
    for y in 0..41
      for x in 0..101
        f_x = value(current_x)
        # jeśli dana wartość jest na danej wysokości, to wypisujemy dla nej *
        if f_x <= ceil and f_x > ceil - step_y
          print '*'

          # jeśli znak x-a się zmienił, to wypisujemy oś Y
        elsif current_x == 0
          print '|'
        elsif (current_x+step_x) * current_x < 0
          print '|'


        elsif y == 20 + 1
          # wypisanie a i b pod osią X
          if x == 0
            print a
          elsif x == 100
            print b

            # nie wypisanie tylu spacji ile cyfr ma liczba a, po to aby punkty
            # na danej lini się nie przesunęły
          elsif pop_space+1 > 0
            pop_space -= 1
          else
            print ' '
          end

          # wypisywanue osi X
        elsif y == 20
          print '-'
          # w przeciwnym razie wypisujemy spacje
        else
          print ' '
        end
        # przechodzimy do kolenego punktu x
        current_x = current_x + step_x
      end

      puts
      # zresetowanie bieżącego x oraz zejście w dół do kolejnego punktu y
      current_x = a
      ceil -= step_y

    end
    # wypisanie dolnego indeksu osi Y
    print_val(-10,a,step_x)
  end
end
