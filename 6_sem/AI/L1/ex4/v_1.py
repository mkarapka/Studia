def is_solved(block, num):
    sum_of_ones = sum([int(d) for d in block])
    
    flag = 0
    for d in block:
        if d == "1" and flag == 0:
            flag+=1
        if d == "0" and flag == 1:
            flag += 1
        if d == "1" and flag == 2:
            flag += 1
        
    if num == 0 and sum_of_ones == 0:
        return True
       
    if flag != 3 and sum_of_ones == num:
        return True
    return False


dp = {}

def opt_dist(block, num):
    lst_block = [d for d in block]
    def solve_block(block, num, step, i):
        global dp
        print(block)
        x = dp.get("".join(block))
        if x:
            return x
        
        if is_solved(block, num):
            print(block, step)
            return step
        
        if step >= len(block) or i == len(block):
            return float('inf')

        cp_block = block[:]
        zero, one = float('inf'), float('inf')
        saved_d = cp_block[i]
        # print(cp_block)
        if cp_block[i] == "0":
            zero = solve_block(cp_block, num, step, i + 1)
            cp_block[i] = "1"
            one = solve_block(cp_block, num, step + 1, i + 1)
            if zero < one:
                cp_block[i] = saved_d
        else:
            one = solve_block(cp_block, num, step, i + 1)
            cp_block[i] = "0"
            zero = solve_block(cp_block, num, step + 1, i + 1)
            if zero > one:
                cp_block[i] = saved_d
        
        dp["".join(cp_block)] = min(zero, one)
        # print("dupsko")
        return min(zero, one)
    global dp
    dp = {}
    s = solve_block(lst_block, num, 0, 0)
    print(f"my= {s}",f"opt= {num}", block)
    return s

# block = "1111000000"
# block = "0010001000"
# # num = 4

# for num in range(0, 6):
#     print(f"min steps for {num}:" , min_ones(block, num))
    
# print(is_solved(block, num))

# file_in = [line.rstrip().split() for line in open("zad4_input.txt", "r").readlines()]
# with open("zad4_output.txt", "w") as file_out:
#     for block, n in file_in:
#         file_out.write(str(opt_dist(block, int(n))) + "\n")

block = "1000000000"
num = 1
print(f"min steps for {num}:" , opt_dist(block, num))