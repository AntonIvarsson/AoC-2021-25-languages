const fs = require('fs');

const input = fs.readFileSync('input.txt', 'utf-8').split(/\n/)
aim = 0
horizontal = 0
depth = 0
input.forEach(line =>  {
    [command, X] = line.split(" ")
    X = Number(X)
    if (command === 'down') aim += X
    if (command === 'up') aim -= X

    if (command === 'forward') {
        horizontal += X
        depth += (X*aim)
    } 
});

console.log(depth*horizontal)