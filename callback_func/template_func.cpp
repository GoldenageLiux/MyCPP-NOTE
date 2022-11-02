/**
 * @Author: liuxin
 * @Date:   2022-11-02 13:57:23
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-02 14:05:35
 */
#include <iostream>

template <typename Func>
void call_process(Func func) {
    func(42);
}

struct Process2 {
    Process2(int n) : m_n(n) { }
    void operator()(int element) {
        std::cout << "process2: " << element * m_n << "\n";
    }
    int m_n;
};

int main() {
    int n = 10;
    call_process([n](int element) {
        std::cout << "process1: " << element * n << "\n";
    });
    // OK: capturing lambda

    call_process(Process2(n));
    // OK: callable struct

    return 0;
}
