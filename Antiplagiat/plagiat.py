import math
def levenstein(str_1, str_2):
    n, m = len(str_1), len(str_2)
    if n > m:
        str_1, str_2 = str_2, str_1
        n, m = m, n

    current_row = range(n + 1)
    for i in range(1, m + 1):
        previous_row, current_row = current_row, [i] + [0] * n
        for j in range(1, n + 1):
            add, delete, change = previous_row[j] + 1, current_row[j - 1] + 1, previous_row[j - 1]
            if str_1[j - 1] != str_2[i - 1]:
                change += 1
            current_row[j] = min(add, delete, change)

    return current_row[n]

def plagiat(str1, str2):
    znaki=(".",",","?","/","!","@","#","$","%","^",'&',"*","(",")","[","]","{","}",'"',"'",":",";","<",">","=","-","+","`","«","»","—")
    predlogi=(" с "," в "," у "," по ", " под "," к "," до "," из "," а ", " и ")
    predlogi1=(" с"," в"," у"," по", " под"," к"," до"," из"," а", " и")
    len_znaki=len(znaki)
    for i in range(len_znaki):
        str1 = str1.replace(znaki[i], "")
        str2 = str2.replace(znaki[i], "")
    for i in range(len(predlogi)):
        str1 = str1.replace(predlogi[i], predlogi1[i])
        str2 = str2.replace(predlogi[i], predlogi1[i])
    listStr1 = str1.split()
    listStr2 = str2.split()

    len_listStr1 = len(listStr1)
    len_listStr2 = len(listStr2)

    QuantityShingles = 5

    ModListStr1 = len_listStr1%QuantityShingles
    ModListStr2 = len_listStr2%QuantityShingles

    DivListStr1 = len_listStr1//QuantityShingles
    DivListStr2 = len_listStr2//QuantityShingles

    MatrixListStr1 = []
    MatrixListStr2 = []

    if (ModListStr1 != 0 ):
        rows1 = DivListStr1+1
    else:
        rows1 = DivListStr1

    if (ModListStr2 != 0 ):
        rows2 = DivListStr2+1
    else:
        rows2 = DivListStr2


    for i in range(rows1):
            MatrixListStr1.append([0] * QuantityShingles)
    for i in range(rows2):
            MatrixListStr2.append([0] * QuantityShingles)

    num = 0
    LastPass1 = 0
    LastPass2 = 0

    for i in range(rows1):
        for j in range(QuantityShingles):
            if(num==len_listStr1):
                MatrixListStr1[i][j] = ""
                LastPass1 += 1
            else:
                MatrixListStr1[i][j] = listStr1[num].lower()
                num+=1

    num = 0

    for i in range(rows2):
        for j in range(QuantityShingles):
            if(num==len_listStr2):
                MatrixListStr2[i][j] = " "
                LastPass2 += 1
            else:
                MatrixListStr2[i][j] = listStr2[num].lower()
                num+=1

    CheckLast = False
    ShinglePlagiat = 0

    for i in range(rows1):
        WordPlagiat = 0
        for j in range(rows2):
            WordPlagiat = 0
            for k in range(QuantityShingles):
                for d in range(QuantityShingles):
                    if(levenstein(MatrixListStr1[i][k],MatrixListStr2[j][d])/max(len(MatrixListStr1[i][k]),len(MatrixListStr2[j][d])) < 0.3):
                        WordPlagiat +=1                 
            if(WordPlagiat/QuantityShingles > 0.5):
                if(i == rows1-2):
                    CheckLast = True
                elif(i == rows1-1):
                    CheckLast = False
                print("shingle plagiat", i," - " ,MatrixListStr1[i]," - ", MatrixListStr2[j], " - ", WordPlagiat)
                ShinglePlagiat +=1    
                break


    WordPlagiat = 0
    if(CheckLast == True):
        for i in range(QuantityShingles - LastPass1):
            for j in range(QuantityShingles - LastPass2):
                if(levenstein(MatrixListStr1[rows1-1][i],MatrixListStr2[rows2-1][j])/max(len(MatrixListStr1[rows1-1][i]),len(MatrixListStr2[rows2-1][j])) < 0.3):
                        WordPlagiat +=1
    if(WordPlagiat/(QuantityShingles-LastPass1) >= 0.5):
        print("shingle plagiat", rows1-1," - " ,MatrixListStr1[rows1-1]," - ", MatrixListStr2[rows2-1], " - ", WordPlagiat)
        ShinglePlagiat +=1

    uniqueness = (1 - ShinglePlagiat/rows1)*100
    if(uniqueness < 60):
        print("Text plagiat",", uniqueness: ", uniqueness,"%")
    else:
        print("Text no plagiat",", uniqueness: ", uniqueness,"%")        
    
    return uniqueness 

with open('text1.txt', 'r', encoding='utf-8') as file:
    str1 = file.read()                                                      # Текст 1 - Который нужно проверить
file.close()

with open('text2.txt', 'r', encoding='utf-8') as file:
    str2 = file.read()                                                      # Текст 2 - Основной текст
file.close()

print(plagiat(str1,str2))
