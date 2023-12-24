def return_row(nums, tmp_x, x2, y):
    row = []
    for i in range(nums):
        row.append(tmp_x*y)
    row.append(x2*y)
    return row

def print_num(lenght, num):
    res = lenght - (len(str(num)))
    if res >= 0:
        print(" " * res, num, end="")
    

def print_row(tmp_x, x2, y, d, lst):
    i = 0
    while tmp_x < x2:
        print_num(lst[i], tmp_x * y)
        tmp_x += d
        i += 1  
    print_num(lst[i], x2 * y)  
    print()  
    
def tabliczka(x1, x2, y1, y2, d):
    tmp_x = x1
    
    list_of_max_width = []
    nums = 0
    
    while tmp_x < x2:
        list_of_max_width.append(len(str(tmp_x*y2)))
        tmp_x += d
        nums += 1
    list_of_max_width.append(len(str(x2*y2)))
    
    tab = []
    tmp_y = y1
    while tmp_y < y2:
        tab.append(return_row(nums, x1, x2, tmp_y))
        tmp_y += d
    tab.append(return_row(nums, x1, x2, y2))
    
    print(" " * len(str(y2)), end=" ")
    
    print_row(x1, x2, 1, d, list_of_max_width)
    
    while y1 < y2:
        print_num(list_of_max_width[0], y1)
        print_row(x1, x2, y1, d, list_of_max_width)
        y1 += d
    
    print_num(list_of_max_width[0], y2)   
    print_row(x1,x2,y2,d, list_of_max_width)
    
    
    

    
tabliczka(3.0, 100.0, 2.0, 14.0, 10.0)
