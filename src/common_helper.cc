#include "common_helper.hh"

namespace inx {

bool is_prefix(const std::string& prefix, const std::string& line) {
    if (prefix.size() > line.size())
        return false;
    return std::equal(prefix.begin(), prefix.end(), line.begin());
}

bool extract_tokens(const std::string& line, char delimiter, std::vector<std::string>& tokens /* out */) {
    if (line.empty()) {
        return false;
    }

    std::stringstream ss{line};
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        return false;
    }

    return true;
}

} // namespace inx
