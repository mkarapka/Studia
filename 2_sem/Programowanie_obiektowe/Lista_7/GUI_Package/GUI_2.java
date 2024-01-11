//Mikołaj Karapka, Lista 7: Implementacja interfejsu graficznego dla klasy
//Jacht
package GUI_Package;

import javax.swing.*;
import Interface.Jacht;
import R_W.Utilis_3;
public class GUI_2 extends GUI{

    // Deklaracja pola tekstowego zanurzenieField
    JTextField zanurzenieField = new JTextField();

    // Konstruktor klasy GUI_2 przyjmujący jako argument nazwę pliku
    public GUI_2(String filename) {
    
    // Wywołanie konstruktora klasy bazowej z flagą ustawioną na false
    super(filename,false); 

    // Dodanie nowego pola tekstowego zanurzenieField do panelu
    JPanel panel = (JPanel) frame.getContentPane().getComponent(0);
    panel.add(new JLabel("Zanurzenie:"));
    panel.add(zanurzenieField);

    // Dodanie paneli spacer oraz buttonsPanel do panelu głównego oraz 
    //wyświetlenie okna
    panel.add(spacer);
    panel.add(buttonsPanel);
    frame.pack();
    frame.setVisible(true);
    }

    // Metoda obsługująca kliknięcie przycisku
    public void button_clicked(){

    // Stworzenie obiektu jachtu na podstawie wprowadzonych danych
    Jacht jacht = new Jacht(markaField.getText(),modelField.getText(),
    Integer.parseInt(rokField.getText()), Integer.parseInt(zanurzenieField
    .getText()));
        
    // Serializacja obiektu do pliku
    Utilis_3.serializePojazd(jacht, fileName);

    // Wyświetlenie informacji o zdeserializowanym obiekcie
    System.out.print("Marka:" + Utilis_3.deserializePojazd(fileName).
    getMarka() + " ");
    System.out.print("Model:" + Utilis_3.deserializePojazd(fileName).
    getModel() + " ");
    System.out.print("Rok:" + Utilis_3.deserializePojazd(fileName)
    .getRok_produkcji() + " ");
    System.out.println("Zanurzenie:" + Utilis_3.deserializePojazd(fileName).
    getZanurzenie() + " ");
    System.out.println();
}

}
