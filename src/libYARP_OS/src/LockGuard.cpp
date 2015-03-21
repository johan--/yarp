// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2013 iCub Facility
 * Authors: Francesco Romano
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <yarp/os/LockGuard.h>
#include <yarp/os/Lockable.h>

namespace yarp {
    namespace os {
        LockGuard::LockGuard(yarp::os::Lockable& _lock)
            : lock(_lock)
        {
            lock.lock();
        }
        
        LockGuard::~LockGuard()
        {
            lock.unlock();
        }
        
        LockGuard::LockGuard(const LockGuard& lg)
        : lock(lg.lock) { }
        
        LockGuard& LockGuard::operator=(const LockGuard&) { return *this; }
    }
}
