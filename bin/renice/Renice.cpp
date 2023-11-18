#include "sys/renice.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Renice.h"
#include <ProcessClient.h>

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Changes the scheduling priority of a running process.");
    parser().registerPositional("PRIORITY", "Change the priority to this level");
    parser().registerPositional("PROCESS_ID", "Change the priority of this process");
    parser().registerFlag('n', "priority", "change priority level");
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{ 
       if (arguments().get("priority")){
        const ProcessClient process; 
        ProcessID pid = (atoi(arguments().get("PROCESS_ID")));
        int priority = (atoi(arguments().get("PRIORITY")));

        ProcessClient::Info info; 
        const ProcessClient::Result result = process.processInfo(pid, info); 

        if(result != ProcessClient::Success) {
            //checks if the process exists or not
            ERROR("No process of ID '" << pid << "' is found")
            return InvalidArgument;
        }

        // check that the new priority is valid
        if(priority >= 1 && priority <= 5) {
            INFO("Process " << pid << "'s priority has been updated to " << priority);
            return Success;

        } else {
            ERROR("Invalid priority level. Failed to set priority for process " << pid)
            return InvalidArgument;
        }
        renicepid(pid, priority, 0, 0);
        printf("process %d set to priority %d, from priority %d\n", pid, priority, info.kernelState.priority);
    }
    
    // Done
    return Success;
}
