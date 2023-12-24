# Mikołaj Karapka, lista 8, zadanie 1 i 3 - program sprawdzający poprawność
# klasy Function

# Instrukcja uruchomienia programu
# System: Windows
# Użyte środowisko: ruby 3.2.2
# Polecenie uruchamiające program: ruby main.rb

# zaimportowanie klasy Function
require_relative 'function'
class Main
  a = proc { |x| x*x*Math.sin(x) }
  b = proc { |x| 2 * x**2 + 3*x - 2 }

  fun_1 = Function.new(a)
  fun_2 = Function.new(b)

  puts "Funkcja: x^2 * sin(x)"
  puts "Wartość dla x = 0: #{fun_1.value(0).round(4)}"
  puts "Wartość dla x = 2: #{fun_1.value(2).round(4)}"
  puts "Wartość dla x = -4: #{fun_1.value(-4).round(4)}"

  print "Miejsce zerowe dla przedziału [2,6] z dokładnością do 0.0001:  "
  puts fun_1.zero(2,6,0.0001).round(4)
  puts "Pole pod wykresem dla przedziału [7,9]:  #{fun_1.field(7,9).round(4)}"
  puts "Szkic funkcji dla przedziału [-5,5]"
  fun_1.print_f(-5,5)

  puts "Funkcja: 2x^2 + 3x - 2"
  puts "Wartość dla x = 0: #{fun_2.value(0).round(4)}"
  puts "Wartość dla x = -2: #{fun_2.value(-2).round(4)}"
  puts "Wartość dla x = 3: #{fun_2.value(3).round(4)}"
  print "Miejsce zerowe dla przedziału [0,8] z dokładnością do 0.00001:  "
  puts fun_2.zero(0,8,0.00001).round(4)
  print "Pole pod wykresem dla przedziału [0.5,2]:  "
  puts fun_2.field(0.5,2).round(4)
  puts "Szkic funkcji dla przedziału [-2,7]"
  fun_2.print_f(-2,7)
end
