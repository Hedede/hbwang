#ifndef PRINT_H
#define PRINT_H

#include <format>
#include <iostream>

template <typename... Args>
void println(std::string_view fmt, Args&&... args)
{
    auto res = std::format(fmt, std::forward<Args>(args)...);
    std::cout << res << std::endl; // NOLINT: flush is intentional
}

#endif // PRINT_H
