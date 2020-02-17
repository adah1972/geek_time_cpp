#ifndef SINGLETON_H
#define SINGLETON_H

#include <atomic>
#include <mutex>

class singleton {
public:
    static singleton* instance();
    static void destroy();

    void do_something();

private:
    singleton();
    ~singleton();
    static std::mutex lock_;
    static std::atomic<singleton*> inst_ptr_;
};

#endif // SINGLETON_H
