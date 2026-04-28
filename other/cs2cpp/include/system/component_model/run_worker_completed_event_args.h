/// @file system/component_model/run_worker_completed_event_args.h
#ifndef __run_worker_completed_event_args_h__
#define __run_worker_completed_event_args_h__

#include <system/exceptions.h>
#include <system/component_model/async_completed_event_args.h>

namespace System { namespace ComponentModel {

    /// An instance of this class is passed as the argument to the RunWorkerCompletedEventHandler delegate.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class ASPOSECPP_SHARED_CLASS RunWorkerCompletedEventArgs : public AsyncCompletedEventArgs
    {
        /// This type.
        typedef RunWorkerCompletedEventArgs ThisType;
        /// Parent type.
        typedef System::ComponentModel::AsyncCompletedEventArgs BaseType;
        /// RTTI information.
        RTTI_INFO(System::ComponentModel::RunWorkerCompletedEventArgs, ::System::BaseTypesInfo<System::ComponentModel::AsyncCompletedEventArgs>);
    
    public:
        /// Constructor
        /// @param result The result of an asynchronous operation.
        /// @param error Any error that occurred during the asynchronous operation.
        /// @param canceled A value indicating whether the asynchronous operation was canceled.
        ASPOSECPP_SHARED_API RunWorkerCompletedEventArgs(const System::SharedPtr<System::Object>& result, const System::Exception &error, bool canceled);

        /// Gets a value that represents the result of an asynchronous operation.
        /// @return An System.Object representing the result of an asynchronous operation. 
        ASPOSECPP_SHARED_API System::SharedPtr<System::Object> get_Result() const;

    private:
        System::SharedPtr<System::Object> m_result;
    };

}}

#endif
