#pragma once

#include<vector>
extern "C" __declspec(dllexport) unsigned long long Prod(const std::vector<double>&v, const int& position_of_num, const int& size);

extern "C" __declspec(dllexport) int GetInt();
extern "C" __declspec(dllexport) double GetDouble();
