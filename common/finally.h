#ifndef FINALLY_H
#define FINALLY_H

#include <exception>    // std::uncaught_exception(s)
#include <type_traits>  // std::decay_t
#include <utility>      // std::exchange/forward/move

template <typename T>
class final_action {
public:
    explicit final_action(T action) : action_(std::move(action)) {}

    final_action(final_action&& other) noexcept
        : action_(std::move(other.action_)),
          is_active_(std::exchange(other.is_active_, false))
    {
    }

    final_action(const final_action&) = delete;
    final_action& operator=(const final_action&) = delete;
    final_action& operator=(final_action&&) = delete;

    ~final_action()
    {
        if (is_active_) {
            action_();
        }
    }

    void dismiss() noexcept
    {
        is_active_ = false;
    }

private:
    T action_;
    bool is_active_{true};
};

template <typename T>
auto finally(T&& action)
{
    return final_action<std::decay_t<T>>(std::forward<T>(action));
}

// Similar to final_action, with the differences that the contained
// action will not be invoked when there are uncaught exceptions.
template <typename T>
class on_return_action {
public:
    explicit on_return_action(T action) : action_(std::move(action)) {}

    on_return_action(on_return_action&& other) noexcept
        : action_(std::move(other.action_)),
          is_active_(std::exchange(other.is_active_, false))
    {
    }

    on_return_action(const on_return_action&) = delete;
    on_return_action& operator=(const on_return_action&) = delete;
    on_return_action& operator=(on_return_action&&) = delete;

    ~on_return_action()
    {
        if (is_active_ &&
#if __cpp_lib_uncaught_exceptions >= 201411L
            std::uncaught_exceptions() == 0
#else
            !std::uncaught_exception()
#endif
        ) {
            action_();
        }
    }

    void dismiss() noexcept
    {
        is_active_ = false;
    }

private:
    T action_;
    bool is_active_{true};
};

template <typename T>
auto on_return(T&& action)
{
    return on_return_action<std::decay_t<T>>(std::forward<T>(action));
}

#endif // FINALLY_H
