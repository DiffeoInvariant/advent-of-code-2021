#include "utils.h"
#include <bitset>
#include <vector>
#include <array>

int main(int argc, char **argv) {
  std::string first;
  std::getline(std::cin, first);
  std::bitset<12> bits(first, 0, first.size());
  std::vector<std::array<int, 2>> counts(first.size());
  auto update_counts = [&counts](std::bitset<12> b) {
			 for (std::size_t i=0; i<b.size(); ++i) {
			   if (b[i]) {
			     ++counts[i][1];
			   } else {
			     ++counts[i][0];
			   }
			 }
		       };
  update_counts(bits);
  for_each_line(std::cin, [&counts, &update_counts](std::string line) {
			    update_counts(std::bitset<12>(line, 0, line.size()));
			  });
  std::bitset<12> most_common(std::string(counts.size(), '0'), 0, counts.size()),
    least_common(std::string(counts.size(), '0'), 0, counts.size());

  for (std::size_t i=0; i<counts.size(); ++i) {
    if (counts[i][1] > counts[i][0]) {
      most_common[i] = 1;
      least_common[i] = 0;
    } else {
      most_common[i] = 0;
      least_common[i] = 1;
    }
  }

  std::cout << most_common.to_ulong() * least_common.to_ulong() << '\n';
  return 0;
}
