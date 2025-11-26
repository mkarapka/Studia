#include "fs.hpp"


int main() {
  std::ifstream file_in("zad_input.txt");
  vec2char board;

  std::string line;

  while (std::getline(file_in, line)) {
    std::vector<char> row;
    for (char &field : line) {
      row.push_back(field);
    }
    board.push_back(row);
  }
  file_in.close();

  for (auto &line : board) {
    for (auto &field : line) {
      std::cout << field;
    }
    std::cout << std::endl;
  }
  pair_set start_points = get_points(board, 'S');
  pair_set goal_points = get_points(board, 'G');

  std::string path = Astar(board, start_points, goal_points);
  // std::string path = "";
  // std::cout << board.size() << std::endl;
  // std::cout << board[board.size() - 2][-2] << std::endl;
  // std::cout << "ehj" << std::endl;

  // for (auto& field : board.back()){
  //     std::cout <<"siema" <<field << std::endl;
  // }
  // std::cout << "Path GÓWNO" << std::endl;
  std::ofstream file_out("zad_output.txt");

  std::cout << "Path: " << path;

  file_out << path;
  file_out.close();
}
