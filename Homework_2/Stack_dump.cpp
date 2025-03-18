#include <cxxabi.h>
#include <execinfo.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

void stack_dump(int depth, std::ostream& os) {
    int max_frames = depth;
    void* callstack[max_frames];
    int frames = backtrace(callstack, max_frames);
    char** symbols = backtrace_symbols(callstack, frames);
    if (symbols == nullptr) {
        os << "Failed to get backtrace symbols" << std::endl;
        return;
    }
    int limit = std::min(frames, depth);
    os << "Stack trace (depth is " << limit - 2 << "):" << std::endl;
    for (int i = 2; i < limit; ++i) {
        std::string symbol(symbols[i]);
        size_t begin = symbol.find('(');
        size_t end = symbol.find('+', begin);
        if (begin != std::string::npos && end != std::string::npos) {
            std::string mangled_name = symbol.substr(begin + 1, end - begin - 1);
            int status;
            char* demangled_name = abi::__cxa_demangle(mangled_name.c_str(), nullptr, nullptr, &status);
            if (status == 0 && demangled_name != nullptr) {
                symbol = symbol.substr(0, begin + 1) + demangled_name + symbol.substr(end);
                free(demangled_name);
            }
        }
        os << "#" << i - 2 << " " << symbol << std::endl;
    }
}

void function3() {
    stack_dump(9, std::cout);
}

void function2() {
    function3();
}

void function1() {
    function2();
}

int main() {
    function1();
    return 0;
}