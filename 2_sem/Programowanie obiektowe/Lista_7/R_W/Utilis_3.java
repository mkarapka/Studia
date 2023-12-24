//Mikołaj Karapka, Lista 7: Implementacja klasy Utilis_3
package R_W;
import java.io.*;
import Interface.Jacht;

// Deklaracja klasy Utilis_3
public class Utilis_3 {

    // Metoda napisująca dany obiekt w konkretnym pliku
    public static void serializePojazd(Jacht pojazd, String fileName){
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
    public static Jacht deserializePojazd(String fileName){
        Jacht pojazd = null;
        try{
            FileInputStream fileIn = new FileInputStream(fileName);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            pojazd = (Jacht) in.readObject();
            in.close();
            fileIn.close();
        }
        catch (IOException | ClassNotFoundException e){
            serializePojazd(pojazd, fileName);
        }
        return pojazd;
    }
}
