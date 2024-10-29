## Zadanie 2
Aby dodaæ nowy component do windows forms bêdziemy chcieli u¿yæ do tego nowej klasy, która bêdzie dziedziczyæ po jakim obiekcie z windows forms.
Jednak, jeœli chcemy u¿yæ do tego klasy w wersji nowszej .net, to musimy w pliku xml wpisaæ
```
<UseWindowsForms>true</UseWindowsForms>
```
oraz wejœæ we w³aœciwoœci klasy i w target OS ustawiæ na Windows.

### Pytania
- Zapytaæ dlaczego jak zmienie wartoœæ jakieœ zmiennej dla danego obiektu, to czemu w desinerze siê to nie zmienia.