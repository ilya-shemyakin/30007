#ifndef __COMMANDS_H_
#define __COMMANDS_H_

#include <vector>

#include "polygon.h"

namespace command
{
  int convertToNumber(const std::string& str);
  void area(const std::vector<skor::Polygon>& data, const std::string& arg);
  void max(const std::vector<skor::Polygon>& data, const std::string& arg);
  void min(const std::vector<skor::Polygon>& data, const std::string& arg);
  void count(const std::vector<skor::Polygon>& data, const std::string& arg);
  void rmecho(std::vector<skor::Polygon>& data);
  void inframe(const std::vector<skor::Polygon>& data);
}

#endif
