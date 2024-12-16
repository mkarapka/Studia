# Opis rozwiązanych zadań 

## Zadanie 1
- Wstawinono do folderu ex1 koncepcje strony
## Zadanie 2
Stworzono strukture opierającą się na przykładzie z wykładu:
- app
  - application
  - domain 
  
- domain
  - entities
  - value_objects
- infrastructure
  - servises
- main

## Zadanie 3
1. Zdefniowano obiekty takie jak:
   - **Entities:** Product, Card, Order 
   - **Values objects:** Price, Adress 
2. Zdefiniowano cykl życia entities
    - **Cart:** add_product oraz remove_product 
    - **Product:** in_stock, out_of_stock
    - **Order:** Created -> Paid -> Shipped
3. Agregaty 

    Czyli chcemy pogrupować logicznie encje i zachować spójność za pomocą innuch encji
    - **Cart** jest agregatem zwierającym **Product**
    - **Order** jest agregatem wykorzystującym **Cart**

## Zadanie 4
1. Zdefiniowanie Klas abstrakcyjnych dla repozytoriów 
2. Zaimplementowanie tych interfejsów w inmemory impemetation
3. Zrobienie klasy bazowej, która jest dziedziczone przez inne klasy inmemory

# Zadanie 5 - TO-DO