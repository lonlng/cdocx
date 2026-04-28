/// @file net/web/services/protocol/invoke_completed_event_args.h
#pragma once

#include <system/array.h>
#include <system/component_model/async_completed_event_args.h>
#include <system/exceptions.h>
#include <system/object.h>
#include <system/shared_ptr.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// An instance of this class is passed as the argument on to the InvokeCompletedEventHandler delegate.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS InvokeCompletedEventArgs : public System::ComponentModel::AsyncCompletedEventArgs
{
public:
    /// Returns a collection of asynchronous operation results.
    /// @returns A collection of asynchronous operation results.
    ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<Object>> get_Results();

    /// Constructs a new instance.
    /// @param error Any error that occurred during an asynchronous operation.
    /// @param cancelled A value that indicates if an asynchronous operation is canceled.
    /// @param userState The optional user-supplied state object passed to the
    /// System.ComponentModel.BackgroundWorker.RunWorkerAsync(System.Object) method.
    /// @param results A collection of asynchronous operation results.
    ASPOSECPP_SHARED_API InvokeCompletedEventArgs(Exception error, bool cancelled, System::SharedPtr<Object> userState,
                                                  System::ArrayPtr<System::SharedPtr<Object>> results);

private:
    /// A collection of asynchronous operation results.
    System::ArrayPtr<System::SharedPtr<Object>> _results;
};

}}}} // namespace System::Web::Services::Protocols
