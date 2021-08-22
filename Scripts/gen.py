from random import randint, shuffle, choice

smallLetters = "abcdefghijklmnopqrstuvwxyz"

# Returns a random integer in range [a,b]
def getInt(a, b):
    assert b >= a, "Range must be valid"
    a = int(a)
    b = int(b)

    return randint(a, b)

# Returns a random pair of integers <x,y>
# such that x and y lies in the range [a,b].
# way decides the ordering of the pairs:
# (way = 1) => random
# (way = 2) => strictly increasing
# (way = 3) => weakly increasing
# (way = 4) => strictly decreasing
# (way = 5) => weakly decreasing
def getPair(a, b, way = 1):
    a = int(a)
    b = int(b)
    way = int(way)

    x = getInt(a,b)

    if way == 1:
        y = getInt(a, b)

    elif way == 2:
        assert b > a, "Must have at least 2 possible values for strictly increasing"
        while(x == b):
            x = getInt(a,b)
        y = getInt(max(x+1,a), b)

    elif way == 3:
        y = getInt(max(x,a), b)

    elif way == 4:
        assert b > a, "Must have at least 2 possible values for strictly decreasing"
        while(x == a):
            x = getInt(a,b)
        y = getInt(a, min(x-1, b))

    elif way == 5:
        y = getInt(a, min(x, b))

    else:
        raise RuntimeError("Invalid way passed")

    return (x,y)

# Returns an array of size n of random integers in [a,b] range
def getArray(n, a, b):
    n = int(n)
    a = int(a)
    b = int(b)

    arr = []

    for _ in range(n):
        arr.append(getInt(a,b))

    return arr

# Returns an array of size n of random integers in [a,b] range
# where each element occurs exactly 1 time in the array
def getUniqueArray(n,a,b):
    n = int(n)
    a = int(a)
    b = int(b)

    assert b - a + 1 >= n, "Possible number of elements should be at least n"

    arr = []
    seen = set([])

    while(len(arr) < n):
        ele = getInt(a,b)
        if ele in seen:
            continue
        else:
            arr.append(ele)
            seen.add(ele)

    return arr

# Returns a random permutation of the integers from [1,n]
def getPermutation(n):
    n = int(n)

    arr = []

    for i in range(1, n+1):
        arr.append(i)
    shuffle(arr)

    return arr

# Prints an array
def printArray(arr):
    print(" ".join([str(x) for x in arr]))

# Returns a matrix of size n X m where each element lies
# in the range [a,b]
def getMatrix(n, m, a, b):
    n = int(n)
    m = int(n)
    a = int(a)
    b = int(b)

    mat = []

    for _ in range(n):
        mat.append(getArray(m, a, b))
    return mat

# Prints a matrix
def printMatrix(mat):
    for i in range(len(mat)):
        printArray(mat[i])

# Gets a random string of size n
# consisting of only characters from ALLOWED
def getString(n, ALLOWED = smallLetters):
    assert len(ALLOWED) > 0, "There must be at least one possible character"

    ans = []

    while(len(ans) < n):
        ans.append(choice(ALLOWED))

    return "".join(ans)

# Gets a random character matrix of size n x m
# where each character comes from ALLOWED
def getCharMatrix(n, m, ALLOWED = smallLetters):
    ans = []

    for _ in range(n):
        temp = []
        for _ in range(m):
            temp.append(choice(ALLOWED))
        ans.append(temp)

    return ans

# Prints a character matrix
def printCharMatrix(mat):
    for i in range(len(mat)):
        print("".join(mat[i]))

# Main test generation happens here
def main():

    return 0

if __name__ == '__main__':
    main()