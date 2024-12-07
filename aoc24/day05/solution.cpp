
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "mylib.h"

void solve1() {
    std::optional<MmappedFile> maybe_file = mmap_file("day05/input1.txt");
    if (!maybe_file.has_value()) {
        std::cerr << "Failed to mmap file" << std::endl;
        return;
    }
    MmappedFile file = maybe_file.value();

    // Construct a directed graph from the order pairs in the input.
    std::vector<std::unordered_set<uint_fast8_t>> graph_adjlist;
    graph_adjlist.resize(100);
    std::vector<std::unordered_set<uint_fast8_t>> graph_inv_adjlist;
    graph_inv_adjlist.resize(100);

    uint_fast8_t lnum, rnum;
    for (size_t i = 0; i < file.size; i += 6) {
        if (file.data[i] == '\n') {
            // set to next section, skip newline and null terminator
            file.data += i + 1;
            file.size -= i + 2;
            break;
        }
        lnum = (file.data[i] - '0') * 10 + (file.data[i + 1] - '0');
        rnum = (file.data[i + 3] - '0') * 10 + (file.data[i + 4] - '0');

        graph_adjlist[lnum].insert(rnum);
        graph_inv_adjlist[rnum].insert(lnum);
    }

    // We check if there is a hamiltonian path for the update subgraph.
    std::istringstream update_section(file.data);
    std::string line;
    std::string num_str;
    std::vector<uint_fast8_t> update;
    uint64_t sum = 0;
    while (std::getline(update_section, line)) {
        std::istringstream line_ss(line);
        update.clear();
        while (std::getline(line_ss, num_str, ',')) {
            uint_fast8_t num = std::stoi(num_str);
            update.push_back(num);
        }
        for (size_t i = 0; i < update.size() - 1; ++i) {
            uint_fast8_t a = update[i];
            uint_fast8_t b = update[i + 1];
            if (!graph_adjlist[a].contains(b)) {
                goto unsorted;
            }
        }
        sum += update[update.size() / 2];
    unsorted:;
    }

    std::cout << sum << std::endl;
}

void solve2() {
    std::optional<MmappedFile> maybe_file = mmap_file("day05/input2.txt");
    if (!maybe_file.has_value()) {
        std::cerr << "Failed to mmap file" << std::endl;
        return;
    }
    MmappedFile file = maybe_file.value();

    // Construct a directed graph from the order pairs in the input.
    std::vector<std::unordered_set<uint_fast8_t>> graph_adjlist;
    graph_adjlist.resize(100);
    std::vector<std::unordered_set<uint_fast8_t>> graph_inv_adjlist;
    graph_inv_adjlist.resize(100);

    uint_fast8_t lnum, rnum;
    for (size_t i = 0; i < file.size; i += 6) {
        if (file.data[i] == '\n') {
            // set to next section, skip newline and null terminator
            file.data += i + 1;
            file.size -= i + 2;
            break;
        }
        lnum = (file.data[i] - '0') * 10 + (file.data[i + 1] - '0');
        rnum = (file.data[i + 3] - '0') * 10 + (file.data[i + 4] - '0');

        graph_adjlist[lnum].insert(rnum);
        graph_inv_adjlist[rnum].insert(lnum);
    }

    // We check if there is a hamiltonian path for the update subgraph.
    std::istringstream update_section(file.data);
    std::string line;
    std::string num_str;
    std::vector<uint_fast8_t> update;
    uint64_t sum = 0;
    while (std::getline(update_section, line)) {
        std::istringstream line_ss(line);
        update.clear();
        while (std::getline(line_ss, num_str, ',')) {
            uint_fast8_t num = std::stoi(num_str);
            update.push_back(num);
        }
        for (size_t i = 0; i < update.size() - 1; ++i) {
            uint_fast8_t a = update[i];
            uint_fast8_t b = update[i + 1];
            if (!graph_adjlist[a].contains(b)) {
                goto unsorted;
            }
        }
        continue;
    unsorted:;
        // Sort the update based on the fact that only the direct neighbors'
        // < relation has to be well defined.
        auto comparator = [&graph_adjlist](uint_fast8_t a, uint_fast8_t b) {
            return graph_adjlist[a].contains(b);
        };
        std::sort(update.begin(), update.end(), comparator);
        sum += update[update.size() / 2];
    }

    std::cout << sum << std::endl;
}
