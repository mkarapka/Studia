
    return (permutations([lst[elem]] + lst[i:i+k-1]) \
        for elem in range(len(lst)) \
            for i in range(elem+1, len(lst)-k+2))