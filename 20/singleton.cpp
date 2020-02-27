#include "singleton.h"
#include <iostream>  // std::cout

std::mutex singleton::lock_;
std::atomic<singleton*> singleton::inst_ptr_;

singleton* singleton::instance()
{
    singleton* ptr = inst_ptr_.load(std::memory_order_acquire);
    if (ptr == nullptr) {
        std::lock_guard<std::mutex> guard{lock_};
        ptr = inst_ptr_.load(std::memory_order_relaxed);
        if (ptr == nullptr) {
            ptr = new singleton();
            inst_ptr_.store(ptr, std::memory_order_release);
        }
    }
    return inst_ptr_;
}

void singleton::destroy()
{
    std::lock_guard<std::mutex> guard{lock_};
    singleton* ptr = inst_ptr_.load(std::memory_order_acquire);
    if (ptr) {
        delete ptr;
        inst_ptr_.store(nullptr, std::memory_order_release);
    }
}

singleton::singleton()
{
    std::cout << "singleton is created\n";
}

singleton::~singleton()
{
    std::cout << "singleton is destroyed\n";
}

void singleton::do_something()
{
}
