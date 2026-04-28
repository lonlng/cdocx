/// @file system/component_model/progress_changed_event_args.h
#ifndef __progress_changed_event_args_h__
#define __progress_changed_event_args_h__

#include <system/eventargs.h>

namespace System { namespace ComponentModel {

    /// An instance of this class is passed as the argument on to the ProgressChangedEventHandler delegate.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class ASPOSECPP_SHARED_CLASS ProgressChangedEventArgs : public EventArgs
    {
    public:
        /// Constructor
        /// @param progressPercentage The percentage of an asynchronous task that has been completed.
        /// @param userState A unique user state.
        ProgressChangedEventArgs(int progressPercentage, System::SharedPtr<System::Object> userState)
            : m_progressPercentage(progressPercentage)
            , m_userState(userState)
        {}

        /// Gets the asynchronous task progress percentage.
        inline int get_ProgressPercentage() const { return m_progressPercentage; }
        ///  Gets a unique user state.
        inline System::SharedPtr<System::Object> get_UserState() const { return m_userState; }

    private:
        int m_progressPercentage;
        System::SharedPtr<System::Object> m_userState;
    };

} }

#endif
