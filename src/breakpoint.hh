#if !defined(BREAKPOINT_HEADER)
#define BREAKPOINT_HEADER

#include <cstdlib>
#include <cstdint>

namespace inx {
 
class Breakpoint {
public:
    Breakpoint(pid_t pid, std::intptr_t address);

    void enable();
    void disable();

    auto is_enabled() const -> bool { return enabled_; }
    auto get_address() const -> std::intptr_t { return address_; }
private:
    pid_t proc_id_;
    std::intptr_t address_;
    bool enabled_;

    // Data which used to be at the breakpoint address
    // Since we overwrite the the address location with INT 3 instruction (x86)
    // to cause software interupt
    uint8_t saved_data_;
};


} // namespace inx

#endif // BREAKPOINT_HEADER
