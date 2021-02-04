#if !defined(INX_DEBUGGER_HEADER)
#define INX_DEBUGGER_HEADER

#include <unistd.h>
#include <string>

namespace inx {
    
class Debugger {
public:
    Debugger(std::string program_name, pid_t pid);
    void run();

private:
    void handle_command_(const std::string& line);
    void continue_execution_();

    std::string program_name_;
    pid_t proc_id_;
};

} // namespace inx

#endif // INX_DEBUGGER_HEADER
