// Mikołaj Karapka - implementacja klasy Scalanie
package package1;

// deklaracja klasy implementującej Comparable
public class Scalanie implements Comparable<Scalanie> {
    int value;
    
   // konstruktor przypisujący wartość elementu
    public Scalanie(int value) {
        this.value = value;
    }

    // metoda porównująca wartość elementu z innym elementem
    @Override
    public int compareTo(Scalanie other) {
        return Integer.compare(value, other.value);
    }

    // konwersja wartości elementu z typu int na String w celu wypisania 
    //na wyjściu
    @Override
    public String toString() {
        return String.valueOf(value);
    }

}
