#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

int main(int argc, char **argv) {
  if (argc > 1) {
    for (int i=1; i<argc; ++i) {
      if (std::string{argv[1]}.find("-h") != std::string::npos) {
	std::cerr << "Usage: solves the day 1 puzzle (count number of "
	  "increasing values in a data stream and write the answer to stdout) "
	  " with input streamed into stdin. Example: cat input | " << argv[0]
		  << std::endl; // flush on purpose
	return 0;
      }
    }
  }
  std::size_t count = 0;
  std::string line;
  std::getline(std::cin, line);
  int prev = std::atoi(line.c_str());
  while (std::getline(std::cin, line)) {
    int val = std::atoi(line.c_str());
    if (val > prev) {
      ++count;
    }
    prev = val;
  }
  std::cout << count << '\n';
  return 0;
}
	
