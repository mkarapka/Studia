# MCTS
## 2 main phases:
- Expansion
- Exploration

1. Wyliczliamy maxymalne UCB dla naszych dzieci
2. Wybieramy ten z maxymalnym
3. 2 warunki
  - Jeśli nie był odwiedzany:
    Zrób eksploracje
  - Wpp:
    Zrób ekspansje
4. Jeśli dotarłeś do stanu końcowego
    zwróć wartość danego stanu
5. Zrób rollout

P0 won-tied-lost 3-0-7 times.

________________________________________________________
Executed in  153.32 secs    fish           external
   usr time  150.04 secs    0.00 millis  150.04 secs
   sys time    3.62 secs    1.15 millis    3.62 secs


Sortowanie w alphabeta search
