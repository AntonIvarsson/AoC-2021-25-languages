#!/usr/bin/env groovy
def lines = new File("input.txt") as String[]

def starting_grid(n) {
    arr = [0] * n
    for (i in 0..(n-1)) {
        arr[i] = [0] * n
    }
    return arr
}

def mark_grid(points, grid, task1) {
    p1 = points[0].split(",")
    p2 = points[1].split(",")
    x1 = p1[0].toInteger()
    y1 = p1[1].toInteger()
    x2 = p2[0].toInteger()
    y2 = p2[1].toInteger()

    row = x1 < x2 ? (x1..x2) : (x2..x1)
    col = y1 < y2 ? (y1..y2) : (y2..y1)

    if (x1 != x2 && y1 != y2) {
        if (task1) {
            return
        }
        x_now = x1 < x2 ? x1 : x2
        y_now = x_now == x1 ? y1 : y2
        y_end = y_now == y1 ? y2 : y1
        while (x_now <= row.last()) {
            grid[x_now][y_now] += 1
            y_now = y_now > y_end ? y_now - 1 : y_now + 1
            x_now++
        }
        return
    }
    for (x in row) {
        for (y in col) {
            grid[x][y] += 1
        }
    }
}

def check_grid(grid) {
    count = 0
    flattened = grid.flatten()
    for (number in flattened) {
        if (number > 1) {
            count += 1
        } 
    }
    return count
}

grid = starting_grid(1000)
for (line in lines) {
    points = line.split(" -> ")
    mark_grid(points, grid, true)
}
println check_grid(grid)
grid = starting_grid(1000)
for (line in lines) {
    points = line.split(" -> ")
    mark_grid(points, grid, false)
}
println check_grid(grid)
