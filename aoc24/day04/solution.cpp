#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

uint64_t explore_X_star_pattern(const std::vector<std::string>& input_matrix,
                                size_t mat_width, size_t mat_height,
                                size_t start_x, size_t start_y) {
    size_t x = start_x;
    size_t y = start_y;
    uint64_t count = 0;

    if (input_matrix[y][x] != 'X')
        return 0;  // we only start on X, that way we'll only count every
                   // XMAS once

    // up
    if (y >= 3) {  // there can be no XMAS above if we're higher
        char M = input_matrix[y - 1][x];
        char A = input_matrix[y - 2][x];
        char S = input_matrix[y - 3][x];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }
    // right
    if (x <= mat_width - 4) {  // there can be no XMAS to the right if
                               // we're further right
        char M = input_matrix[y][x + 1];
        char A = input_matrix[y][x + 2];
        char S = input_matrix[y][x + 3];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }
    // down
    if (y <= mat_height - 4) {  // there can be no XMAS below if we're
                                // lower than 4 from the bottom
        char M = input_matrix[y + 1][x];
        char A = input_matrix[y + 2][x];
        char S = input_matrix[y + 3][x];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }
    // left
    if (x >= 3) {  // there can be no XMAS to the left if we're further
                   // left than 4 from the left
        char M = input_matrix[y][x - 1];
        char A = input_matrix[y][x - 2];
        char S = input_matrix[y][x - 3];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }
    // up-right
    if (y >= 3 && x <= mat_width - 4) {  // up rule + right rule
        char M = input_matrix[y - 1][x + 1];
        char A = input_matrix[y - 2][x + 2];
        char S = input_matrix[y - 3][x + 3];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }
    // down-right
    if (y <= mat_height - 4 && x <= mat_width - 4) {  // down rule + right
                                                      // rule
        char M = input_matrix[y + 1][x + 1];
        char A = input_matrix[y + 2][x + 2];
        char S = input_matrix[y + 3][x + 3];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }
    // down-left
    if (y <= mat_height - 4 && x >= 3) {  // down rule + left rule
        char M = input_matrix[y + 1][x - 1];
        char A = input_matrix[y + 2][x - 2];
        char S = input_matrix[y + 3][x - 3];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }
    // up-left
    if (y >= 3 && x >= 3) {  // up rule + left rule
        char M = input_matrix[y - 1][x - 1];
        char A = input_matrix[y - 2][x - 2];
        char S = input_matrix[y - 3][x - 3];

        if (M == 'M' && A == 'A' && S == 'S') {
            count++;
        }
    }

    return count;
}

void solve1() {
    std::ifstream file("day04/input1.txt");

    std::vector<std::string> input_matrix;
    input_matrix.reserve(141);
    size_t mat_width = 0;
    size_t mat_height = 0;

    std::string line;
    while (std::getline(file, line)) {
        input_matrix.push_back(line);
    }
    mat_width = input_matrix[0].size();
    mat_height = input_matrix.size();

    std::cout << "Matrix width: " << mat_width << std::endl;
    std::cout << "Matrix height: " << mat_height << std::endl;
    std::cout << std::endl;

    uint64_t count = 0;
    for (size_t i = 0; i < mat_height; i++) {
        for (size_t j = 0; j < mat_width; j++) {
            // std::cout << input_matrix[i][j];
            count += explore_X_star_pattern(input_matrix, mat_width,
                                            mat_height, j, i);
        }
        // std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Count: " << count << std::endl;
}

uint64_t explore_A_star_pattern(const std::vector<std::string>& input_matrix,
                                size_t mat_width, size_t mat_height,
                                size_t start_x, size_t start_y) {
    size_t x = start_x;
    size_t y = start_y;

    if (input_matrix[y][x] != 'A')
        return 0;  // we only start on A, that way we'll only count every
                   // MAS cross once
    // M.S
    // .A.
    // M.S

    if (y < 1 || y >= mat_height - 1 || x < 1 || x >= mat_width - 1)
        return 0;  // we can't have a MAS cross on the edge

    char upper_left = input_matrix[y - 1][x - 1];
    char upper_right = input_matrix[y - 1][x + 1];
    char lower_left = input_matrix[y + 1][x - 1];
    char lower_right = input_matrix[y + 1][x + 1];

    bool ul_to_lr_mas = upper_left == 'M' && lower_right == 'S';
    bool ur_to_ll_mas = upper_right == 'M' && lower_left == 'S';
    bool ll_to_ur_mas = lower_left == 'M' && upper_right == 'S';
    bool lr_to_ul_mas = lower_right == 'M' && upper_left == 'S';
    if ((ul_to_lr_mas || lr_to_ul_mas) && (ur_to_ll_mas || ll_to_ur_mas)) {
        return 1;
    }

    return 0;
}

void solve2() {
    std::ifstream file("day04/input2.txt");

    std::vector<std::string> input_matrix;
    input_matrix.reserve(141);
    size_t mat_width = 0;
    size_t mat_height = 0;

    std::string line;
    while (std::getline(file, line)) {
        input_matrix.push_back(line);
    }
    mat_width = input_matrix[0].size();
    mat_height = input_matrix.size();

    std::cout << "Matrix width: " << mat_width << std::endl;
    std::cout << "Matrix height: " << mat_height << std::endl;
    std::cout << std::endl;

    uint64_t count = 0;
    for (size_t i = 0; i < mat_height; i++) {
        for (size_t j = 0; j < mat_width; j++) {
            // std::cout << input_matrix[i][j];
            count += explore_A_star_pattern(input_matrix, mat_width,
                                            mat_height, j, i);
        }
        // std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Count: " << count << std::endl;
}
