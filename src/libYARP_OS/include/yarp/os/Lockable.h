// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 Robotics and Cognitive Sciences Department. IIT
 * Authors: Francesco Romano
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef YARP_LOCK_H
#define YARP_LOCK_H

#include <yarp/os/api.h>

namespace yarp {
    namespace os {
        class Lockable;
    }
}
/**
 * This interface defines the Lockable object.
 * A Lockable is a synchronization primitive that can be used to protect shared data from being
 * simultaneously accessed by multiple threads.
 * 
 *
 */
class YARP_OS_API yarp::os::Lockable
{
public:
    virtual ~Lockable();
    
   /**
    * @brief Lock the associated resource, waiting if the resource is busy.
    *
    * See the actual implementation documentation for the correct use
    */
   virtual void lock() = 0;

   /**
    * @brief Lock the associated resource if it is free.
    *
    * If the lock is successfully taken returns true, otherwise returns false
    * and no lock is taken.
    * See the actual implementation documentation for the correct use
    *
    * @return true if the associated resource was successfully locked.
    *
    */
   virtual bool tryLock() = 0;

   /**
    * @brief Unlock the associated resource thus freeing waiting threads.
    *
    * See the actual implementation documentation for the correct use
    *
    */
   virtual void unlock() = 0;
};


#endif /* end of include guard: YARP_LOCK_H */
