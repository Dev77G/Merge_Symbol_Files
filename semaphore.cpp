#include "combine.hpp"

std::mutex mtx;
std::condition_variable cv;
int sema_count = 1;

void Wait() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return sema_count > 0; });
    --sema_count;
}
void Notify() {
    std::lock_guard<std::mutex> lock(mtx);
    ++sema_count;
    cv.notify_one();
}