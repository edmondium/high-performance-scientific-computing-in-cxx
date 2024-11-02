#pragma once

#include <span>

// write function in terms of spans
auto compute(std::span<const double> u, std::span<const double> v) -> double;

