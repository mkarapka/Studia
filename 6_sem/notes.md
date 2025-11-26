# Plan na prezentacje
## Plan prezentacji
- Małe przypomnienie
  - Struktura blockchain (bitcoin)
  - Podstawowe pojęcia
    - Leadger
    - Merkle Tree
    - Miner and Emitter
    - P2P
    - Blockchain Proof (POW, POS)
    - Budowanie bloku
    - minig / mining pools

- POW w Bitcoin - dlaczego to jest takie trudne do zgadnięcia
- Typy blockchain ze względu na ich strukture, desin itd
- ZCASH vs Bitcoin
  - Tworzenie bloków - ZCASH vs Bitcoin
  - Merkle Tree - Dlaczego O(log n)
- Secretsharing
- Homomorfizm
- Zero Knowledge





- Blockchain w helthcare




---

## 🧭 **Plan prezentacji: Blockchain Crypto Foundations – Deep Dive**

### 1. **Wprowadzenie – szybkie przypomnienie**

Krótki przegląd kluczowych pojęć i struktury blockchaina na przykładzie Bitcoina: ledger, Merkle Tree, P2P, miner/emitter, proof mechanisms, budowa bloku, mining i mining pools.

---

### 2. **Od transakcji do zatwierdzenia bloku**

Przepływ procesu: od podpisania transakcji, przez mempool i selekcję do bloku, aż po zatwierdzenie i rozgłoszenie. Omówienie, gdzie w tym wszystkim stosowana jest kryptografia: podpisy, haszowanie, Merkle Tree, konsensus.

---

### 3. **Typy blockchainów**

Rozróżnienie blockchainów: publiczne i prywatne, permissioned i permissionless. Przykłady: Bitcoin, Ethereum, Hyperledger, Ripple. Kontekst zastosowania różnych modeli w zależności od potrzeb biznesowych lub społecznościowych.

---

### 4. **Porównanie podejść: Bitcoin vs Zcash vs Monero**

Trójstronne zestawienie podejść do prywatności transakcji i kryptografii:

* Bitcoin jako transparentny system,
* Zcash z opcjonalną prywatnością i zk-SNARKs,
* Monero jako domyślnie anonimowy blockchain oparty na ring signatures i stealth addressach.
  Różnice w podejściu do PoW, struktury transakcji, zaufania i efektywności.

---

### 5. **Mechanizmy kryptograficzne w praktyce**

Przegląd tego, jak różne kryptograficzne narzędzia są stosowane w blockchainie: podpisy cyfrowe, funkcje skrótu, zero-knowledge proofs, obfuskacja w Monero, mechanizmy tajnego dzielenia informacji, commitmenty i homomorficzne szyfrowanie. Wszystko z naciskiem na kontekst użycia, nie na matematykę.

---

### 6. **Mining w różnych sieciach**

Porównanie podejścia do kopania w trzech blockchainach:

* Bitcoin i jego ASIC-owy SHA-256d,
* Zcash z RAM-zależnym Equihash,
* Monero z CPU-friendly RandomX – i jego motywacją przeciwdziałania centralizacji.

---

### 7. **Zastosowanie blockchaina w ochronie zdrowia**

Scenariusz użycia blockchaina do zarządzania dokumentacją pacjentów: szyfrowanie danych, udostępnianie ich wybranym podmiotom z rejestrowaniem dostępu, a nie zawartości. Przykłady rozwiązań z ACL, SMPC, prywatnych blockchainów z PoA lub BFT.

---

### 8. **Wnioski i trendy**

Podsumowanie różnic w projektowaniu blockchainów, kompromisów między prywatnością, decentralizacją i wydajnością. Rola kryptografii jako podstawy zaufania. Zarys przyszłych kierunków rozwoju: skalowalność, prywatność, interoperacyjność.

---

### 9. **Q\&A / Dyskusja**

Otwarcie na pytania i komentarze od uczestników.
