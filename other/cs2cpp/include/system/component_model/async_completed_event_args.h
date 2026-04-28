/// @file system/component_model/async_completed_event_args.h
#pragma once
#include <system/eventargs.h>
#include <system/exceptions.h>


namespace System { namespace ComponentModel {
    /// An instance of this class is passed as the argument on to the AsyncCompletedEventHandler delegate.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class ASPOSECPP_SHARED_CLASS AsyncCompletedEventArgs : public EventArgs
    {
        /// This type.
        typedef AsyncCompletedEventArgs ThisType;
        /// Parent type.
        typedef System::EventArgs BaseType;
        /// RTTI information.
        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        ASPOSECPP_SHARED_RTTI_INFO_DECL();

    public:
        /// Constructor
        ASPOSECPP_SHARED_API AsyncCompletedEventArgs();
        /// Initializes a new instance of the System.ComponentModel.AsyncCompletedEventArgs class.
        /// @param error Any error that occurred during the asynchronous operation.
        /// @param canceled A value indicating whether the asynchronous operation was canceled.
        /// @param userState The optional user-supplied state object passed to the System.ComponentModel.BackgroundWorker.RunWorkerAsync(System.Object) method.
        ASPOSECPP_SHARED_API AsyncCompletedEventArgs(const System::Exception &error, bool canceled, const System::SharedPtr<System::Object>& userState);
        /// Gets a value indicating which error occurred during an asynchronous operation.
        /// @return An System.Exception instance, if an error occurred during an asynchronous operation otherwise null.
        ASPOSECPP_SHARED_API const System::Exception & get_Error() const;
        /// Gets a value indicating whether an asynchronous operation has been canceled.
        /// true if the background operation has been canceled; otherwise false. The default is false.
        ASPOSECPP_SHARED_API bool get_Cancelled() const;
        /// Gets the unique identifier for the asynchronous task.
        /// An object reference that uniquely identifies the asynchronous task; otherwise, null if no value has been set.
        ASPOSECPP_SHARED_API System::SharedPtr<Object> get_UserState() const;

    protected:
        ASPOSECPP_SHARED_API void RaiseExceptionIfNecessary();

    private:
        const System::Exception m_error;
        bool m_cancelled;
        System::SharedPtr<Object> m_userState;
    };
}}
