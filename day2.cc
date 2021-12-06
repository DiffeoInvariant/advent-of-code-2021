#include "utils.h"


int main(int argc, char **argv) {
  long horiz = 0, depth = 0;
  if (argc > 1) {
    for (int i=1; i<argc; ++i) {
      if (std::string{argv[1]}.find("-h") != std::string::npos) {
	std::cerr << "Usage: solves the day 2 puzzle (compute final position, multiply horizontal times depth, and write the answer to stdout) "
	  " with input streamed into stdin. Example: cat input | " << argv[0]
		  << std::endl; // flush on purpose
	return 0;
      }
    }
  }

  for_each_line(std::cin, [&horiz, &depth](std::string line) {
			    std::size_t idx;
			    if ((idx = line.find("up")) != std::string::npos) {
			      depth -= std::atoi(line.c_str() + idx + sizeof("up"));
			    } else if ((idx = line.find("down")) != std::string::npos) {
			      depth += std::atoi(line.c_str() + idx + sizeof("down"));
			    } else if ((idx = line.find("forward")) != std::string::npos) {
			      horiz += std::atoi(line.c_str() + idx + sizeof("forward"));
			    } 
			  });
  std::cout << horiz * depth << '\n';
  return 0;
}
			      
