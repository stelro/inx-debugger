#include "debugger.hh"

#include <sys/wait.h>
#include <sys/ptrace.h>

#include <utility>
#include <vector>

#include "common_helper.hh"

#include "linenoise.h"

namespace inx {

Debugger::Debugger(std::string program_name, pid_t pid) :
    program_name_(std::move(program_name)),
    proc_id_(pid) {  }

void Debugger::run() {

    int wait_status;
    auto options{0};
    waitpid(proc_id_, &wait_status, options);

    char* line = nullptr;

    while ((line = linenoise("inxgdb> ")) != nullptr) {
        handle_command_(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}

void Debugger::handle_command_(const std::string& line) {

    std::vector<std::string> tokens;
    [[maybe_unused]]bool status = extract_tokens(line, ' ', tokens);

    auto command = tokens[0];
    
    if (is_prefix(command, "continue")) {
        continue_execution_();
    } else if (is_prefix(command, "break")) {
        std::string addr{tokens[1], 2};
        set_breakpoint_at_address(std::stol(addr, 0, 16));
    } else {
        fprintf(stderr, "Unknown command\n");
    }
}

void Debugger::continue_execution_() {
    ptrace(PTRACE_CONT, proc_id_, nullptr, nullptr);

    int wait_status;
    auto options{0};
    waitpid(proc_id_, &wait_status, options);
}

void Debugger::set_breakpoint_at_address(std::intptr_t address) {

    printf("Set breakpoint at address %p", address);
    Breakpoint bp{proc_id_, address};
    bp.enable();
    breakpoints_.insert(std::make_pair(address, bp));
}



} // namespace inx
