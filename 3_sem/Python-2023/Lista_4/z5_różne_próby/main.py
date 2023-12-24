def shadow_pix(vec1, vec2):
    img = [[0 for i in range(len(vec1))] for j in range(len(vec1))]
    global row_vec 
    row_vec = [0,0,0,0]

def fill_img(img, vec, ind):
    blocks = vec[ind]
    if vec[ind] != 0:
        for row in range(0,len(vec)-vec[ind]+1):
            img = fill_rows(img, row, row+vec[row], ind)
            
def fill_rows(img, p, k, ind):
    for i in range(p,k):
        img[i][ind] = 1
    return img

def clear_rows(img, p, k, ind):
    for i in range(p,k):
        img[i][ind] = 0
    return img  
  
def check_boad(img, vec):
    for row in range(len(vec)):
        flag = False
        if vec[pix] == 0:
            if sum[img[row]] == 0:
                flag = True
        else:
            for el in range(0,len(vec)-vec[row]+1):
                if sum(img[row][el:el+vec[row]]) == vec[row]:
                    flag = True
        if flag == False:
            return False
    return True
             
            
def check_seg(segment):
                
fill_img([[0,0,0,0]],3,0)
# lst = [[0,0,0,0]]
# lst[0:2] = [1 for i in range(2)]
# print(lst)

