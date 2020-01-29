#pragma once
#include <string>
#include <exception>
#include "Log.h"
#include "Main.h"

/*******************************************************************************
 * List of exceptions.
 ******************************************************************************/
struct BoutEagleException : public std::exception {
public:
    BoutEagleException(std::string const &message) : msg(message) {}
    virtual const char* getMessage() const noexcept { return msg.c_str(); }
protected:
    std::string msg;
};

#define DEFINE_EXCEPTION(x) /*x = Exception class name */ \
    struct x : public BoutEagleException {\
    public:\
        x(std::string const &message) : BoutEagleException(message) {  }\
    }

DEFINE_EXCEPTION(UnsupportedTGAException);
DEFINE_EXCEPTION(ViewException);
DEFINE_EXCEPTION(IOException);
DEFINE_EXCEPTION(ResourceManagerException);

/*******************************************************************************
 * Macro to manually trigger an exception.
 ******************************************************************************/
#define THROW_EXCEPTION(type, params) {\
        try {\
            throw type(params);\
        } catch (BoutEagleException& myException) {\
            ExceptionHandler::Handle(myException);\
        }\
    }

/*******************************************************************************
 * Exception handler. Performs action(s) based on the given exception.
 ******************************************************************************/
namespace ExceptionHandler {
    inline void Handle(std::exception& e) {
        try {
            throw;
        } catch (const UnsupportedTGAException& e) {
            Log::Log(Log::WARNING, e.getMessage());
            return;
        } catch (const ViewException& e) {
            Log::Log(Log::FATAL, e.getMessage());
        } catch (const IOException& e) {
            Log::Log(Log::FATAL, e.getMessage());
        } catch (const ResourceManagerException& e) {
            Log::Log(Log::FATAL, e.getMessage());
        } catch (const BoutEagleException& e) {
            Log::Log(Log::INFO, e.getMessage());
            return;
        } catch (...) {
           Log::Log(Log::INFO, "Encountered an unhandled exception.");

           /* Perform standard actions after handling the exception if the
            * handler did not recover the situation. */
           Main::Abort();
       }


    }
}
