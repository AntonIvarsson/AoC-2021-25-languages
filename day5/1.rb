lines = File.readlines('input.txt')

def starting_grid(n)
    grid = []
    (0..n).each do |i|
        grid << []
        (0..n).each do |j|
            grid[i][j] = 0
        end
     end
    return grid
end

def mark_grid(points, grid, task1)
    p1 = points[0].split(",").map { |v| v.to_i }
    p2 = points[1].split(",").map { |v| v.to_i }
    x1 = p1[0]
    y1 = p1[1]
    x2 = p2[0]
    y2 = p2[1]

    row = x1 < x2 ? (x1..x2) : (x2..x1)
    col = y1 < y2 ? (y1..y2) : (y2..y1)

    if x1 != x2 and y1 != y2
        if task1
            return
        end
        x_now = x1 < x2 ? x1 : x2
        y_now = x_now == x1 ? y1 : y2
        y_end = y_now == y1 ? y2 : y1

        while x_now <= row.last()
            grid[x_now][y_now] += 1
            y_now = y_now > y_end ? y_now -= 1 : y_now += 1
            x_now +=1
        end
        return
    end

    row.each do |x|
        col.each do |y|
            grid[x][y] += 1
       end
    end
end

def check_grid(grid)
    count = grid.flatten().select {|num| num > 1 }.count()
    puts count
end

grid = starting_grid 1000
for item in lines
    points = item.split(" -> ", 0)
    mark_grid(points, grid, true)
end
check_grid(grid)

grid = starting_grid 1000
for item in lines
    points = item.split(" -> ", 0)
    mark_grid(points, grid, false)
end
check_grid(grid)