## Zadanie 1


### 1. $10.1.2.3/8$

```latex
10.1.2.3 = 00001010.00000001.00000010.00000011

00001010.00000001.00000010.00000011
11111111.00000000.00000000.00000000 (AND)
-----------------------------------------
00001010.00000000.00000000.00000000 = 10.0.0.0
```

Nie jest to pierwszy adres w danej sieci, więc jest to **adres komputera**.

- Adres sieci = $10.0.0.0$
- Adres rozgłoszeniowy = $10.255.255.255$
- Inny adres IP z tej sieci = $10.10.2.10$

### 2. $156.17.0.0/16$

```latex
156.17.0.0 = 10011100.00010001.00000000.00000000

10011100.00010001.00000000.00000000
11111111.11111111.00000000.00000000 (AND)
-----------------------------------------
10011100.00010001.00000000.00000000 = 156.17.0.0
```

Jest to pierwszy adres, więc jest **adresem sieci**.

- Adres sieci = $156.17.0.0/16$
- Adres rozgłoszeniowy = $156.17.255.255/16$
- Inny adres IP z tej sieci = $156.17.255.254/16$
### 3. $99.99.99.99/27$

```latex
99 .99 .99 .01100011
255.255.255.11100000 (AND)
---------------------
99 .99 .99 .01100000 = 99.99.99.96
```



- Adres sieci = $99.99.99.96/27$
- Adres rozgłoszeniowy = $99.99.99.011 11111 = 99.99.99.127/27$
- Inny adres IP z tej sieci = $99.99.99.100/27$

Zatem $99.99.99.99/27$ jest **adresem komputera**.

### 4. $156.17.64.4/30$

```latex
156.17 .64 .00000100
255.255.255.11111100(AND)
--------------------------
156.17 .64 .00000100 = 156.17.64.0
```

- Adres sieci = $156.17.64.4/30$
- Adres rozgłoszeniowy = $156.17 .64 .00000111 = 156.17 .64 .7/30$
- Inny adres IP z tej sieci = $156.17 .64 .6/30$

Zatem $156.17.64.4/30$ jest **adresem sieci**.

### 5. $123.123.123.123/32$

Jest to pojedynczy adres IP , ponieważ jak zrobimy (AND) z $255.255.255.255$ to otrzymamy ten sam adres, a że 32 bity są zajęte, to nie ma miejsca na inny adres.
