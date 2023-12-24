// Mikołaj Karapka,Lista 6,Zadanie 4 - plik testujący program

// Instrukcja kompilacji:
// System: Windows
// Użyte środowisko: OpenJDK version "17.0.6"
// Polecenie użyte do kompilacji (w folderze "Zad_4"): 
// javac *.java
// Polecenie do uruchomienia programu: //java Main
import package1.Scalanie;
import package1.Sortowanie;
public class Main {
    public static void main(String[] args) throws Exception {

        // utworzenie tablicy typu Scalanie []
        Scalanie [] array = new Scalanie[10];

        // przykładowe wartości
        array[0] = new Scalanie(13);
        array[1] = new Scalanie(4);
        array[2] = new Scalanie(8);
        array[3] = new Scalanie(3);
        array[4] = new Scalanie(20);
        array[5] = new Scalanie(40);
        array[6] = new Scalanie(1);
        array[7] = new Scalanie(10);
        array[8] = new Scalanie(14);
        array[9] = new Scalanie(8);
        
        // utworzenie obiektu typu Thread
        Sortowanie cos = new Sortowanie(10, array);
        Thread thread = new Thread(cos);
    
        // uruchomienie wątku oraz zatrzymanie go aż inne podwątki się wykonają
        thread.start();
        thread.join();

        // wypisanie wyniku
        System.out.println("Posortowane elementy tablicy:");
        for (Scalanie s : array) {
            System.out.print(s + " ");
        }
    }
}