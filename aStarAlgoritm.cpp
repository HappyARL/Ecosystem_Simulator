//
// Created by Арлан on 11.05.2023.
//

#include "aStarAlgoritm.h"

#include <cmath>
#include <chrono>
#include <iostream>
#include <float.h>
#include <utility>

void aStarAlgoritm::Init_variables(std::vector<std::vector<int> > map) {
  this->original_map = std::move(map);
}

bool aStarAlgoritm::isValid(int x, int y) {
  if (this->original_map[x][y] == 0) {
    return true;
  }
  return false;
}

bool aStarAlgoritm::isDestination(int x, int y, Node dest) {
  if (x == dest.x && y == dest.y) {
    return true;
  }
  return false;
}

double aStarAlgoritm::calculateH(int x, int y, Node dest) {
  double H = (sqrt((x - dest.x)*(x - dest.x) + (y - dest.y)*(y - dest.y)));
  return H;
}

std::vector<Node> aStarAlgoritm::makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest) {
  try {
    std::cout << "Found a path" << std::endl;
    int x = dest.x;
    int y = dest.y;
    std::stack<Node> path;
    std::vector<Node> usablePath;

    while (!(map[x][y].parentX == x && map[x][y].parentY == y)
           && map[x][y].x != -1 && map[x][y].y != -1)
    {
      path.push(map[x][y]);
      int tempX = map[x][y].parentX;
      int tempY = map[x][y].parentY;
      x = tempX;
      y = tempY;

    }
    path.push(map[x][y]);

    while (!path.empty()) {
      Node top = path.top();
      path.pop();
      usablePath.emplace_back(top);
    }
    return usablePath;
  }
  catch(const std::exception& e){
    std::cout << e.what() << std::endl;
  }
}

std::vector<Node> aStarAlgoritm::aStar(Node source, Node dest) {
  std::vector<Node> empty;
  if (isValid(dest.x, dest.y) == false) {
    std::cout << "Destination is an obstacle" << std::endl;
    return empty;
    //Destination is invalid
  }
  if (isDestination(source.x, source.y, dest)) {
    std::cout << "You are the destination" << std::endl;
    return empty;
  }
  bool closedList[(X_MAX / X_STEP)][(Y_MAX / Y_STEP)];

  //Initialize whole map
  std::array<std::array < Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> allMap;
  for (int x = 0; x < (X_MAX / X_STEP); x++) {
    for (int y = 0; y < (Y_MAX / Y_STEP); y++) {
      allMap[x][y].fCost = FLT_MAX;
      allMap[x][y].gCost = FLT_MAX;
      allMap[x][y].hCost = FLT_MAX;
      allMap[x][y].parentX = -1;
      allMap[x][y].parentY = -1;
      allMap[x][y].x = x;
      allMap[x][y].y = y;

      closedList[x][y] = false;
    }
  }

  //Initialize our starting list
  int x = source.x;
  int y = source.y;
  allMap[x][y].fCost = 0.0;
  allMap[x][y].gCost = 0.0;
  allMap[x][y].hCost = 0.0;
  allMap[x][y].parentX = x;
  allMap[x][y].parentY = y;

  std::vector<Node> openList;
  openList.emplace_back(allMap[x][y]);
  bool destinationFound = false;

  while (!openList.empty()&&openList.size()<(X_MAX / X_STEP)*(Y_MAX / Y_STEP)) {
    Node node;
    do {
      float temp = FLT_MAX;
      std::vector<Node>::iterator itNode;
      for (std::vector<Node>::iterator it = openList.begin();
           it != openList.end(); it = next(it)) {
        Node n = *it;
        if (n.fCost < temp) {
          temp = n.fCost;
          itNode = it;
        }
      }
      node = *itNode;
      openList.erase(itNode);
    } while (isValid(node.x, node.y) == false);

    x = node.x;
    y = node.y;
    closedList[x][y] = true;

    //For each neighbour starting from North-West to South-East
    for (int newX = -1; newX <= 1; newX++) {
      for (int newY = -1; newY <= 1; newY++) {
        double gNew, hNew, fNew;
        if (isValid(x + newX, y + newY)) {
          if (isDestination(x + newX, y + newY, dest))
          {
            //Destination found - make path
            allMap[x + newX][y + newY].parentX = x;
            allMap[x + newX][y + newY].parentY = y;
            destinationFound = true;
            return makePath(allMap, dest);
          }
          else if (closedList[x + newX][y + newY] == false)
          {
            gNew = node.gCost + 1.0;
            hNew = calculateH(x + newX, y + newY, dest);
            fNew = gNew + hNew;
            // Check if this path is better than the one already present
            if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
                allMap[x + newX][y + newY].fCost > fNew)
            {
              // Update the details of this neighbour node
              allMap[x + newX][y + newY].fCost = fNew;
              allMap[x + newX][y + newY].gCost = gNew;
              allMap[x + newX][y + newY].hCost = hNew;
              allMap[x + newX][y + newY].parentX = x;
              allMap[x + newX][y + newY].parentY = y;
              openList.emplace_back(allMap[x + newX][y + newY]);
            }
          }
        }
      }
    }
  }
  if (destinationFound == false) {
    return empty;
  }
}

std::vector<std::pair<int, int> > aStarAlgoritm::got_to_position(int src_x, int src_y,
                                                                 int dst_x, int dst_y) {
  auto start = std::chrono::steady_clock::now();
  std::vector<std::pair<int, int> > res;

  Node src;
  src.x = src_x;
  src.y = src_y;
  src.fCost = 0.0;
  src.gCost = 0.0;
  src.hCost = 0.0;
  src.parentX = src.x;
  src.parentY = src.y;

  Node dst;
  dst.x = dst_x;
  dst.y = dst_y;
  
  std::vector<Node> path = aStar(src, dst);
  res.reserve(path.size());
  for (auto elem : path) {
    res.emplace_back(elem.x, elem.y);
  }
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  auto time = std::chrono::duration <double, std::milli> (diff).count();
  std::cout << time << " ms" << std::endl;
  std::reverse(res.begin(), res.end());
  return res;
}

aStarAlgoritm::aStarAlgoritm(std::vector<std::vector<int>> map) {
  this->Init_variables(map);
}

aStarAlgoritm::~aStarAlgoritm() {

}
