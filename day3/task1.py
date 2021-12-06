import numpy as np
import functools

file1 = open('input.txt', 'r')
Lines = file1.readlines()
array = np.array([[int(c) for c in line.strip()] for line in Lines])

def toDecimal(bitlist):
    return functools.reduce(lambda acc, bit: (acc << 1) | bit, bitlist, 0)

def first(lines):
    binTuples = [(np.argmax(np.bincount(column)), np.argmin(np.bincount(column))) for column in array.T]
    gamma = toDecimal(map(lambda bitTuple : bitTuple[0], binTuples))
    epsilon = toDecimal(map(lambda bitTuple : bitTuple[1], binTuples))
    print(gamma*epsilon)

def second(lines):
    def critera(column, max):
        ones = np.count_nonzero(column == 1)
        zeros = np.count_nonzero(column == 0)
        if zeros == ones: return 1 if max else 0
        return int(ones > zeros if max else zeros < ones)

    def filter_numbers(lines, depth, rating = 'oxygen'):
        toKeep = critera(lines.T[depth], rating == 'oxygen')
        newLines = list(filter(lambda x : x[depth] == toKeep, lines))
        if len(newLines) == 1:
            return toDecimal(newLines[0])
        return filter_numbers(np.array(newLines), depth+1, rating)

    oxygenRating = filter_numbers(array, 0)
    co2Rating = filter_numbers(array, 0, 'c02')
    print(oxygenRating * co2Rating)

first(Lines)
second(Lines)