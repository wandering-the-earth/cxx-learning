#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
     DynFibonacci(int capacity) 
        : cache(new size_t[capacity]()), cached(2) {
        if (capacity < 2) {
            throw std::invalid_argument("Capacity must be at least 2");
        }
        cache[0] = 0;
        cache[1] = 1;
    }

    // 析构器：释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 斐波那契数计算（带缓存优化）
    size_t get(int i) {
        if (i < 0) {
            throw std::out_of_range("Index cannot be negative");
        }
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
