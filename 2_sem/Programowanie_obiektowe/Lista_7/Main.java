//Mikołaj Karapka, Lista 7: Program testujący

//Instrukcja kompilacji
//System: Windows
//Użyte środowisko: OpenJDK version "17.0.6"
//Polecenia użyte do kompilacji: 
//javac .\GUI_Package\*.java
//javac *.java
//Polecenie do uruchomienia programu: java Main <nazwa_pliku> <nazwa_klasy>
import GUI_Package.*;
public class Main {
    
    public static void main(String[] args){

        // Wypisanie błędu jeśli liczba argumentów jest mniejsza niż 2
        if(args.length < 2){
            System.out.println("Zbyt mala liczba argumentow!");
        }
        //w przeciwnym przypadku wywołanie odpowieniego interfejsu graficznego
        else if(args[1].equals("Pojazd") ){
            GUI test = new GUI(args[0], true);
        }
        else if(args[1].equals("Samochod") ){
            GUI_1 test_1 = new GUI_1(args[0]);
        }
        else if(args[1].equals("Jacht") ){
            GUI_2 test_2 = new GUI_2(args[0]);
        }
    }
}
