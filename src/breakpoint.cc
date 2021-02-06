#include "breakpoint.hh"

#include <sys/ptrace.h>

namespace inx {

Breakpoint::Breakpoint(pid_t pid, std::intptr_t address) :
    proc_id_(pid),
    address_(address) {  }

void Breakpoint::enable() {

    auto data = ptrace(PTRACE_PEEKDATA, proc_id_, address_, nullptr);
    saved_data_ = static_cast<uint8_t>(data & 0xff); // save bottom byte
    // debugger interupt opcode for x86
    uint64_t int3 = 0xcc;
    uint64_t data_with_int3 = ((data & ~0xff) | int3); // set bottom byte to 0xcc
    // Set the breakpoint
    ptrace(PTRACE_POKEDATA, proc_id_, address_, data_with_int3);

    enabled_ = true;
}

void Breakpoint::disable() {

    auto data = ptrace(PTRACE_PEEKDATA, proc_id_, address_, nullptr);
    auto resotred_data = ((data & ~0xff) | saved_data_);
    ptrace(PTRACE_POKEDATA, proc_id_, address_, resotred_data);

    enabled_ = false;
}



} // namespace inx
