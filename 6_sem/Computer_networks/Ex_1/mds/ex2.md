# Zadanie 2

Wszystkie sieci muszą zaczynać od prefixu `10.10.`

#### Sieć 1
```
bitowo: 10.10.000|0 0000.0000 0000 - 10.10.000|1 1111.1111 1111
zakres: 10.10.0.0 - 10.10.31.255
adres: 10.10.0.0/19
```

#### Sieć 2
```
bitowo: 10.10.001|0 0000.0000 0000 - 10.10.001|1 1111.255
zakres: 10.10.32.0 - 10.10.63.255
adres: 10.10.32.0/19
```

#### Sieć 3
```
bitowo: 10.10.010|0 0000.0000 0000 - 10.10.010|1 1111.255
zakres: 10.10.64.0 - 10.10.95.255
adres: 10.10.64.0/19
```

#### Sieć 4
```
bitowo: 10.10.011|0 0000.0000 0000 - 10.10.011|1 1111.255
zakres: 10.10.96.0 - 10.10.127.255
adres: 10.10.96.0/19
```

#### Sieć 5
```
bitowo: 10.10.1|000 0000.0000 0000 - 10.10.255.255
zakres: 10.10.128.0 - 10.10.255.255
adres: 10.10.128.0/17
```

### Jak zmieniła się liczba adresów?
- Na początku mieliśmy dostępne $2^{32-16} - 2$ adresów.
- Po podzieleniu każda sieć będzie miała:
    - Adres sieci
    - Adres rozgłoszeniowy
- Czyli będziemy mieli $2^{16}- (2\cdot5) =2^{16} - 10$ dostępnych adresów

### Minimalny rozmiar sieci
Aby uzyskać minimalny rozmiar sieci, to przy każdym następnym dzieleniu musimy zwiększać długość maski o 1. 

Zatem otrzymamy:

1. `00001010.00001010.10000000.00000000/17 = 10.10.128.0/17`
2. `00001010.00001010.01000000.00000000/18 = 10.10.64.0/18`
3. `00001010.00001010.00100000.00000000/19 = 10.10.32.0/19`
4. `00001010.00001010.00010000.00000000/20 = 10.10.16.0/20`
5. `00001010.00001010.00000000.00000000/20 = 10.10.0.0/20`

Najmniejsza podsieć, to ta z najmniejszą maską czyli 4 lub 5.
Jej rozmiar to:
$$2^{32 - 20}-2 = 2^{12}-2= 4094$$ 
