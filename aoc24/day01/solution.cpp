#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

void solve1() {
    std::ifstream file("day01/input1.txt");

    std::vector<int32_t> lnums;
    std::vector<int32_t> rnums;

    lnums.reserve(1100);
    rnums.reserve(1100);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> this_line_nums;
            std::istringstream iss(line);
            std::string lnum, rnum;
            iss >> lnum >> rnum;

            lnums.push_back(std::stoul(lnum));
            rnums.push_back(std::stoul(rnum));
        }
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }

    std::sort(lnums.begin(), lnums.end());
    std::sort(rnums.begin(), rnums.end());

    uint64_t sum = 0;
    for (size_t i = 0; i < lnums.size(); i++) {
        sum += std::abs(rnums[i] - lnums[i]);
    }

    std::cout << sum << std::endl;
}

void solve2() {
    std::ifstream file("day01/input2.txt");

    std::vector<int32_t> lnums;
    std::unordered_map<int32_t, uint32_t> rnums;

    lnums.reserve(1001);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> this_line_nums;
            std::istringstream iss(line);
            std::string lnumStr, rnumStr;
            iss >> lnumStr >> rnumStr;

            lnums.push_back(std::stoul(lnumStr));
            auto rnum = std::stoul(rnumStr);

            // track the number of occurences
            if (rnums.contains(rnum))
                rnums[rnum]++;
            else
                rnums[rnum] = 1;
        }
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }

    uint64_t similarity_score = 0;
    for (size_t i = 0; i < lnums.size(); i++) {
        similarity_score += rnums[lnums[i]] * lnums[i];
    }

    std::cout << similarity_score << std::endl;
}
