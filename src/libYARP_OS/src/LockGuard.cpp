// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2013 iCub Facility
 * Authors: Francesco Romano
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <yarp/os/LockGuard.h>

namespace yarp {
    namespace os {
        template <typename Lockable>
        AbstractLockGuard<Lockable>::AbstractLockGuard(Lockable& _lock)
            : lock(_lock)
        {
            lock.lock();
        }

        template <typename Lockable>
        AbstractLockGuard<Lockable>::~AbstractLockGuard()
        {
            lock.unlock();
        }

        template <typename Lockable>
        AbstractLockGuard<Lockable>::AbstractLockGuard(const AbstractLockGuard& lg)
        : lock(lg.lock) { }

        template <typename Lockable>
        AbstractLockGuard<Lockable>& AbstractLockGuard<Lockable>::operator=(const AbstractLockGuard&) { return *this; }
    }
}

//actual (and visible) implementations
#include <yarp/os/Mutex.h>
#include <yarp/os/RecursiveMutex.h>

template class YARP_OS_API yarp::os::AbstractLockGuard<yarp::os::Mutex>;
template class YARP_OS_API yarp::os::AbstractLockGuard<yarp::os::RecursiveMutex>;

