#pragma once
#include <string>
// I've read that to more accurately get unicode on Windows one should use wstrings so I am.
// All other systems use normal strings

#ifdef _WIN32
    typedef std::wstring td_string;
#else
    typedef std::string td_string;
#endif
