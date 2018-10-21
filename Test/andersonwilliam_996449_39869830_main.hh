#include <string>
#include <queue>
#include <stdexcept>

int main() noexcept;

int parseInt(const std::string &arg, int min, int max) throw(std::invalid_argument);

std::string parseString(std::queue<std::string> &arguments) throw(std::invalid_argument);

std::string parseQuotedString(std::queue<std::string> &arguments) throw(std::invalid_argument);

bool processCommand(std::queue<std::string> &arguments) noexcept;