/// @file system/details/lambda_capture_holder.h
#pragma once

#include <system/details/is_forwarding_of.h>
#include <memory>
#include <type_traits>

namespace System { namespace Details {

/// Uses to hold a lambda capture.
/// @tparam T A lambda capture type.
template <typename T>
class LambdaCaptureHolder
{
    /// A held lambda capture.
    std::shared_ptr<T> m_capture;

public:
    /// Constructs a new instance of LambdaCaptureHolder. This method creates a copy of capture.
    /// @param capture A lambda capture to hold.
    LambdaCaptureHolder(const T& capture) : m_capture(std::make_shared<T>(capture)) {}

    /// Constructs a new instance of LambdaCaptureHolder. This method also creates a new instance of T.
    /// @param args Arguments that are passed to a constructor of T.
    template <typename... Args, typename = std::enable_if_t<!IsForwardingOf<LambdaCaptureHolder<T>, Args...>::value>>
    LambdaCaptureHolder(Args&&... args) : m_capture(std::make_shared<T>(std::forward<Args>(args)...)) {}

    /// Constructs a new instance of LambdaCaptureHolder to hold the default value of T.
    LambdaCaptureHolder() : m_capture(std::make_shared<T>()) {}

    /// Returns a held lambda capture.
    T& GetCapture() const
    {
        return *m_capture;
    }
};

}} // namespace System::Details
