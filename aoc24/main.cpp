#include <chrono>
#include <iostream>

extern void solve1();
extern void solve2();

void call_with_timer(void (*func)(), const char *name) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration_millis = duration_cast<nanoseconds>(end - start) / 1000000.0;
    std::cout << "Done with " << name << std::endl;
    std::cout << name << " execution time: " << duration_millis.count() << " ms"
              << std::endl;
}

int main() {
    std::cout << "Solution 1:" << std::endl;
    std::cout << "===========" << std::endl;
    call_with_timer(solve1, "solve1()");

    std::cout << "Solution 2:" << std::endl;
    std::cout << "===========" << std::endl;
    call_with_timer(solve2, "solve2()");

    return 0;
}
