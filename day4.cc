#include "utils.h"
#include <array>
#include <utility>
#include <unordered_map>
#include <sstream>
#include <iterator>
#include <cstring>
struct card {
  std::array<std::array<std::pair<int, bool>, 5>, 5> values;
  std::unordered_map<int, std::pair<int, int>> indices;

  static card from(std::istream& stream) {
    std::string line;
    card result;
    int i=0;
    int skip_c = 0;
    while (i < 5) {
      std::getline(stream, line);
      if (line.empty()) {
	if (skip_c > 0 && i < 4) {
	  throw "skipped multiple lines! invalid input";
	}
	++skip_c;
	continue;
      }
      for (int j=0, k=0; j<line.size(); j+=3, ++k) {
	result.values[i][k].first = std::stoi(line.substr(j, 2));
	result.values[i][k].second = false;
	result.indices[result.values[i][k].first] = std::make_pair(i, k);
      }
      ++i;
    }
    return result;
  }

  int score() const noexcept
  {
    int tot = 0;
    bool is_any_winner = false;
    bool is_diag_winner = true;
    std::unordered_map<int, bool> marked;
    for (const auto& [val, _] : indices) {
      marked[val] = false;
    }
    for (int i=0; i<5; ++i) {
      if (!values[i][i].second) {
	is_diag_winner = false;
	if (!marked[values[i][i].first]) {
	  tot += values[i][i].first;
	  marked[values[i][i].first] = true;
	}
      }
      bool is_row_winner = true, is_col_winner = true;
      for (int j=0; j<5; ++j) {
	if (!values[i][j].second) {
	  is_row_winner = false;
	  if (!marked[values[i][j].first]) {
	    tot += values[i][j].first;
	    marked[values[i][j].first] = true;
	  }
	}
	if (!values[j][i].second) {
	  is_col_winner = false;
	  if (!marked[values[j][i].first]) {
	    tot += values[j][i].first;
	    marked[values[j][i].first] = true;
	  }
	}
      }
      if (is_row_winner || is_col_winner) is_any_winner = true;
    }
    if (is_diag_winner) is_any_winner = true;
    return is_any_winner ? tot : 0;
  }

  void mark(int num) {
    auto idxs = indices.find(num);
    if (idxs != indices.end()) {
      values[idxs->second.first][idxs->second.second].second = true;
    }
  }

};



int main(int argc, char **argv) {

  std::string draws;
  std::getline(std::cin, draws);
  std::vector<card> game;
  bool done = false;
  while (!std::cin.eof() && !done) {
    try {
      game.push_back(card::from(std::cin));
    } catch (const char *c) {
      std::cerr << c << '\n';
      done = true;
      break;
    }
  }
  long long score = 0;
  char *tok = strtok(const_cast<char*>(draws.c_str()), ",");
  while(tok) {
    auto val = std::atoi(tok);
    tok = strtok(NULL, ",");
    int max_winning_score = 0;
    for (auto& b : game) {
      b.mark(val);
      int c = b.score();
      if (c > 0) {
	// winning board
	max_winning_score = std::max(max_winning_score, c * val);
      }
    }
    if (max_winning_score > 0) {
      std::cout << max_winning_score << '\n';
      return 0;
    }
  }
  return 1;
}
