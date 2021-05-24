#pragma once

#include <functional>
#include <vector>

namespace std
{
    template<typename T, typename X, typename Z> std::vector<Z> select(T, T, X);
}

#include "Extensions.ipp"