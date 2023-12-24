//Mikołaj Karapka, Lista 7: Implementacja klasy Pojazd
package Interface;

import java.io.Serializable;

public class Pojazd implements Serializable{

    // pola prywatne
    private String marka;
    private String model;
    private int rok_produkcji;

    // konstruktory
    public Pojazd(){}

    public Pojazd(String marka, String model, int rok_produkcji){
        this.marka = marka;
        this.model = model;
        this.rok_produkcji = rok_produkcji;
    }

    // metody dostępowe (gettery) do pól prywatnych
    public String getMarka() {return marka;}
    public String getModel() {return model;}
    public int getRok_produkcji() {return rok_produkcji;}

    // metody ustawiające (settery) pola prywatne
    public void setMarka(String marka) {this.marka = marka;}
    public void setModel(String model) {this.model = model;}
    public void setRok_produkcji(int rok_produkcji) {this.rok_produkcji = rok_produkcji;}

    // nadpisana metoda toString() zwracająca rok produkcji
    @Override
    public String toString() {
        return String.valueOf(getRok_produkcji());
    }
}

