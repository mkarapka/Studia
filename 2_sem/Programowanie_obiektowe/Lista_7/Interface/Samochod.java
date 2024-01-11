//Mikołaj Karapka, Lista 7: Implementacja klasy Samochod
package Interface;

public class Samochod extends Pojazd {
    // Deklarujemy prywatne pole koloru
    private String kolor;

    // Konstruktor klasy Samochod, który przyjmuje 4 parametry: markę, model, 
    //rok produkcji oraz kolor samochodu
    public Samochod(String marka,String model,int rok_produkcji, String kolor){
        
        // Wywołujemy konstruktor klasy nadrzędnej Pojazd, przekazując mu jako 
        //argumenty markę, model oraz rok produkcji
        super(marka, model, rok_produkcji);
        
        // Inicjalizujemy pole koloru
        this.kolor = kolor;
    }

    // Getter dla pola koloru
    public String getKolor() {
        return kolor;
    }

    // Setter dla pola koloru
    public void setKolor(String kolor) {
        this.kolor = kolor;
    }

}
