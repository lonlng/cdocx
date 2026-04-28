/// @file system/details/makeobject_leakage_detector.h
#pragma once

#include <string>
#include <typeinfo>

#include "system/diagnostics/debug.h"
#include "defines.h"

namespace System {
    class Object;
}

namespace System { namespace Details {

/// Checks if count of shared pointers to passed object differs from 0 after object construction completion.
class MakeObjectLeakageDetector
{
public:
    enum class LeakOrigin : uint8_t
    {
        FromMakeObject,
        FromDestructor,
        Cycle
    };

#if defined(ENABLE_MAKE_OBJECT_LEAKAGE_DETECTION)
    /// Helper structure to implement backtracing mechanism for static thread_local variables used by MakeObjectLeakageDetector.
    struct SignatureBacktraceSentry
    {
        /// Save current values of static thread_local variables to data-members of this class instance.
        /// Must be called before Object constructor call.
        SignatureBacktraceSentry()
        {
            signature = GetSignatureRef();
        }

        ///Reports leaks count to detector.
        /// @param obj Object that was constructed successfully.
        void CreatedSuccessfully(System::Object* obj)
        {
            System::Details::MakeObjectLeakageDetector::ReportLeakFromMakeObject(obj);
        }

        /// Revert changes of static thread_local variables
        ~SignatureBacktraceSentry()
        {
            GetSignatureRef() = signature;
        }

        /// Signature of caller method.
        std::string signature;

    private:
        SignatureBacktraceSentry(const SignatureBacktraceSentry&) = delete;
    };
#else
    /// Dummy class to be used in case of switched off make object leakage detection option.
    struct SignatureBacktraceSentry
    {
    public:
        /// Stub function that does nothing.
        SignatureBacktraceSentry() = default;

        /// Stub function that does nothing.
        void CreatedSuccessfully(System::Object*) {}

    private:
        SignatureBacktraceSentry(const SignatureBacktraceSentry&) = delete;
    };
#endif

#if defined(ENABLE_MAKE_OBJECT_LEAKAGE_DETECTION)
    /// Builds signature and stores it in thread_local variable.
    /// @tparam T Type of constructed object.
    /// @tparam Args Argument types passed to object constructor.
    /// @param object Constructed object.
    /// @param args Arguments passed to object constructor.
    template<class T, class ...Args>
    static void SetSignature(Args&&... args)
    {
        GetSignatureRef() = StringifyTypeAndArgTypes<T>(std::forward<Args>(args)...);
    }
#else
    /// Dummy function
    template<class T, class ...Args>
    static void SetSignature(Args&&...)
    {
    }
#endif

    /// Defines static thread_local signature string and returns reference to it.
    ASPOSECPP_SHARED_API static std::string& GetSignatureRef();

    /// Processes leak if count of shared pointers to passed object differs from 0.
    /// @tparam T Type of constructed object.
    /// @param object Constructed object.
    template<class T>
    static void ReportLeakFromMakeObject(T* object)
    {
        const auto leaked = object->SharedCount();
        if (leaked > 0)
        {
            ProcessLeak(object, GetSignatureRef(), leaked, LeakOrigin::FromMakeObject);
        }
    }

#if defined(ENABLE_MAKE_OBJECT_LEAKAGE_DETECTION)
    /// Processes leak if count of shared pointers to passed object differs from 0.
    /// @param leaked Number of leaked pointers.
    static void ReportLeakFromObjectDestructor(int leaked)
    {
        if (leaked > 0)
        {
            ProcessLeak(nullptr, GetSignatureRef(), leaked, LeakOrigin::FromDestructor);
        }
    }
#elif defined(_DEBUG) || defined(DEBUG)
    /// Processes leak if count of shared pointers to passed object differs from 0.
    /// @param leaked Number of leaked pointers.
    static void ReportLeakFromObjectDestructor(int leaked)
    {
        CODEPORTING_DEBUG_ASSERT(leaked == 0);
    }
#else
    /// Dummy function
    static void ReportLeakFromObjectDestructor(int)
    {
    }
#endif

#if defined(ENABLE_MAKE_OBJECT_LEAKAGE_DETECTION)
    /// Processes leak if count of shared pointers to passed object less than from 0.
    /// @param leaked Number of leaked pointers.
    static void ReportLeakCycle(int leaked)
    {
        if (leaked < 0)
        {
            ProcessLeak(nullptr, GetSignatureRef(), leaked, LeakOrigin::Cycle);
        }
    }
#elif defined(_DEBUG) || defined(DEBUG)
    /// Processes leak if count of shared pointers to passed object differs from 0.
    /// @param leaked Number of leaked pointers.
    static void ReportLeakCycle(int leaked)
    {
        CODEPORTING_DEBUG_ASSERT(leaked >= 0);
    }
#else
    /// Dummy function
    static void ReportLeakCycle(int)
    {
    }
#endif

    /// MakeObjectLeakageDetector stores leaks, but does not propagate them to handler or cerr until it is disabled.
    /// Once it is enabled, already stored leaks are propagated as well as newly created from this point.
    /// @param enable Flag to report leaks from destructors and/or MakeObject functions.
    /// @param reportLeaksFromMakeObject Flag to report leaks from MakeObject functions.
    static ASPOSECPP_SHARED_API void Set(bool enable, bool reportLeaksFromMakeObject);

private:

    /// Passes leak to leak storage.
    /// @param object Constructed object.
    /// @param signature System::MakeObject signature.
    /// @param leaked Leaked object shared pointer count.
    /// @param leak_origin Leak origin.
    static ASPOSECPP_SHARED_API void ProcessLeak(System::Object* object, const std::string& signature, int leaked, LeakOrigin leak_origin);

    /// Convert arg type to string.
    /// @tparam Arg Argument type.
    /// @param arg Argument to be converted to string.
    template<typename Arg>
    static std::string AppendArgType(Arg&& arg)
    {
        return typeid(arg).name();
    }

    /// Specialization for variadic template expansion - converts arg types to strings.
    /// @tparam Arg1 Argument type.
    /// @tparam Args Left expansion argument types.
    /// @param arg Argument to be converted to string.
    /// @param args Left expansion arguments to be converted to string.
    template<typename Arg1, typename ...Args>
    static std::string AppendArgType(Arg1&& arg, Args&&... args)
    {
        return std::string(typeid(arg).name()) + ", " + AppendArgType(std::forward<Args>(args)...);
    }

    /// Template to stringify constructed object type and System::MakeObject signature.
    /// @tparam T Constructed object type.
    /// @tparam Args Argument types passed to System::MakeObject.
    /// @param args Arguments passed to System::MakeObject.
    template<class T, class ...Args>
    static std::string StringifyTypeAndArgTypes(Args&&... args)
    {
        return  std::string("System::MakeObject<") + typeid(T).name() + ">(" + AppendArgType(std::forward<Args>(args)...) + ")";
    }

    /// Specialization for template without System::MakeObject arguments.
    /// @tparam T Constructed object type.
    template<class T>
    static std::string StringifyTypeAndArgTypes()
    {
        return  std::string("System::MakeObject<") + typeid(T).name() + ">()";
    }
};

} } // namespace System::Details
