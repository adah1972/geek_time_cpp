#if __cplusplus > 201703L
#include <coroutine>               // coroutine_handle/suspend_always
using std::coroutine_handle;
using std::suspend_always;
#else
#include <experimental/coroutine>  // coroutine_handle/suspend_always
using std::experimental::coroutine_handle;
using std::experimental::suspend_always;
#endif
#include <iostream>                // std::cout/endl
#include <stdint.h>                // uint64_t

class uint64_resumable {
public:
    struct promise_type {
        uint64_t value_;
        using coro_handle = coroutine_handle<promise_type>;
        auto get_return_object()
        {
            return uint64_resumable{coro_handle::from_promise(*this)};
        }
        constexpr auto initial_suspend() noexcept { return suspend_always(); }
        constexpr auto final_suspend() noexcept { return suspend_always(); }
        auto yield_value(uint64_t value)
        {
            value_ = value;
            return suspend_always();
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using coro_handle = coroutine_handle<promise_type>;
    explicit uint64_resumable(coro_handle handle) : handle_(handle) {}
    ~uint64_resumable() { handle_.destroy(); }
    uint64_resumable(const uint64_resumable&) = delete;
    uint64_resumable(uint64_resumable&&) = default;
    bool resume();
    uint64_t get();

private:
    coro_handle handle_;
};

bool uint64_resumable::resume()
{
    if (!handle_.done())
        handle_.resume();
    return !handle_.done();
}

uint64_t uint64_resumable::get()
{
    return handle_.promise().value_;
}

uint64_resumable fibonacci()
{
    uint64_t a = 0;
    uint64_t b = 1;
    while (true) {
        co_yield b;
        auto tmp = a;
        a = b;
        b += tmp;
    }
}

int main()
{
    auto res = fibonacci();
    while (res.resume()) {
        auto i = res.get();
        if (i >= 10000) {
            break;
        }
        std::cout << i << std::endl;
    }
}
