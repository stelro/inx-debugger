#include "registers.hh"

#include <sys/ptrace.h>

#include <algorithm>
#include <stdexcept>

namespace inx {

uint64_t get_register_value(pid_t pid, reg r) {

    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);

    // TODO(rstelmac): replace this 'hack' with a big switch statement
    auto it = std::find_if(g_register_descriptors.begin(), g_register_descriptors.end(),
            [r](auto&& rd) { return rd.r == r; });

    // The cast here is safe because user_regs_struct is standard layout, but the pointer
    // arithmetic probably is technically UB.
    return *(reinterpret_cast<uint64_t*>(&regs) + (it - begin(g_register_descriptors)));
}

void set_register_value(pid_t pid, reg r, uint64_t value) {
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, nullptr, &regs);

    auto it = std::find_if(g_register_descriptors.begin(), g_register_descriptors.end(),
            [r](auto&& rd) { return rd.r == r; });

    // The cast here is safe because user_regs_struct is standard layout, but the pointer
    // arithmetic probably is technically UB.
    *(reinterpret_cast<uint64_t*>(&regs) + (it - begin(g_register_descriptors))) = value;
    ptrace(PTRACE_SETREGS, pid, nullptr, regs);
}

uint64_t get_register_value_from_dwarf_register(pid_t pid, unsigned regnum) {

    auto it = std::find_if(g_register_descriptors.begin(), g_register_descriptors.end(),
            [regnum](auto&& rd) { return rd.dwarf_r == regnum; });
    if (it == g_register_descriptors.end()) {
        throw std::out_of_range{"Unknown dwarf register"};
    }

    return get_register_value(pid, it->r);
}

std::string get_register_name(reg r) {
     auto it = std::find_if(g_register_descriptors.begin(), g_register_descriptors.end(),
            [r](auto&& rd) { return rd.r == r; });
     return it->name;
}

reg get_register_from_name(const std::string& name) {
     auto it = std::find_if(g_register_descriptors.begin(), g_register_descriptors.end(),
            [name](auto&& rd) { return rd.name == name; });
     return it->r;
}
} // namespace inx
