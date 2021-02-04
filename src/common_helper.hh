#if !defined(INX_COMMON_HELPER)
#define INX_COMMON_HELPER

#include <string>
#include <vector>
#include <sstream>

namespace inx {

bool is_prefix(const std::string& prefix, const std::string& line);
bool extract_tokens(const std::string& line, char delimiter, std::vector<std::string>& tokens /* out */);
} // namespace inx

#endif // INX_COMMON_HELPER
