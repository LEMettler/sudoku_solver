import numpy as np
'''
Reads in a sudoku from a Text-File.
0 represents positions to fill
'''

#extract sudoku to an array
def readFile(s):
    print("Sudoku-File:")
    name = input()
    file = open(name, "r")
    i=0
    j=0
    for line in file:
        for ch in line:
            if ch != '\n':
                s[i][j] = int(ch)
                j+=1
        i+=1
        j=0
    file.close()

#check the i-row for "num" entries
def testRow(s, i, j, num):
    for x in range(0,9):
        if x!=j:
            if s[i][x] == num:
                return False
    return True

#check the j-column for "num" entries
def testColumn(s, i, j, num):
    for x in range(0,9):
        if x!=i:
            if s[x][j] == num:
                return False
    return True

#check 3x3 box for num entries
def testBox(s, i, j, num):
    x = int(i/3)*3    #s[x][y] is the top left entry in relevant box 
    y = int(j/3)*3
    for u in range(x,x+3):
        for v in range(y,y+3):
            if (u != i and v != j):
                if s[u][v] == num:
                    return False
    return True

def testNumber(s, i, j, num):
    return testRow(s, i, j, num) and testColumn(s, i, j, num) and testBox(s, i, j, num) and num != 0

#find the next position to fill (contains a 0)
#when all positions are filled return -1
def nextPosition(s):
    for i in range(0,9):
        for j in range(0,9):
            if s[i][j] == 0:
                return (i,j,0)
    return (-1,-1,0)

#a console representation with boxes  
def printField(s):
    print("___________________")
    for i in range(0,9):
        print("|" + str(s[i][0]) + " " + str(s[i][1]) + " " + str(s[i][2]) + "|" +
              str(s[i][3]) + " " + str(s[i][4]) + " " + str(s[i][5]) + "|" +
              str(s[i][6]) + " " + str(s[i][7]) + " " + str(s[i][8]) + "|")
        if i%3 ==2 and i!=8:
            print("|-----------------|")
    print("l-----------------l")    


#---------------main------------------------
s = np.zeros((9,9), dtype=int)
readFile(s)
printField(s)
print()

#use a list as a queue for visited positions for backtracking
#index: i and j in array s, last is the last viable solution (init value = 0)
queue = []
(i,j, last) = nextPosition(s)

queue.append((i,j,last))
#loop until all positions are filled with an accepted solution
while(i != -1):
    found = False
    n = 0
    #try 1-9 as solutions for the current position
    #continue from last when this position has been touched before
    for num in range(last+1,10):
        found = testNumber(s, i, j, num)
        if found:
            n = num            
            break
    s[i][j] = n

    if found:
        #a solution was found for s[i][j]
        #add it to the queue and find the next position
        queue.append((i,j,n))
        (i,j,last) = nextPosition(s)
    else:
        #no solution was found for s[i][j]
        #go back to the previous position
        #continue from last
        (i,j,last) = queue.pop()
        
print("Solution:")
printField(s)

    
        
    





















