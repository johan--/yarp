// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2013 iCub Facility
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef _YARP2_MUTEX_
#define _YARP2_MUTEX_

#include <yarp/os/api.h>
#include <yarp/os/Lockable.h>

namespace yarp {
    namespace os {
        class Mutex;
    }
}


/**
 *
 * Basic wrapper for mutual exclusion. Intended to match std::mutex in
 * C++11, for eventual replacement by that class.
 *
 */
class YARP_OS_API yarp::os::Mutex : public yarp::os::Lockable {
public:

    /**
     *
     * Constructor.
     *
     */
    Mutex();

    /**
     *
     * Destructor.
     *
     */
    virtual ~Mutex();

    /**
     *
     * Lock the associated resource, waiting if necessary.
     * Behavior is undefined if called by the thread currently locking
     * the resource.
     *
     */
    virtual void lock();

    /**
     *
     * Lock the associated resource if possible.  Don't wait.
     * Behavior is undefined if called by the thread currently locking
     * the resource.
     *
     * @return true if the associated resource was successfully locked.
     *
     */
    virtual bool tryLock();

    /**
     *
     * Unlock the associated resource.
     * If the resource is not currently locked by the calling thread,
     * the behavior is undefined.
     *
     */
    virtual void unlock();
private:
    void *implementation;
};


#endif
