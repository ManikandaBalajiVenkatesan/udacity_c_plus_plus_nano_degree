#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
std::string ElapsedTime(long times);  // TODO: See src/format.cpp
std::string string_conv(int data);	//to convert the time into padded string
};                                    // namespace Format

#endif