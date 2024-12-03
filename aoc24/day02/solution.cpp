#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int16_t get_num_from_string(std::stringstream& ss) {
    std::string str;
    ss >> str;
    if (str.empty()) {
        return 0;
    }
    return std::stoi(str);
}

void solve1() {
    std::ifstream file("day02/input1.txt");

    int64_t num_lines = 0;

    uint64_t unsafe_count = 0;
    if (file.is_open()) {
        std::string line;
        // for each line
        while (std::getline(file, line)) {
            std::stringstream ss(line);

            int16_t last_word = get_num_from_string(ss);
            int16_t word = get_num_from_string(ss);

            while (word) {
                // for each level pair
                bool ascending = word < last_word;
                if (ascending) {
                    if (word > last_word || last_word - word > 3) {
                        unsafe_count++;
                        break;
                    }
                } else {
                    if (word < last_word || word - last_word > 3) {
                        unsafe_count++;
                        break;
                    }
                }
                last_word = word;
                word = get_num_from_string(ss);
            }
            num_lines++;
        }
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }

    file.close();

    uint64_t safe_count = num_lines - unsafe_count;
    std::cout << safe_count << std::endl;
}

void solve2() {
    std::ifstream file("day02/input2.txt");

    std::vector<std::vector<int16_t>> lvls;
    lvls.reserve(1001);

    uint64_t unsafe_count = 0;
    if (file.is_open()) {
        std::string line;
        size_t i = 0;

        // for each line
        while (std::getline(file, line)) {
            lvls.push_back(std::vector<int16_t>());
            lvls[i].reserve(20);
            std::string word;
            std::stringstream ss(line);
            while (std::getline(ss, word, ' ')) {
                lvls[i].push_back(std::stoi(word));
            }

            // generate variations where we remove one word in each variation sequentially
            auto variations = std::vector<std::vector<int16_t>>();
            variations.reserve(lvls[i].size());
            for (size_t j = 0; j < lvls[i].size(); j++) {
                variations.push_back(std::vector<int16_t>());
                variations[j].reserve(lvls[i].size() - 1);
                for (size_t k = 0; k < lvls[i].size(); k++) {
                    if (k != j) {
                        variations[j].push_back(lvls[i][k]);
                    }
                }
            }

            size_t num_variations = variations.size();
            size_t unsafe_variations = 0;
            for (auto v : variations) {
                // for each level pair
                int16_t word1, word2;
                bool ascending = true;
                for (size_t i = 0; i < v.size() - 1; i++) {
                    word1 = v[i];
                    word2 = v[i + 1];
                    bool this_ascending = word1 < word2;
                    if (i > 0 && this_ascending != ascending) {
                        unsafe_variations++;
                        break;
                    } else {
                        ascending = this_ascending;
                    }

                    int64_t diff = std::abs(word2 - word1);
                    if (diff < 1 || diff > 3) {
                        unsafe_variations++;
                        break;
                    }
                }
            }
            if (unsafe_variations == num_variations) {
                unsafe_count++;
            }

            i++;
        }
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }

    file.close();

    uint64_t safe_count = lvls.size() - unsafe_count;
    // std::cout << safe_count << std::endl;
}
