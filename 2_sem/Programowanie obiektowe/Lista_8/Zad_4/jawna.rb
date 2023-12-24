# Mikołaj Karapka, lista 8, zadanie 4 - implementacja klasy Jawna
# Importowanie klasy Zaszyfrowane
require_relative 'zaszyfrowane'
class Jawna
  # zmienna przechowująca dany wyraz
  attr_accessor :napis

  # konstruktor przyjmujący argument i ustawiający zmienną napis
  def initialize(napis)
    self.napis = napis
  end

  # metoda szyfrująca dany napis, dla danego klucza
  def zawszyfruj(key)
    szyfr = Zaszyfrowane.new("")
    szyfr_list = []

    # pętla przechodząca po każdej literze w wyrazie
    napis.each_char do |letter|

      #dodanwanie do listy zakodowanej litery
      if key[letter].nil?
        puts "Zły klucz szyfrujący!"
      end
      szyfr_list.push(key[letter])
    end

    #zamiana listy na zmienną typu string
    szyfr.napis = szyfr_list.join("")
    return szyfr

    # metdoda zwracająca zmienną typu string
    def to_s
      return @napis
    end
  end
end
