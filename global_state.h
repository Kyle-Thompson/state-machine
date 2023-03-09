#pragma once

#include <__memory/construct_at.h>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

template <typename StateEnum>
struct BaseGlobalState {
  BaseGlobalState(std::byte* buf) : buffer_(buf) {}

  template <typename From, typename To, typename... T>
  StateEnum change_state(T&&... t) noexcept;

 private:
  std::byte* buffer_;
};

template <typename StateEnum>
template <typename From, typename To, typename... T>
StateEnum
BaseGlobalState<StateEnum>::change_state(T&&... t) noexcept {
    std::destroy_at<From>(reinterpret_cast<From *>(buffer_));
    std::construct_at<To>(reinterpret_cast<To *>(buffer_), std::forward<T>(t)...);
    return To::STATE;
}
