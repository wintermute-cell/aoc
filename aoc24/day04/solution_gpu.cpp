// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format one

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>

GLuint createComputeShader(const char* source) {
    GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());
        std::cerr << "ERROR: Compute Shader Compilation Failed\n" << log.data() << std::endl;
        exit(-1);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, log.data());
        std::cerr << "ERROR: Shader Program Linking Failed\n" << log.data() << std::endl;
        exit(-1);
    }

    glDeleteShader(shader);
    return program;
}

void solve1() {}

void solve2() {

    // Opengl
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1, 1, "Compute Shader Context", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        std::cerr << "GL CALLBACK: " << message << std::endl;
    }, nullptr);
    const char* compute_shader_source = R"(
#version 430
layout (local_size_x = 3, local_size_y = 3) in;

layout (binding = 0) readonly buffer InputBuffer {
    int inputData[];
};
layout (binding = 1) writeonly buffer OutputBuffer {
    uint outputData[];
};

uniform uint matWidth;
uniform uint matHeight;

void main() {
    // uint index = gl_GlobalInvocationID.y * matWidth + gl_GlobalInvocationID.x;
    // outputData[index] = inputData[index]; // Echo input data
    uint x = gl_GlobalInvocationID.x;
    uint y = gl_GlobalInvocationID.y;

    x = x - 4;

    uint index = y * matWidth + x;
    bool inBounds = (x >= 1) && (x < matWidth - 1) && (y >= 1) && (y < matHeight - 1);

    bool isA = inputData[index] == 65;

    int upperLeft = inputData[(y - 1) * matWidth + (x - 1)];
    int upperRight = inputData[(y - 1) * matWidth + (x + 1)];
    int lowerLeft = inputData[(y + 1) * matWidth + (x - 1)];
    int lowerRight = inputData[(y + 1) * matWidth + (x + 1)];

    bool ulToLrMas = (upperLeft == 77) && (lowerRight == 83);
    bool urToLlMas = (upperRight == 77) && (lowerLeft == 83);
    bool llToUrMas = (lowerLeft == 77) && (upperRight == 83);
    bool lrToUlMas = (lowerRight == 77) && (upperLeft == 83);

    bool hasMasPattern = (ulToLrMas || lrToUlMas) && (urToLlMas || llToUrMas);
    outputData[index] = (inBounds && isA && hasMasPattern) ? 1u : 0u;
}
    )";
    GLuint compute_shader_program = createComputeShader(compute_shader_source);

    // Actual solution
    std::ifstream file("day04/input2.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input file" << std::endl;
        return;
    }

    std::vector<std::string> input_matrix;
    std::vector<char> flattenedMatrix;

    uint32_t mat_width = 0, mat_height = 0;

    std::string line;
    while (std::getline(file, line)) {
        if (input_matrix.empty()) {
            mat_width = line.size();
        }
        input_matrix.push_back(line);
        flattenedMatrix.insert(flattenedMatrix.end(), line.begin(), line.end());
    }
    std::vector<int> intMatrix(flattenedMatrix.begin(), flattenedMatrix.end());

    mat_height = input_matrix.size();

    if (mat_width == 0 || mat_height == 0) {
        std::cerr << "Input matrix is empty or malformed" << std::endl;
        return;
    }

    GLuint inputBuffer, outputBuffer;
    glGenBuffers(1, &inputBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, inputBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, intMatrix.size()*sizeof(int), intMatrix.data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, inputBuffer);

    std::vector<uint32_t> outputData(intMatrix.size(), 0);
    glGenBuffers(1, &outputBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, outputBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, outputData.size() * sizeof(uint32_t), nullptr, GL_DYNAMIC_READ);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, outputBuffer);

    glUseProgram(compute_shader_program);

    GLuint matWidthLoc = glGetUniformLocation(compute_shader_program, "matWidth");
    glUniform1ui(matWidthLoc, mat_width);
    GLuint matHeightLoc = glGetUniformLocation(compute_shader_program, "matHeight");
    glUniform1ui(matHeightLoc, mat_height);

    GLuint groupSizeX = (mat_width + 15) / 16;
    GLuint groupSizeY = (mat_height + 15) / 16;

    auto smallest_time = std::chrono::nanoseconds::max();

    for (size_t it = 0; it < 100000; it++) {

    auto start = std::chrono::high_resolution_clock::now();

    glDispatchCompute(groupSizeX, groupSizeY, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glFinish();
    auto end = std::chrono::high_resolution_clock::now();
        smallest_time = std::min(smallest_time, end - start);

    // calc result
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, outputBuffer);
    void* ptr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
    std::memcpy(outputData.data(), ptr, outputData.size() * sizeof(uint32_t));
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

    }
    // std::cout << "Exec time: " << duration_millis.count() << " ms" << std::endl;
    std::cout << "Exec time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(smallest_time).count() << " ns" << std::endl;

    uint64_t count = std::accumulate(outputData.begin(), outputData.end(), 0ULL);
    std::cout << "Count: " << count << std::endl;
}

