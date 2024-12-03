
#include <iostream>
void solve1() {
    std::cout << "Solution 1 is not implemented in cpp but bash, see solution.cpp for command" << std::endl;
    // Using a programming language is overkill, this is a simple solution:
    // cat input1.txt | grep -o -P "mul\(\d{1,3},\d{1,3}\)" | sed 's/,/*/g' | sed 's/mul(/+/' | sed 's/)//' | tr -d '\n' | cut -c 2- | bc
    // or
    // cat input1.txt | grep -o -P "mul\(\d{1,3},\d{1,3}\)" | perl -pe "s/mul\((\d+),(\d+)\)\n/\1*\2+/g" | sed "s/+\$//" | bc
}

void solve2() {
    std::cout << "Solution 2 is not implemented in cpp but bash, see solution.cpp for command" << std::endl;
    // I confess, solution 2 is a bit f'd...
    // time cat input2.txt | tr -d '\n' | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?\$//" | grep -o -P "mul\(\d{1,3},\d{1,3}\)" | perl -pe "s/mul\((\d+),(\d+)\)\n/\1*\2+/g" | sed "s/+\$//" | bc
}
