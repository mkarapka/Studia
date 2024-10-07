#include <bits/stdc++.h>
#include <iostream>
#include <limits>

struct item {
    int price;
    int wt;
};

bool unbound_knapsack(int dp[], int W, item items[], int n, bool deafult = true) {
    if (deafult == true)
        std::memset(dp, 0, W + 1);
    else
        std::memset(dp, std::numeric_limits<int>::max(), W + 1);

    bool achievable = false;
    for (int i = 0; i <= W; i++) {
        for (int j = 0; j < n; j++) {
            if (items[j].wt <= i) {
                if (deafult == true)
                    std::max(dp[i], dp[i - items[j].wt] + items[j].price);
                else
                    std::min(dp[i], dp[i - items[j].wt] + items[j].price);
            }
        }
        if (i == W and dp[i] != 0)
            achievable = true;
    }
    int last = dp[W], i = W;
    do {
        if (dp[i] != last) {
            printf("%d ", i);
            last = dp[i];
        }
        i--;
    } while (i > 0);
    printf("\n");
    return achievable;
}

int main() {
    int F, C;

    scanf("%d", &F);
    scanf("%d", &C);

    item items[C];
    int dp_min[F + 1], dp_max[F + 1];

    // clang-format off
    for (int i = 0; i < C; i++) {
        scanf("%d" "%d", &items[i].price, &items[i].wt); 
    }

    bool achivable = unbound_knapsack(dp_max, F, items, C);

    if (!achivable)
        printf("NIE\n");
    else{
        achivable = unbound_knapsack(dp_min, F, items, C, false);
        if(!achivable)
            printf("NIE\n");
        else{
            printf("TAK\n");
        }        
    }
    return 0;
}