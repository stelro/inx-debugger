#if !defined(INX_DEBUGGER_HEADER)
#define INX_DEBUGGER_HEADER

#include <unistd.h>
#include <string>
#include <unordered_map>

#include "breakpoint.hh"

namespace inx {
    
class Debugger {
public:
    Debugger(std::string program_name, pid_t pid);
    void run();

    void set_breakpoint_at_address(std::intptr_t address);

private:
    void handle_command_(const std::string& line);
    void continue_execution_();

    std::string program_name_;
    pid_t proc_id_;

    std::unordered_map<std::intptr_t, Breakpoint> breakpoints_;
};

} // namespace inx

#endif // INX_DEBUGGER_HEADER
