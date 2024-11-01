#include <iomanip>
#include <fstream>
#include <numeric>
#include <algorithm>
#include "commands.h"

using namespace T3_hism;

int main(int argc, char* argv[]) {

  // EVEN - 0;2;4;6;..., ODD - 1;3;5;7...
  setlocale(LC_ALL, "ru");

  if (argc != 2) {
    std::cerr << "Ошибка: Параметр командной строки filename не задан!" << std::endl;
    return 1;
  }

  std::ifstream fin(argv[1]);
  if (!fin.is_open()) {
    std::cerr << "Ошибка: Файл не был найден..." << std::endl;
    return 1;
  }

  std::vector<Polygon> data;
  data = readStream(fin);

  std::cout << std::setprecision(1) << std::fixed;

  try {
    while (!std::cin.eof()) {
      std::string command = "";
      std::string arg;
      std::cin >> command;
      try {
        if (command == "AREA") {
          arg = "";
          std::cin >> arg;
          std::cout << area(data, arg) << std::endl;
        }
        else if (command == "MAX") {
          arg = "";
          std::cin >> arg;
          if (arg == "AREA") {
            std::cout << maxArea(data) << std::endl;
          }
          else if (arg == "VERTEXES") {
            std::cout << maxVertexes(data) << std::endl;
          }
          else {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
        }
        else if (command == "MIN") {
          arg = "";
          std::cin >> arg;
          if (arg == "AREA") {
            std::cout << minArea(data) << std::endl;
          }
          else if (arg == "VERTEXES") {
            std::cout << minVertexes(data) << std::endl;
          }
          else {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
        }
        else if (command == "COUNT") {
          arg = "";
          std::cin >> arg;
          std::cout << count(data, arg) << std::endl;
        }
        else if (command == "PERMS") {
          Polygon input_polygon;
          std::cin >> input_polygon;
          if (!std::cin) {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
          std::cout << perms(data, input_polygon) << std::endl;
        }
        else if (command == "INFRAME") {
          Polygon input_polygon;
          std::cin >> input_polygon;
          if (!std::cin) {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
          std::cout << inframe(data, input_polygon) << std::endl;
        }
        else if (command != "") {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      }
      catch (const std::invalid_argument& exception) {
        std::cout << exception.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    return 0;
  }
  catch (...) {
    std::cerr << "Произошла непредвиденная ошибка..." << std::endl;
    return 1;
  }
}
