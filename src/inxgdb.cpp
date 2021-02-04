#include <unistd.h>
#include <sys/ptrace.h>

#include <cstdio>

#include "debugger.hh"

int main(int argc, char **argv) {
    
    if (argc < 2) {
        fprintf(stderr, "Program name not specified\n");
        return -1;
    }

    auto prog = argv[1];

    // If we are in the child process, for returns 0 and if we're in 
    // the parent process fork returns the process ID of the child process.
    auto pid = fork();
    if (pid == 0) {
        // We're in the child process
        //
        // The child process ( the tracer ) want to observe and control the execution
        // of anohter process ( the tracee ), and examine or change the tracee's memory
        // or registers.
        // TODO(rstelmac): check for return code, and handle the error code
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl(prog, prog, nullptr);
    } else if (pid >= 1) {
        // We're in the parent process
        printf("Started debugging process \"%d\"\"n", pid);
        inx::Debugger debugger{prog, pid};
        debugger.run();
    }

    return 0;
}
