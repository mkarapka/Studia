//Mikołaj Karapka, Lista 7: Implementacja interfejsu graficznego dla klasy
//Pojazd
package GUI_Package;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import Interface.Pojazd;
import R_W.Utilis;

// Deklaracja klasy GUI dziedziczącej po klasie JComponent oraz implementującej
// interfejs ActionListener 
public class GUI extends JComponent implements ActionListener{
    // Deklaracja pól klasy, reprezentujących pola tekstowe oraz przyciski
    JTextField markaField = new JTextField(20);
    JTextField modelField = new JTextField(20);
    JTextField rokField = new JTextField(20);
    JPanel buttonsPanel, spacer;
    JFrame frame;
    JButton button, cancel;
    String fileName;
    static Boolean flag = true;

    // Konstruktor klasy GUI
    public GUI(String filename, Boolean flag) {

        // Inicjalizacja pól klasy
        this.fileName = filename;

        // Utworzenie nowego okna JFrame
        frame = new JFrame();

        // Utworzenie nowego panelu JPanel
        JPanel panel = new JPanel();

        // Ustawienie domyślnego działania po zamknięciu okna JFrame
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Ustawienie layoutu panelu na BoxLayout w kierunku Y
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        // Ustawienie marginesów panelu
        panel.setBorder(BorderFactory.createEmptyBorder(30, 30, 
        10, 30));

        // Utworzenie przycisków i przypisanie im ActionListenera
        button = new JButton("Save");
        cancel = new JButton("Exit");
        button.addActionListener(this);
        cancel.addActionListener(this);

        // Inicjalizacja pól buttonsPanel i spacer
        buttonsPanel = new JPanel();
        spacer = new JPanel(); 

        //Stworzenie Layout'u panelu dla przycisków oraz dodanie do niego 
        //przycisków
        buttonsPanel.setLayout(new BoxLayout(buttonsPanel, BoxLayout.X_AXIS));
        buttonsPanel.add(Box.createRigidArea(new Dimension
        (34, 0))); 
        buttonsPanel.add(cancel);
        buttonsPanel.add(Box.createHorizontalGlue());
        buttonsPanel.add(button);
        buttonsPanel.setAlignmentX(Component.LEFT_ALIGNMENT); 
        buttonsPanel.add(Box.createHorizontalGlue());
    
        // Dodanie etykiet i pól tekstowych do panelu
        panel.add(new JLabel("Marka: "));
        panel.add(markaField);
        panel.add(new JLabel("Model: "));
        panel.add(modelField);
        panel.add(new JLabel("Rok produkcji: "));
        panel.add(rokField);

        // Ustawienie preferowanej wielkości panelu spaceru
        spacer.setPreferredSize(new Dimension(10, 10));

        // Sprawdzenie flagi i dodanie paneli przycisków i spacji między nimi 
        // do panelu, tylko jeśli flaga jest ustawiona na wartość true
        if(flag == true){
        panel.add(spacer);
        panel.add(buttonsPanel);
        }

        // Dodanie panelu do zawartości okna
        frame.getContentPane().add(panel);

        // Dopasowanie rozmiaru okna do zawartości i wyświetlenie go
        frame.pack();
        frame.setVisible(true);
        }
    
    //Metoda, która dokonuje operacji na pliku po kliknięciu przycisku
    public void button_clicked(){

        //Wywołanie konstruktora dla danych argumentów
        Pojazd pojazd = new Pojazd(markaField.getText(),modelField.getText(),
        Integer.parseInt(rokField.getText()));
        
        // Zapisanie obiektu w pliku za pomocą klasy Utilis
        Utilis.serializePojazd(pojazd, fileName);

        //Wypisanie parametrów po przez ich odczytanie z pliku
        System.out.print("Marka:" + Utilis.deserializePojazd(fileName).
        getMarka() + " ");
        System.out.print("Model:" + Utilis.deserializePojazd(fileName).
        getModel() + " ");
        System.out.print("Rok:" + Utilis.deserializePojazd(fileName)
        .getRok_produkcji() + " ");
    }

    // Metoda, która implementuje interfejs ActionListener
    @Override
    public void actionPerformed(ActionEvent e) {

        // Sprawdznie, który przycisk został wciśnięty oraz 
        // wykonanie odpowiedniego działania dla danego zdarzenia
        if(e.getSource() == button){
            button_clicked();
        }

        else if(e.getSource() == cancel){
            frame.dispose();
        }
    }

}
