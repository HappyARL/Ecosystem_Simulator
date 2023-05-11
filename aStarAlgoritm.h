//
// Created by Арлан on 11.05.2023.
//

#ifndef GAME_ASTARALGORITM_H
#define GAME_ASTARALGORITM_H

#include <stack>
#include <vector>
#include <array>

#define X_MAX 50
#define X_STEP 1
#define Y_MAX 50
#define Y_STEP 1


struct Node {
  int y;
  int x;
  int parentX;
  int parentY;
  float gCost;
  float hCost;
  float fCost;
};

inline bool operator < (const Node& lhs, const Node& rhs) {
  return lhs.fCost < rhs.fCost;
}

class aStarAlgoritm {
 private:
  std::vector<std::vector<int> > original_map;

  void Init_variables(std::vector<std::vector<int>> map);
 public:
  // Functions
  bool isValid(int x, int y);
  bool isDestination(int x, int y, Node dest);
  double calculateH(int x, int y, Node dest);
  std::vector<Node> makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest);
  std::vector<Node> aStar(Node source, Node dest);
  std::vector<std::pair<int, int> > got_to_position(int src_x, int src_y, int dst_x, int dst_y);

  aStarAlgoritm(std::vector<std::vector<int>> map);
 ~aStarAlgoritm();
};


#endif //GAME_ASTARALGORITM_H
