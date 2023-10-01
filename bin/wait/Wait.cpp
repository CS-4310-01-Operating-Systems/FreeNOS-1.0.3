#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"
#include "sys/wait.h"
#include <ProcessClient.h>
#include <Macros.h>

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Waiting for some time");
    parser().registerPositional("PID", "Wait for the method pid");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    const ProcessClient process;
    ProcessID pid = (atoi(arguments().get("PROCESS_ID")));
    
    ProcessClient::Info info;
    const ProcessClient::Result result = process.processInfo(pid, info);
    
    if (result == ProcessClient::Success) {
        waitpid(pid, 0, 0);        
    } else {
        // using FreeNOS convention for printing errors
        ERROR("No process with ID '" << arguments().get("PROCESS_ID"))
        return InvalidArgument;
    }
    
    // if waiting was successful
    return Success;
    
    /*
    
    pid_t pid = (atoi(arguments().get("PID")));
    // Wait now
    if (pid.getState() == Success) {
        waitpid(pid, 0, 0);        
    } else {
        ERROR("failed to Wait: " << arguments().get("PROCESS_ID"));
        return InvalidArgument;
    
    */
        
    }

    // Done
    return Success;
}
