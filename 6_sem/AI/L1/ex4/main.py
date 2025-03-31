def opt_dist(block, n):
    if n == 0:
        return block.count("1")
    
    if n > len(block):
        return float('inf')
    
    block = [int(d) for d in block]
    
    min_flips = float('inf')
    for b in range(len(block) - n + 1):
        fragment = block[b:b+n]
        flips = sum([1 for d in fragment if d == 0])
        
        flips += sum(block[:b])
        flips += sum(block[b+n:])
            
        min_flips = min(min_flips, flips)
    return min_flips
        
file_in = [line.rstrip().split() for line in open("zad4_input.txt", "r").readlines()]
with open("zad4_output.txt", "w") as file_out:
    for block, n in file_in:
        file_out.write(str(opt_dist(block, int(n))) + "\n")