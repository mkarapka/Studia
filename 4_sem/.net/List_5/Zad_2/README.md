# Lista 5
| 1  | 2  |  3 | 4 |
| -----------------|
| 3p | 3p | 1p | - |

## Zadanie 1
Dlaczego w pierwszym aby program dzia³a³ musimy daæ Tryb Release zamiast Debug

### OdpowiedŸ: 
Po prostu Debug wp³ywa na wydajnoœæ, czasem warunkach zamiast 1 zmiennej przechowuje dodatkowo drug¹.


## Zadanie 2
- Nie rozumiem dlaczego odwo³uj¹c siê ca³y czas do indexes[0] otrzymujemy nowy indeks.
- Dlaczego nie mogê zrobiæ 
	```
		if(dictionary.ContainsKey(index.ToString())){
			return dictionary.TryGetValue(index.ToString(), out result)
		}
		else{
			return false
		}
	``` 
W sumie chodzi mi tutaj o to, ¿e czemu muszê przypisaæ jak¹œ wartoœæ dla result 

### OdpowiedŸ:
- W tym indexes[0] to odwo³ujemy siê do pierwszej tablicy po prostu
- I w tym result musimy przypisaæ jak¹œ zmienn¹, bo jak w C# mamy typ out to musimy przypisaæ mu wartoœæ przed zakoñczeniem funkcji. 

## Zadanie 3
Nie rozumiem, sutuacji napisanej przez mnie 
Czyli wywo³uje w g³ównej metodzie asynchronicznie **PrintSome**, jej wykonanie trwa d³u¿ej ni¿ kolejne opóŸnienie w g³ównej metodzie. Kiedy wszystkie funkcje w g³ónej metodzie siê wykonaj¹, to nie czekaj¹ na zakoñczenie funkcji **PrintSome** i koñczy siê program. 

### OdpowiedŸ: 
- W skrócie interpreter C# jest g³upi XD, jeœli skoñczy siê funkcja Main  to nie czeka na skoñczenie innych funkcji. 

# Zadanie 4
Nie wiem dlaczego nie mogê zrobiæ takiego w³aœnie rozwi¹zania

### OdpowiedŸ:
- TO-DO - Trzeba na to spojrzeæ jeszcze. 