#pragma once

#include <string>
#include <vector>

#ifndef TEXTTOOL_H
#define TEXTTOOL_H

char asciitolower(char c);
std::string strToLower(std::string &str);
bool strInVec(std::string str, std::vector<std::string> v);
bool isNumber(std::string str);
std::vector<std::string> strToVector(std::string str);
void strCharSwap(std::string& str, const char c1, const char c2);
void removeChar(std::string& str, char c);
#endif
