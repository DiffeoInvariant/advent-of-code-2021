#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <functional>
#include <exception>

using line_fn = std::function<void(std::string)>;

void for_each_line(std::istream& stream, const line_fn& f) {
  std::string line;
  while (std::getline(stream, line)) {
    try {
      f(line);
    } catch (const std::exception&) {
      continue;
    }
    catch (...) {
      throw;
    }
  }
}

#endif // UTILS_H
