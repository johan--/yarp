/*
 * Copyright (C) 2012-2014  iCub Facility, Istituto Italiano di Tecnologia
 * Author: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 *
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <yarp/os/Log.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include <cstdlib>
#include <cstring>
#include <cstdarg>

#ifdef YARP_HAS_ACE
# include <ace/Stack_Trace.h>
#elif defined(YARP_HAS_EXECINFO)
# include <execinfo.h>
#endif

#include <yarp/conf/system.h>
#include <yarp/os/Os.h>
#include <yarp/os/LogStream.h>
#include <yarp/os/impl/PlatformStdio.h>


#define YARP_MAX_LOG_MSG_SIZE 512

#ifndef WIN32

 #define RED     (colored_output ? "\033[01;31m" : "")
 #define GREEN   (colored_output ? "\033[01;32m" : "")
 #define YELLOW  (colored_output ? "\033[01;33m" : "")
 #define BLUE    (colored_output ? "\033[01;34m" : "")
 #define MAGENTA (colored_output ? "\033[01;35m" : "")
 #define CYAN    (colored_output ? "\033[01;36m" : "")
 #define WHITE   (colored_output ? "\033[01;37m" : "")
 #define RED_BG  (colored_output ? "\033[01;41m" : "")
 #define CLEAR   (colored_output ? "\033[00m" : "")

#else // WIN32

 // TODO colored and verbose_output for WIN32
 #define RED     ""
 #define GREEN   ""
 #define YELLOW  ""
 #define BLUE    ""
 #define MAGENTA ""
 #define CYAN    ""
 #define WHITE   ""
 #define RED_BG  ""
 #define CLEAR   ""

#endif // WIN32


std::ofstream yarp::os::Log::ftrc;
std::ofstream yarp::os::Log::fout;
std::ofstream yarp::os::Log::ferr;

bool yarp::os::Log::colored_output(getenv("YARP_COLORED_OUTPUT") && (strcmp(yarp::os::getenv("YARP_COLORED_OUTPUT"), "1") == 0));
bool yarp::os::Log::verbose_output(getenv("YARP_VERBOSE_OUTPUT") && (strcmp(yarp::os::getenv("YARP_VERBOSE_OUTPUT"), "1") == 0));
bool yarp::os::Log::trace_output(getenv("YARP_TRACE_ENABLE") && (strcmp(yarp::os::getenv("YARP_TRACE_ENABLE"), "1") == 0));



yarp::os::Log::Log(const char *file,
                   unsigned int line,
                   const char *func) :
        file(file),
        line(line),
        func(func)
{
}

yarp::os::Log::Log() :
        file(NULL),
        line(0),
        func(NULL)
{
}

void yarp::os::Log::print_output(LogType t,
                                 const char *msg,
                                 const char *file,
                                 unsigned int line,
                                 const char *func)
{
    switch (t) {
    case TraceType:
        if(trace_output)
        if (ftrc.is_open()) {
            if (verbose_output) {
                ftrc << "T: " << file << ":" << line << " " << func << ":" << msg << std::endl;
            } else {
                ftrc << "TRACE: " << func << msg << std::endl;
            }
        } else {
            if (verbose_output) {
                std::cout << WHITE << "T" << CLEAR << ": " << file << ":" << line << " " << WHITE << func << CLEAR << ": " << msg << std::endl;
            } else {
                std::cout << "[" << WHITE << "TRACE" << CLEAR << "]" << func << msg << std::endl;
            }
        }
        break;
    case DebugType:
        if (fout.is_open()) {
            if (verbose_output) {
                fout << "D: " << file << ":" << line << " " << func << ":" << msg << std::endl;
            } else {
                fout << "DEBUG: " << msg << std::endl;
            }
        } else {
            if (verbose_output) {
                std::cout << GREEN << "D" << CLEAR << ": " << file << ":" << line << " " << GREEN << func << CLEAR << ": " << msg << std::endl;
            } else {
                std::cout << "[" << GREEN << "DEBUG" << CLEAR << "]" << msg << std::endl;
            }
        }
        break;
    case InfoType:
        if (fout.is_open()) {
            if (verbose_output) {
                fout << "I: " << file << ":" << line << " " << func << ":" << msg << std::endl;
            } else {
                fout << "INFO: " << msg << std::endl;
            }
        } else {
            if (verbose_output) {
                std::cout << BLUE << "I" << CLEAR << ": " << file << ":" << line << " " << BLUE << func << CLEAR << ": " << msg << std::endl;
            } else {
                std::cout << "[" << BLUE     << "INFO" << CLEAR << "]" << msg << std::endl;
            }
        }
        break;
    case WarningType:
        if (ferr.is_open()) {
            if (verbose_output) {
                ferr << "W: " << file << ":" << line << " " << func << ":" << msg << std::endl;
            } else {
                ferr << "WARNING: " << msg << std::endl;
            }
        }
        if (verbose_output) {
            std::cerr << YELLOW << "W" << CLEAR << ": " << file << ":" << line << " " << YELLOW << func << CLEAR << ": " << msg << std::endl;
        } else {
            std::cerr << "[" << YELLOW << "WARNING" << CLEAR << "]" << msg << std::endl;
        }
        break;
    case ErrorType:
        if (ferr.is_open()) {
            if (verbose_output) {
                ferr << "E: " << file << ":" << line << " " << func << ":" << msg << std::endl;
            } else {
                ferr << "ERROR: " << msg << std::endl;
            }
        }
        if (verbose_output) {
            std::cerr << RED << "E" << CLEAR << ": " << file << ":" << line << " " << RED << func << CLEAR << ": " << msg << std::endl;
        } else {
            std::cerr << "[" << RED << "ERROR" << CLEAR << "]" << msg << std::endl;
        }
        break;
    case FatalType:
        if (ferr.is_open()) {
            if (verbose_output) {
                ferr << "F: " << file << ":" << line << " " << func << ":" << msg << std::endl;
            } else {
                ferr << "FATAL: " << msg << std::endl;
            }
        }
        if (verbose_output) {
            std::cerr << WHITE << RED_BG << "F" << CLEAR << ": " << file << ":" << line << " " << WHITE << RED_BG << func << CLEAR << ": " << msg << std::endl;
        } else {
            std::cerr << "["<< WHITE << RED_BG << "FATAL" << CLEAR << "]" << msg << std::endl;
        }
        yarp_print_trace(stderr, file, line);
        yarp::os::exit(-1);
        break;
    default:
        break;
    }
}


void yarp::os::Log::trace(const char *msg, ...) const
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[YARP_MAX_LOG_MSG_SIZE];
        ACE_OS::vsnprintf(buf, YARP_MAX_LOG_MSG_SIZE, msg, args);
        print_output(yarp::os::Log::TraceType, buf, file, line, func);
    }
    va_end(args);
}

yarp::os::LogStream yarp::os::Log::trace() const
{
    return yarp::os::LogStream(yarp::os::Log::TraceType, file, line, func);
}


void yarp::os::Log::debug(const char *msg, ...) const
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[YARP_MAX_LOG_MSG_SIZE];
        ACE_OS::vsnprintf(buf, YARP_MAX_LOG_MSG_SIZE, msg, args);
        print_output(yarp::os::Log::DebugType, buf, file, line, func);
    }
    va_end(args);
}

yarp::os::LogStream yarp::os::Log::debug() const
{
    return yarp::os::LogStream(yarp::os::Log::DebugType, file, line, func);
}


void yarp::os::Log::info(const char *msg, ...) const
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[YARP_MAX_LOG_MSG_SIZE];
        ACE_OS::vsnprintf(buf, YARP_MAX_LOG_MSG_SIZE, msg, args);
        print_output(yarp::os::Log::InfoType, buf, file, line, func);
    }
    va_end(args);
}

yarp::os::LogStream yarp::os::Log::info() const
{
    return yarp::os::LogStream(yarp::os::Log::InfoType, file, line, func);
}


void yarp::os::Log::warning(const char *msg, ...) const
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[YARP_MAX_LOG_MSG_SIZE];
        ACE_OS::vsnprintf(buf, YARP_MAX_LOG_MSG_SIZE, msg, args);
        print_output(yarp::os::Log::WarningType, buf, file, line, func);
    }
    va_end(args);
}

yarp::os::LogStream yarp::os::Log::warning() const
{
    return yarp::os::LogStream(yarp::os::Log::WarningType, file, line, func);
}


void yarp::os::Log::error(const char *msg, ...) const
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[YARP_MAX_LOG_MSG_SIZE];
        ACE_OS::vsnprintf(buf, YARP_MAX_LOG_MSG_SIZE, msg, args);
        print_output(yarp::os::Log::ErrorType, buf, file, line, func);
    }
    va_end(args);
}

yarp::os::LogStream yarp::os::Log::error() const
{
    return yarp::os::LogStream(yarp::os::Log::ErrorType, file, line, func);
}



void yarp::os::Log::fatal(const char *msg, ...) const
{
    va_list args;
    va_start(args, msg);
    if (msg) {
        char buf[YARP_MAX_LOG_MSG_SIZE];
        ACE_OS::vsnprintf(buf, YARP_MAX_LOG_MSG_SIZE, msg, args);
        print_output(yarp::os::Log::FatalType, buf, file, line, func);
    }
    va_end(args);
}

yarp::os::LogStream yarp::os::Log::fatal() const
{
    return yarp::os::LogStream(yarp::os::Log::FatalType, file, line, func);
}


void yarp::os::Log::setTraceFile(const std::string& filename)
{
    if(ftrc.is_open()) {
        ftrc.close();
    }
    ftrc.open(filename.c_str());
}


void yarp::os::Log::setOutputFile(const std::string& filename)
{
    if(fout.is_open()) {
        fout.close();
    }
    fout.open(filename.c_str());
}

void yarp::os::Log::setErrorFile(const std::string& filename)
{
    if(ferr.is_open()) {
        ferr.close();
    }
    ferr.open(filename.c_str());
}

void yarp_print_trace(FILE *out, const char *file, int line) {
#ifdef YARP_HAS_ACE
    ACE_Stack_Trace st(-1);
    // TODO demangle symbols using <cxxabi.h> and abi::__cxa_demangle
    //      when available.
    ACE_OS::fprintf(out, "%s", st.c_str());
#elif defined(YARP_HAS_EXECINFO)
    const size_t max_depth = 100;
    size_t stack_depth;
    void *stack_addrs[max_depth];
    char **stack_strings;
    stack_depth = backtrace(stack_addrs, max_depth);
    stack_strings = backtrace_symbols(stack_addrs, stack_depth);
    fprintf(out, "Assertion thrown at %s:%d by code called from:\n", file, line);
    for (size_t i = 1; i < stack_depth; i++) {
        fprintf(out, " --> %s\n", stack_strings[i]);
    }
    free(stack_strings); // malloc()ed by backtrace_symbols
    fflush(out);
}
#else
    // Not implemented on this platform
#endif
}
