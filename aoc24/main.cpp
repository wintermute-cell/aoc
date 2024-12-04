#include <chrono>
#include <iostream>
#include <thread>

extern void solve1();
extern void solve2();

double call_with_timer(void (*func)()) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    auto duration_millis = duration_cast<nanoseconds>(end - start) / 1000000.0;
    // std::cout << "Done with " << name << std::endl;
    // std::cout << name << " execution time: " << duration_millis.count() << "
    // ms"
    //           << std::endl;
    return duration_millis.count();
}

void warmup_cpu(int seconds) {
    unsigned int n_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    auto work = [seconds]() {
        auto end = std::chrono::high_resolution_clock::now() +
                   std::chrono::seconds(seconds);
        while (std::chrono::high_resolution_clock::now() < end) {
            volatile int x = 0;
            for (int i = 0; i < 1000000; ++i) x += i;
        }
    };

    std::cout << "Warming up CPU for " << seconds << " seconds..."
              << std::endl;

    for (unsigned int i = 0; i < n_threads; ++i) {
        threads.emplace_back(work);
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    constexpr int N = 1;  // num of runs
    double fastest_time_solve1 = std::numeric_limits<double>::max();
    double fastest_time_solve2 = std::numeric_limits<double>::max();

    std::cout << "Running solve1() " << N << " times..." << std::endl;
    for (int i = 0; i < N; ++i) {
        double time = call_with_timer(solve1);
        fastest_time_solve1 = std::min(fastest_time_solve1, time);
    }
    std::cout << "Fastest time for solve1(): " << fastest_time_solve1 << " ms"
              << std::endl;

    std::cout << "\nRunning solve2() " << N << " times..." << std::endl;
    for (int i = 0; i < N; ++i) {
        double time = call_with_timer(solve2);
        fastest_time_solve2 = std::min(fastest_time_solve2, time);
    }
    std::cout << "Fastest time for solve2(): " << fastest_time_solve2 << " ms"
              << std::endl;

    // std::cout << "Solution 1:" << std::endl;
    // std::cout << "===========" << std::endl;
    // warmup_cpu(4);
    // call_with_timer(solve1, "solve1()");
    //
    // std::cout << "Solution 2:" << std::endl;
    // std::cout << "===========" << std::endl;
    // warmup_cpu(4);
    // call_with_timer(solve2, "solve2()");

    return 0;
}
