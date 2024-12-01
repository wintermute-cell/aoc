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

    lnums.reserve(1001);
    rnums.reserve(1001);

    if (file.is_open()) {
        std::string line;
        uint32_t lnum, rnum;
        while (std::getline(file, line)) {
            std::sscanf(line.c_str(), "%d %d", &lnum, &rnum);

            lnums.push_back(lnum);
            rnums.push_back(rnum);
        }
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }

    file.close();

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
        uint32_t lnum, rnum;
        while (std::getline(file, line)) {
            std::sscanf(line.c_str(), "%d %d", &lnum, &rnum);

            lnums.push_back(lnum);

            // track the number of occurences
            if (rnums.contains(rnum))
                rnums[rnum]++;
            else
                rnums[rnum] = 1;
        }
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }

    file.close();

    uint64_t similarity_score = 0;
    for (size_t i = 0; i < lnums.size(); i++) {
        similarity_score += rnums[lnums[i]] * lnums[i];
    }

    std::cout << similarity_score << std::endl;
}
