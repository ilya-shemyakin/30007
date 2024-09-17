#ifndef COMMANDS_H
#define COMMANDS_H
#include <vector>
#include "Polygon.h"
namespace dnlx
{
  int isArgANumber(const std::string& str);
  double area(std::vector<Polygon>& figures, const std::string& arg);
  double maxArea(std::vector<Polygon>& figures);
  int maxVertexes(std::vector<Polygon>& figures);
  double minArea(std::vector<Polygon>& figures);
  int minVertexes(std::vector<Polygon>& figures);
  int count(std::vector<Polygon>& figures, const std::string& arg);
  std::string inframe(std::vector<Polygon>& figures, Polygon& input);
  void intersections(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
}
#endif
