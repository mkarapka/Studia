Problem z **redefinicją** w Twoim kodzie wynika z tego, że w pliku `m.cpp` dołączasz `fs.cpp` za pomocą:

```cpp
#include "fs.cpp"
```

To powoduje, że cały kod z `fs.cpp` jest **wklejany** do `m.cpp` podczas kompilacji. Następnie, gdy kompilator próbuje skompilować `fs.cpp` jako osobny plik, te same funkcje i zmienne są definiowane ponownie. W rezultacie podczas linkowania występuje błąd `multiple definition`.

---

### Dlaczego tak się dzieje?

1. **`#include "fs.cpp"`**:
   - To wstawia cały kod z `fs.cpp` do `m.cpp`. W efekcie funkcje i zmienne z `fs.cpp` są definiowane w `m.cpp`.

2. **Osobna kompilacja `fs.cpp`**:
   - Gdy kompilator kompiluje `fs.cpp` jako osobny plik, te same funkcje i zmienne są definiowane ponownie.

3. **Linkowanie**:
   - Podczas linkowania kompilator widzi te same definicje funkcji i zmiennych w dwóch różnych plikach obiektowych (`m.o` i `fs.o`), co powoduje błąd `multiple definition`.

---

### Jak to naprawić?

Aby uniknąć tego problemu, należy użyć **nagłówków (`.h`)** i **plików implementacyjnych (`.cpp`)** w odpowiedni sposób.

---

### Poprawiona struktura plików

#### 1. Utwórz plik nagłówkowy `fs.h`

Przenieś deklaracje funkcji i zmiennych globalnych z `fs.cpp` do pliku nagłówkowego `fs.h`. Deklaracje to nagłówki funkcji (bez ich implementacji) oraz zmienne globalne oznaczone jako `extern`.

Przykład `fs.h`:

```cpp
#ifndef FS_H
#define FS_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Struktura pair
struct pair {
  pair(int y, int x) : y(y), x(x) {}
  int y;
  int x;

  bool operator==(const pair &other) const {
    return y == other.y && x == other.x;
  }
};

// Funkcja haszująca dla pair
struct pairHash {
  std::size_t operator()(const pair &p) const {
    return std::hash<int>()(p.y) ^ (std::hash<int>()(p.x) << 1);
  }
};

// Typy pomocnicze
typedef std::vector<std::vector<char>> vec2char;
typedef std::unordered_set<pair, pairHash> pair_set;

// Deklaracja zmiennej globalnej
extern std::unordered_map<char, pair> UDLR;

// Deklaracje funkcji
pair_set get_points(vec2char &board, char letter);
pair add(vec2char &board, const pair &ran_coords, pair &move);
int potencial(pair_set &rangers_state, pair_set &goal_points);
std::vector<result> next_moves(pair_set &rangers_state, vec2char &board,
                               pair_set &goal_points);
std::string Astar(vec2char &board, pair_set &start_points,
                  pair_set &goal_points);

#endif // FS_H
```

---

#### 2. Zmień `fs.cpp`

W pliku `fs.cpp` zaimplementuj funkcje i zdefiniuj zmienne globalne. Dołącz `fs.h` na początku pliku.

Przykład `fs.cpp`:

```cpp
#include "fs.h"

// Definicja zmiennej globalnej
std::unordered_map<char, pair> UDLR = {
    {'U', {-1, 0}},
    {'D', {1, 0}},
    {'L', {0, -1}},
    {'R', {0, 1}},
};

// Implementacje funkcji
pair_set get_points(vec2char &board, char letter) {
  pair_set points;
  for (int y = 0; y < board.size(); y++) {
    for (int x = 0; x < board[0].size(); x++) {
      char field = board[y][x];
      if (field == letter || field == 'B') {
        points.insert(pair(y, x));
      }
    }
  }
  return points;
}

pair add(vec2char &board, const pair &ran_coords, pair &move) {
  pair new_coords = {ran_coords.y + move.y, ran_coords.x + move.x};
  return board[new_coords.y][new_coords.x] == '#' ? ran_coords : new_coords;
}

int potencial(pair_set &rangers_state, pair_set &goal_points) {
  int maxi = 0;
  for (const pair &r : rangers_state) {
    int min_dist = std::numeric_limits<int>::max();
    for (const pair &g : goal_points) {
      int dist = std::abs(r.x - g.x) + abs(r.y - g.y);
      min_dist = std::min(min_dist, dist);
    }
    maxi = std::max(maxi, min_dist);
  }
  return maxi;
}

std::vector<result> next_moves(pair_set &rangers_state, vec2char &board,
                               pair_set &goal_points) {
  std::vector<result> res;
  for (auto &move : UDLR) {
    pair_set new_rangers_state;
    for (const pair &r : rangers_state) {
      new_rangers_state.insert(add(board, r, move.second));
    }
    res.push_back({potencial(new_rangers_state, goal_points), new_rangers_state,
                   std::string(1, move.first)});
  }
  return res;
}

std::string Astar(vec2char &board, pair_set &start_points,
                  pair_set &goal_points) {
  std::string path = "";

  int f = potencial(start_points, goal_points);
  std::priority_queue<result> pq;
  pq.emplace(f, start_points, path);

  while (!pq.empty()) {
    result ran_node = pq.top();
    pq.pop();

    if (std::all_of(ran_node.state.begin(), ran_node.state.end(),
                    [&](const pair &field) {
                      return board[field.y][field.x] == 'G' or
                             board[field.y][field.x] == 'B';
                    }))
      return ran_node.path;

    for (auto &m : next_moves(ran_node.state, board, goal_points)) {
      int g = ran_node.path.length() + 1;
      pq.emplace(m.f + g, m.state, ran_node.path + m.path);
    }
  }
  return path;
}
```

---

#### 3. Zmień `m.cpp`

W pliku `m.cpp` dołącz `fs.h` zamiast `fs.cpp`.

Przykład `m.cpp`:

```cpp
#include <fstream>
#include <iostream>
#include "fs.h"

int main() {
  std::ifstream file_in("zad_input.txt");
  vec2char board;

  std::string line;
  while (std::getline(file_in, line)) {
    std::vector<char> row;
    line.pop_back();
    for (char &field : line) {
      row.push_back(field);
    }
    board.push_back(row);
  }
  file_in.close();

  for (auto &line : board) {
    for (auto &field : line) {
      std::cout << field;
    }
    std::cout << std::endl;
  }

  std::string path = "LLLR";
  std::ofstream file_out("zad_output.txt");
  file_out << path;
  file_out.close();
}
```

---

#### 4. Kompilacja

Teraz możesz skompilować program za pomocą:

```bash
g++ -std=c++17 -o m m.cpp fs.cpp
```

---

### Wyjaśnienie

1. **Nagłówki (`fs.h`)**:
   - Deklaracje funkcji i zmiennych globalnych są umieszczone w pliku nagłówkowym.
   - Dzięki temu `fs.cpp` i `m.cpp` mogą współdzielić te same deklaracje.

2. **Definicje w `fs.cpp`**:
   - Funkcje i zmienne globalne są zdefiniowane tylko w jednym miejscu (`fs.cpp`), co zapobiega błędom `multiple definition`.

3. **Dołączanie `fs.h`**:
   - Plik `m.cpp` dołącza `fs.h`, aby uzyskać dostęp do funkcji i zmiennych z `fs.cpp`.

---

Po tych zmianach Twój kod powinien kompilować się i działać poprawnie.


```python
def potencial(rangers_state: np.ndarray, goal_points: np.ndarray) -> int:
    # Obliczamy odległości Manhattan między każdym punktem w rangers_state a każdym punktem w goal_points
    distances = np.abs(rangers_state[:, np.newaxis] - goal_points).sum(axis=2)

    # Dla każdego punktu w rangers_state znajdujemy minimalną odległość do punktów w goal_points
    min_distances = np.min(distances, axis=1)

    # Zwracamy maksymalną z minimalnych odległości
    return np.max(min_distances)
```
