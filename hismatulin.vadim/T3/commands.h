#ifndef commands_h
#define commands_h
#include "Polygon.h"

namespace T3_hism {
  double area(std::vector<Polygon>& data, std::string& arg);
  double maxArea(std::vector<Polygon>& data);
  int maxVertexes(std::vector<Polygon>& data);
  double minArea(std::vector<Polygon>& data);
  int minVertexes(std::vector<Polygon>& data);
  int count(std::vector<Polygon>& data, std::string& arg);
  int perms(std::vector<Polygon>& data, Polygon& polygon);
  std::string inframe(std::vector<Polygon>& data, Polygon& polygon);
}
#endif
