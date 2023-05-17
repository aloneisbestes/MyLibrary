#include <iostream>
#include <unistd.h>
#include "threadpool.h"

using namespace std;

void test(int i) {
    cout << "thread pool: " << i << endl;
}

int main() {
    cout << "hello, c++" << endl;

    for (int i = 0; i < 10000; i++) {
        ThreadPool::instance()->enqueue(test, i);
    }

    sleep(10);
    return 0;
}