//Mikołaj Karapka - implementacja klasy Sortowanie
package package1;

public class Sortowanie implements Runnable {

    public Scalanie[] result; // tablica zawierająca scalone elementy
    public int size; // wielkość tablicy

    // konstruktor przyjmujący wielkość tablicy i tablice typu Scalanie
    public Sortowanie(int value, Scalanie[] array) {
        size = value;
        result = array;
    }

    // metoda zwracająca podliste od elementu o indeksie p do indeksu k
    public Scalanie[] split_up(int p, int k) {

        Scalanie[] array = new Scalanie[k - p + 1];
        for (int i = p; i <= k; i++) {
            array[i - p] = result[i];
        }
        return array;
    }

    // metoda przypisująca posortowane elementy z dwóch tablic do nowej tablicy 
    public void Sort(int value1,int value2,Scalanie[] array1,Scalanie[] array2){
        int i = 0, j = 0, x = 0;

        // wykonuj dopóki indeks pierwszej tablicy i drugiej są mniejsze
        // od ich wielkości
        while (i < value1 && j < value2) {

            if (array1[i].compareTo(array2[j]) < 0) {
                result[x] = array1[i];
                i++;

            } else {
                result[x] = array2[j];
                j++;
            }
            x++;
        }

        // jeżeli indeks pierwszej tablicy był równy jej wielkości,
        // to dodajemy wszystkie pozostałe wartości z drugiej tablicy 
        for (int p = i; p < value1; p++) {
            result[x] = array1[p];
            x++;
        }

        // analogicznie w tym przypadku
        for (int p = j; p < value2; p++) {
            result[x] = array2[p];
            x++;
        }
    }

    // metoda run, do tworzenia nowych wątków
    @Override
    public void run() {
        if (size == 1) {
            return;
        }

        // obliczenie środka oraz zadeklarowanie nowych obiektów typu 
        //Sortowanie odpowienio dla lewej i prawej części tablicy
        int mid = size / 2;
        Sortowanie left = new Sortowanie(mid, split_up(0, mid - 1));
        Sortowanie right = new Sortowanie(size - mid, split_up(mid, size - 1));

        // stworzenie nowych wątków
        Thread th_lf = new Thread(left);
        Thread th_rt = new Thread(right);

        // i ich uruchomienie
        th_lf.start();
        th_rt.start();

        try {
            // zatrzymanie wątków do czasu, aż nie wykonają się na podtablicach
            th_lf.join();
            th_rt.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // wykonanie sortowania dla posortowanej lewej i prawej podtablicy
        Sort(mid, size - mid, left.result, right.result);
    }
}
