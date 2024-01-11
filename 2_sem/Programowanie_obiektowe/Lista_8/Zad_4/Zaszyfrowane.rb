# Mikołaj Karapka, lista 8, zadanie 4 - implementacja klasy Zaszyfrowane
# zaimportownie klasy Jawna
require_relative 'jawna'


class Zaszyfrowane
  #zmiennna przechowująca dany napis
  attr_accessor :napis

  # konstruktor przyjmujący argument i ustawiający zmienną napis
  def initialize(napis)
    self.napis = napis
  end

  # metoda do znajdowania zakodowanej litery
  def find_letter(letter, key)
    flag = false
    # ustawienie zmiennych na numery w kodzie ascii
    a = "a".ord
    z = "z".ord
      for i in a..z
        if key[i.chr] == letter
          flag = true
          return i.chr
        end
      end
    return flag
    end

  # metoda zwracająca odkodowany napis, dla danego klucza
  def odszyfruj(key)
    answer = Jawna.new("")
    answer_list = []
    letter  = ''

    # pętla przechodząca po kolei, po literach w danym napisie
    napis.each_char do |code_letter|

      # przypisanie odkodowanej litery i dodanie jej do listy
      letter = find_letter(code_letter,key)
      if letter == false
        puts "Zły klucz deszyfrujący!"
      end
      answer_list.push(letter)
    end

    # zamiana listy na zmienną typu string
    answer = answer_list.join("")
    return answer
  end

  # metdoda zwracająca zmienną typu string
  def to_s
    return @napis
  end
end
