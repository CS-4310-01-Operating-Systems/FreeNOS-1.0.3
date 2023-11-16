// #include "sys/renice.h"
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
    // Done
    return Success;
}
