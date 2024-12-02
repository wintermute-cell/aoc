#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void solve1() {
    std::ifstream file("day02/input1.txt");

    std::vector<std::vector<int16_t>> lvls;

    lvls.reserve(1001);
    for (size_t i = 0; i < 1001; i++) {
        lvls.push_back(std::vector<int16_t>());
        lvls[i].reserve(20);
    }

    if (file.is_open()) {
        std::string line;
        size_t i = 0;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
            size_t j = 0;
            std::string word;
            std::stringstream ss(line);
            while (std::getline(ss, word, ' ')) {
                std::cout << "word: " << word << std::endl;
                lvls[i].push_back(std::stoi(word));
            }
            i++;
        }
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }

    auto numlines = lvls.size();

    file.close();

    uint64_t unsafe_count = 0;

    // for each report
    for (auto& v : lvls) {
        int16_t word1, word2;
        bool ascending = true;
        // for each level pair
        for (size_t i = 0; i < v.size() - 1; i++) {
            word1 = v[i];
            word2 = v[i + 1];
            bool this_ascending = word1 < word2;
            if (i > 0 && this_ascending != ascending) {
                unsafe_count++;
                break;
            } else {
                ascending = this_ascending;
            }

            int64_t diff = std::abs(word2 - word1);
            if (diff < 1 || diff > 3) {
                unsafe_count++;
                break;
            }
        }
    };

    uint64_t safe_count = numlines - unsafe_count;
    std::cout << safe_count << std::endl;
}

void solve2() {
}
