#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <optional>
#include <vector>

struct MmappedFile {
    const char* data;
    size_t size;
};

inline std::optional<MmappedFile> mmap_file(const char* filename) {
    auto fd = open(filename, O_RDONLY);
    struct stat st;
    if (fstat(fd, &st) == -1) {
        std::cerr << "Failed to stat file" << std::endl;
        return std::nullopt;
    }
    size_t fsize = st.st_size;

    const char* file_data =
        (const char*)mmap(nullptr, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_data == MAP_FAILED) {
        std::cerr << "Failed to map file" << std::endl;
        return std::nullopt;
    }
    close(fd);

    return std::optional<MmappedFile>{MmappedFile{file_data, fsize}};
}

template <typename T>
inline void print_vector(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
