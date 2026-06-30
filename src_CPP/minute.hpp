/*------------------------------------------------------------------------------------------------------------------------------
//
//                                            __  __ _             _   _     _____    
//                                           |  \/  (_)_ __       | | | |   |_   _|__ 
//                                           | |\/| | | '_ \ _____| | | |_____| |/ _ \
//                                           | |  | | | | | |_____| |_| |_____| |  __/
//                                           |_|  |_|_|_| |_|      \___/      |_|\___|
//                                                    Minimal Unit Test support
//
// File:      minute.hpp
//
// Author:    Silvano Catinella
//
// Description
//
//
// Editor parameters: 128 cols, ts=6
------------------------------------------------------------------------------------------------------------------------------*/
#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <getopt.h>

#define OKSYMB  "[\033[1;32m  OK  \e[0m]"
#define ERRSYMB "[\033[1;31mERROR!\e[0m]"

#define ASSERT_EQ(x, y) \
	printf("%s ", (x == y) ? OKSYMB : ERRSYMB); std::cout << __func__ << "(" << __LINE__ << ")" << std::endl;

#define ASSERT_NE(x, y) \
	printf("%s ", (x != y) ? OKSYMB : ERRSYMB); std::cout << __func__ << "(" << __LINE__ << ")" << std::endl;

#define ASSERT_TRUE(x) \
	printf("%s ", (x)      ? OKSYMB : ERRSYMB); std::cout << __func__ << "(" << __LINE__ << ")" << std::endl;

#define WMASSERT_EQ(x, y, ...) \
	std::cout << std::string((x == y) ? OKSYMB : ERRSYMB) << std::string(" ") << __VA_ARGS__ << std::endl;

#define WMASSERT_NE(x, y, ...) \
	std::cout << std::string((x != y) ? OKSYMB : ERRSYMB) << std::string(" ") << __VA_ARGS__ << std::endl;

#define WMASSERT_TRUE(x, ...) \
	std::cout << std::string((x) ? OKSYMB : ERRSYMB) << std::string(" ") << __VA_ARGS__ << std::endl;

#define TEST(x, y)  void x##__##y() 

bool fileArgumentsDb_set (std::string arg_a, std::string value);
bool fileArgumentsDb_get (std::string arg_a);
bool fileArgumentsDb_get (std::string arg_a, std::string &value);
