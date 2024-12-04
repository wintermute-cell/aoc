
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
void solve1() {
    //  Using a programming language is overkill, this is a simple solution:
    //  cat input1.txt | grep -o -P "mul\(\d{1,3},\d{1,3}\)" | sed 's/,/*/g' | sed 's/mul(/+/' | sed 's/)//' | tr -d '\n' | cut -c 2- | bc
    //  or
    //  cat input1.txt | grep -o -P "mul\(\d{1,3},\d{1,3}\)" | perl -pe "s/mul\((\d+),(\d+)\)\n/\1*\2+/g" | sed "s/+\$//" | bc

    std::ifstream file("day03/input1.txt");

    std::string line;
    uint64_t result = 0;
    std::regex mul_regex("mul\\((\\d{1,3}),(\\d{1,3})\\)");

    while (std::getline(file, line)) {
        auto regex_iter = std::sregex_iterator(line.begin(), line.end(), mul_regex);
        int32_t lnum, rnum;
        for (; regex_iter != std::sregex_iterator(); ++regex_iter) {
            lnum = std::stoi((*regex_iter).str(1));
            rnum = std::stoi((*regex_iter).str(2));
            result += lnum * rnum;
        }
    }
    std::cout << result << std::endl;
}

bool num_in_range(int32_t num, int32_t min, int32_t max) {
    return num >= min && num <= max;
}

void solve2() {
    std::cout << "Solution 2 is not implemented in cpp but bash, see solution.cpp for command" << std::endl;
    //  I confess, solution 2 is a bit f'd...
    //  time cat input2.txt | tr -d '\n' | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?do\(\)//" | perl -pe "s/don't\(\).*?\$//" | grep -o -P "mul\(\d{1,3},\d{1,3}\)" | perl -pe "s/mul\((\d+),(\d+)\)\n/\1*\2+/g" | sed "s/+\$//" | bc
}
