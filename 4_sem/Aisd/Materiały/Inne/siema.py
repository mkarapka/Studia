def lcis(X, Y):
    dp = [0 for _ in range(len(X))]
    for i in range(len(Y)):
        current = 0
        for j in range(len(X)):
            if X[j] == Y[i]:
                dp[j] = max(current + 1, dp[j])
            if X[j] < Y[i]:
                current = max(current, dp[j])

    maxi = max(dp)
    tmp = maxi - 1
    res = [X[dp.index(maxi)]]
    prev_val = res[0]
    for i in range(dp.index(maxi), -1, -1):
        if dp[i] == tmp and X[i] < prev_val:
            res.append(X[i])
            prev_val = X[i]
            tmp -= 1
        i -= 1

    return maxi, res[::-1], dp


print(lcis([1, 2, 7, 10, 4, 5, 6, 9], [2, 7, 8, 4, 10, 3, 5, 6]))
print(lcis([1, 7, 2], [2, 1, 4, 3, 7, 8]))
print(lcis([2, 3, 1, 6, 5, 4, 6], [1, 3, 5, 6]))
print(lcis([1, 2, 0, 2, 1], [1, 0, 1]))
print(lcis([2, 5, 4, 10, 3, 6], [2, 5, 10, 6]))
