lines = File.readlines('input.txt')

depth = 0
horizontal = 0

for item in lines
    arr = item.split(" ", 0)
    command = arr[0]
    amount = arr[1].to_i()

    if (command === 'forward')
        horizontal += amount
    elsif (command === 'down')
        depth += amount
    elsif (command === 'up')
        depth -= amount
    end
end

puts depth*horizontal

aim = 0
horizontal = 0
depth = 0

for item in lines
    arr = item.split(" ", 0)
    command = arr[0]
    amount = arr[1].to_i()
    if (command == 'down')
        aim += amount
    elsif (command == 'up')
        aim -= amount
    else (command === 'forward')
        horizontal += amount
        depth += (amount * aim)
    end
end

puts depth*horizontal