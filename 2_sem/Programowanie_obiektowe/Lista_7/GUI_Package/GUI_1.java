//Mikołaj Karapka, Lista 7: Implementacja interfejsu graficznego dla klasy
//Samochod

package GUI_Package;

import javax.swing.*;
import Interface.Samochod;
import R_W.Utilis_2;

public class GUI_1 extends GUI {

    // deklaracja pola tekstowego dla koloru samochodu
    JTextField KolorField = new JTextField();

    public GUI_1(String filename) {
        
        // wywołanie konstruktora klasy bazowej
        super(filename,false);

        // dodanie nowego pola tekstowego do panelu
        JPanel panel = (JPanel) frame.getContentPane().getComponent(0);
        panel.add(new JLabel("Kolor:"));
        panel.add(KolorField);

        panel.add(spacer);
        panel.add(buttonsPanel);
        frame.pack();
        frame.setVisible(true);
    }

    // metoda wywoływana po kliknięciu przycisku
    public void button_clicked() {
        // tworzenie nowego obiektu klasy Samochod
        Samochod samochod = new Samochod(
            markaField.getText(),
            modelField.getText(),
            Integer.parseInt(rokField.getText()),
            KolorField.getText()
        );

        // serializacja obiektu i zapisanie go do pliku
        Utilis_2.serializePojazd(samochod, fileName);

        // odczytanie danych z pliku i wypisanie ich na ekranie
        System.out.print("Marka:" + Utilis_2.deserializePojazd(fileName).
        getMarka() + " ");
        System.out.print("Model:" + Utilis_2.deserializePojazd(fileName).
        getModel() + " ");
        System.out.print("Rok:" + Utilis_2.deserializePojazd(fileName)
        .getRok_produkcji() + " ");
        System.out.println("Kolor:" + Utilis_2.deserializePojazd(fileName).
        getKolor() + " ");
        System.out.println();
    }
}


