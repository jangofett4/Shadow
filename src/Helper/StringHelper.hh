#pragma once

#include <algorithm> 
#include <cctype>
#include <locale>

void ltrim(std::string&);
void rtrim(std::string&);
void trim(std::string&);

std::string ltrimc(std::string&);
std::string rtrimc(std::string&);
std::string trimc(std::string&);