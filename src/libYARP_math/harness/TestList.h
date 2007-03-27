// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef _YARP2_MATHTESTLIST_
#define _YARP2_MATHTESTLIST_

#include <yarp/UnitTest.h>

namespace yarp {
    class TestList;
}

// need to made one function for each new test, and add to collectTests()
// method.
extern yarp::UnitTest& getMathTest();

class yarp::TestList {
public:
    static void collectTests() {
        UnitTest& root = UnitTest::getRoot();
        root.add(getMathTest());
    }
};

#endif

