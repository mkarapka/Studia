//Mikołaj Karapka, Lista 7: Implementacja klasy Utilis
package R_W;
import java.io.*;
import Interface.Pojazd;

// Deklaracja klasy Utilis
public class Utilis {

    // Metoda napisująca dany obiekt w konkretnym pliku
    public static void serializePojazd(Pojazd pojazd, String fileName){

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
    public static Pojazd deserializePojazd(String fileName){

        Pojazd pojazd = null;
        try{
            FileInputStream fileIn = new FileInputStream(fileName);
            ObjectInputStream in = new ObjectInputStream(fileIn);
            pojazd = (Pojazd) in.readObject();
            in.close();
            fileIn.close();
        }
        
        catch (IOException | ClassNotFoundException e){
            serializePojazd(pojazd, fileName);
        }

        return pojazd;
    }
}
