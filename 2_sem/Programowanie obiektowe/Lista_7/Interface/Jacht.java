//Mikołaj Karapka, Lista 7: Implementacja klasy Jacht
package Interface;

public class Jacht extends Pojazd{
    
    // Konstruktor klasy Jacht, wywołuje konstruktor klasy nadrzędnej Pojazd
    public Jacht(String marka, String model, int rok_produkcji,int zanurzenie){
        super(marka, model, rok_produkcji);
        this.zanurzenie = zanurzenie;
    }

    // prywatne pole klasy Jacht
    private int zanurzenie; 

    // Metoda getter dla pola zanurzenie
    public int getZanurzenie() {return zanurzenie;}

    // Metoda setter dla pola zanurzenie
    public void setZanurzenie(int zanurzenie) {
        this.zanurzenie = zanurzenie;
    }
}

