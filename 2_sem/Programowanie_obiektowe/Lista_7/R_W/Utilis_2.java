//Mikołaj Karapka, Lista 7: Implementacja klasy Utilis_2
package R_W;
import Interface.Samochod;
import java.io.*;

// Deklaracja klasy Utilis_2
public class Utilis_2 {

    // Metoda napisująca dany obiekt w konkretnym pliku
    public static void serializePojazd(Samochod pojazd, String fileName){
        try{
            FileOutputStream fileOut = new FileOutputStream(fileName);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(pojazd);
            out.close();
            fileOut.close();
            System.out.println("Obiekt został zapisany w nowym pliku.");
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }

    // Metoda zwracająca dany obiekt z konkretnego pliku
    public static Samochod deserializePojazd(String fileName){
        
        Samochod pojazd = null;
        try{
            FileInputStream fileIn = new FileInputStream(fileName);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            pojazd = (Samochod) in.readObject();
            in.close();
            fileIn.close();
        }
        catch (IOException | ClassNotFoundException e){
            serializePojazd(pojazd, fileName);
        }

        return pojazd;
    }
}
