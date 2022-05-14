#ifndef FINALLY_H
#define FINALLY_H

#include <type_traits>  // std::decay_t
#include <utility>      // std::exchange/forward/move

template <typename T>
class final_action {
public:
    explicit final_action(T action) : action_(std::move(action)) {}

    final_action(final_action&& other)
        : action_(std::move(other.action_))
        , is_active_(std::exchange(other.is_active_, false))
    {}

    final_action(const final_action&) = delete;
    final_action& operator=(const final_action&) = delete;
    final_action& operator=(final_action&&) = delete;

    ~final_action()
    {
        if (is_active_) {
            action_();
        }
    }

    void dismiss() noexcept { is_active_ = false; }

private:
    T action_;
    bool is_active_{true};
};

template <typename T>
auto finally(T&& action)
{
    return final_action<std::decay_t<T>>(std::forward<T>(action));
}

#endif // FINALLY_H
