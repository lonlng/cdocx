/// @file system/collections/invalidatable.h
#pragma once

#include "system/exceptions.h"

namespace System { namespace Collections {

class InvalidatableTracker; // Forward declaration

/// Class that makes it possible to track the state of its descendants through InvalidatableTracker objects.
class ASPOSECPP_SHARED_CLASS Invalidatable
{
public:
    /// Returns current state.
    /// @return Current state
    ASPOSECPP_SHARED_API int64_t GetState();

    /// Changes the current state, invalidating all previously created trackers.
    ASPOSECPP_SHARED_API void Invalidate();

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API Invalidatable();

private:
    /// Current state.
    int64_t m_state;
};

/// Class that implements trackers of Invalidatable objects.
class ASPOSECPP_SHARED_CLASS InvalidatableTracker
{
public:
    /// Constructs a tracker object.
    /// @param invalidator A Invalidatable object, that is needed to be tracked
    ASPOSECPP_SHARED_API InvalidatableTracker(Invalidatable* invalidator);

    /// Checks if the state of the tracked object has changed.
    /// @return True if the state of the tracked object has not changed, false otherwise.
    ASPOSECPP_SHARED_API bool CheckValidity() const;

private:
    /// Tracked Invalidatable object.
    Invalidatable* m_invalidator;
    /// State of the tracked object at the time of the current tracker creation.
    int64_t m_state;
};

}} // namespace System::Collections
