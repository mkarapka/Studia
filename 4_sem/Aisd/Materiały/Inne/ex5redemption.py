def lcs_min_space(X, Y):
    m = len(Y)
    n = len(X)

    dp = [0 for _ in range(n + 1)]
    res = ""

    for i in range(1, m + 1):
        prev = dp[0]
        for j in range(1, n + 1):
            tmp = dp[j]

            if Y[i - 1] == X[j - 1]:
                dp[j] = prev + 1

            else:
                dp[j] = max(dp[j - 1], dp[j])

            prev = tmp


X = "ralaa"
Y = "krola"

# print(lcs_min_space(X, Y))
print(lcs_min_space(Y, X))
