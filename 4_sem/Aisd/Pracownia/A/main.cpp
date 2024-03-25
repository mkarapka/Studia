#include <algorithm>
#include <iostream>
#include <utility>

void set_starts(std::pair<int, int> starts[], const std::pair<int, int> tree[],
                int n) {
    int i = 0;
    while (i < n - 1) {
        int sum = 0, check = tree[i].first, j = i;
        starts[check - 1].first = i;
        while (j < n and tree[j].first == check) {
            sum++;
            j++;
        }
        starts[check - 1].second = starts[check - 1].first + sum;
        i = j;
    }
}

bool is_ancesor(const std::pair<int, int> rels[], const int deg_in[],
                const int deg_out[], const int i) {
    int a = rels[i].first, b = rels[i].second;
    if (deg_in[a - 1] < deg_in[b - 1] and deg_out[a - 1] > deg_out[b - 1]) {
        return true;
    } else {
        return false;
    }
}

void dfs(const std::pair<int, int> tree[], const std::pair<int, int> rels[],
         const int n, const int q) {
    std::pair<int, int> starts[n];
    int deg_in[n]{}, deg_out[n]{}, counter = 1;
    int visited[n]{}, index = 0;

    set_starts(starts, tree, n);

    visited[0] = 1;
    deg_in[0] = counter;
    counter++;
    while (visited[0] != 0) {
        int vertex = visited[index];

        int fst = starts[vertex - 1].first, end = starts[vertex - 1].second;
        while (fst < end and fst < n - 1) {
            int neighbour = tree[fst].second;

            if (deg_in[neighbour - 1] == 0) {
                deg_in[neighbour - 1] = counter;
                counter++;
            }

            if (visited[index + 1] == 0) {
                starts[vertex - 1].first++;
                visited[index + 1] = neighbour;
                vertex = neighbour;
                index++;
                fst = starts[vertex - 1].first;
                end = starts[vertex - 1].second;
            }
        }
        deg_out[vertex - 1] = counter;
        visited[index] = 0;
        index--;
        counter++;
    }

    for (int i = 0; i < q; i++) {
        if (is_ancesor(rels, deg_in, deg_out, i)) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }
}

int main() {
    int q, n;
    scanf("%d %d", &n, &q);
    std::pair<int, int> tree[n - 1], rels[q];

    if (n < 2 or n > 1000000) {
        throw std::invalid_argument("n out of range");
    }
    for (int i = 1; i < n; i++) {
        scanf("%d", &tree[i - 1].first);
        tree[i - 1].second = i + 1;
    }
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &rels[i].first, &rels[i].second);
    }

    std::sort(tree, tree + n - 1);
    dfs(tree, rels, n, q);
    return 0;
}
