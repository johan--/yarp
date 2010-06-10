// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006, 2008 Giorgio Metta, Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */


#include <ace/config.h>
//#include <ace/OS.h>
#include <ace/Log_Msg.h>

#include <yarp/os/impl/Address.h>
#include <yarp/os/impl/SocketTwoWayStream.h>
#include <yarp/os/impl/NameClient.h>
#include <yarp/os/impl/Companion.h>
#include <yarp/os/impl/PortCommand.h>

#include <yarp/os/Terminator.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>


using namespace yarp::os::impl;
using namespace yarp::os;

bool Terminator::terminateByName(const char *name) {
    if (name == NULL)
        return false;

    String s(name);

    if (YARP_STRSTR(s,"/quit")<0) {
        // name doesn't include /quit
        // old mechanism won't work, let's try new
        PortCommand pc('\0',"i");
        Companion::sendMessage(s,pc,true);
        return true;
    }

    if (name[0] != '/') {
        s.clear();
        s += "/";
        s += name;
    }

    Bottle cmd("quit"), reply;
    Contact c = NetworkBase::queryName(s.c_str());
    if (!c.isValid()) {
        fprintf(stderr,"Terminator port not found\n");
        return false;
    }
    ContactStyle style;
    style.quiet = false;
    style.carrier = "text";
    style.expectReply = false;
    NetworkBase::write(c,cmd,reply,style);

    return true;
}

/*
class TermineeHelper {
public:
    ACE_INET_Addr addr;
    ACE_SOCK_Acceptor acceptor;
    SocketTwoWayStream sock;
    char data[4];
    String registeredName;
};
#define HELPER(x) (*((TermineeHelper*)(x)))
*/

#define TermineeHelper Port
#define HELPER(x) (*((TermineeHelper*)(x)))


Terminee::Terminee(const char *name) {
    ok = false;
    if (name == NULL) {
        ACE_OS::printf("Terminator: Please supply a proper port name\n");
        return;
    }

    String s(name);
    if (name[0] != '/') {
        s.clear();
        s += "/";
        s += name;
    }
    
    /*
    NameClient& namer = NameClient::getNameClient();
    Address suggest = Address("...",0,"quit",s);
    Address a = namer.registerName(s,suggest);
	//ACE_OS::printf("listening address: %s port %d\n",a.getName().c_str(),a.getPort());

    implementation = new TermineeHelper;
    YARP_ASSERT(implementation!=NULL);
    TermineeHelper& helper = HELPER(implementation);

    helper.addr.set(a.getPort());
    helper.acceptor.open(helper.addr, 1);
    helper.registeredName = name;
    */

    implementation = new TermineeHelper();
    YARP_ASSERT(implementation!=NULL);
    TermineeHelper& helper = HELPER(implementation);
    ok = helper.open(s.c_str());
    if (!ok) {
        quit = true;
        fprintf(stderr,"Kill port conflict: make sure you supply a distinct --name /PORTNAME\n");
    } else {
        quit = false;
        start();
        ok = true;
    }
}

void Terminee::onStop()
{
    TermineeHelper& helper = HELPER(implementation);
    /*
    helper.sock.interrupt();
    helper.acceptor.close();
    */
    helper.close();
}

Terminee::~Terminee() {
    TermineeHelper& helper = HELPER(implementation);
    if (!quit) {
        //Terminator::terminateByName(helper.registeredName.c_str());
        Terminator::terminateByName(helper.getName().c_str());
    }
    
    // no longer needed, see onClose(), this better handles quit
    // (fixed bug on destructor) -- Lorenzo
    // helper.sock.interrupt();
    // helper.acceptor.close();
    
    // important: stop before deleting "implementation"
    stop(); 
    //NetworkBase::unregisterName(helper.registeredName.c_str());
    //NetworkBase::unregisterName(helper.registeredName.c_str());

    if (implementation!=NULL) {
        delete &HELPER(implementation);
    }
}


void Terminee::run() {
    TermineeHelper& helper = HELPER(implementation);
    while (!isStopping() && !quit) {
        Bottle cmd;
        helper.read(cmd);
        if (cmd.get(0).asString()=="quit") {
            quit = true;
        }
        /*
        helper.sock.open(helper.acceptor);
        Address a = helper.sock.getRemoteAddress();
        //ACE_OS::printf("incoming data: %s %d\n", a.getName().c_str(), a.getPort());
        helper.sock.read(Bytes(helper.data,4));
        if (helper.data[0] == 'q' &&
            helper.data[1] == 'u' &&
            helper.data[2] == 'i' &&
            helper.data[3] == 't') {
            quit = true;
            helper.sock.interrupt();
            helper.acceptor.close();
        } else {
            if (helper.data[0] == 'C' &&
                helper.data[1] == 'O' &&
                helper.data[2] == 'N' &&
                helper.data[3] == 'N') {
                // this is a standard YARP text mode connection

                // read introductory line
                helper.data[0] = 'x';
                while (helper.data[0]!='\n') {
                    helper.sock.read(Bytes(helper.data,1));
                }
                // read data tag line
                helper.data[0] = 'x';
                while (helper.data[0]!='\n') {
                    helper.sock.read(Bytes(helper.data,1));
                }
                // read actual data
                helper.sock.read(Bytes(helper.data,4));
                if (helper.data[0] == 'q' &&
                    helper.data[1] == 'u' &&
                    helper.data[2] == 'i' &&
                    helper.data[3] == 't') {
                    quit = true;
                    helper.sock.interrupt();
                    helper.acceptor.close();
                }
            }
        }
        */
    }
}
