const fs = require('fs');

const input = fs.readFileSync('input.txt', 'utf-8').split(/\n/)
depth = 0
horizontal = 0
input.forEach(line =>  {
    [command, amount] = line.split(" ")
    amount = Number(amount)
    if (command === 'forward') horizontal += amount
    if (command === 'down') depth += amount
    if (command === 'up') depth -= amount
});

console.log(depth*horizontal)