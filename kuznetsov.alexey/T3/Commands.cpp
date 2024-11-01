#include "Commands.h"

using namespace kuzn;
using namespace std::placeholders;

const std::string I_C = "<INVALID COMMAND>";

//Ïðåîáðàçîâàíèå ñòðîêè â ÷èñëî
int commands::convertToNumber(const std::string& str)
{
    char* end;
    //ñòðîêó â ÷èñëî (10 - ñèñòåìà ñ÷èñëåíèÿ,
    //end - óêàçàòåëü íà ïåðâûé ñèìâîë, êîòîðûé íå áûë ïðåîáðàçîâàí
    int convertedResult = strtol(str.c_str(), &end, 10);
    if (*end != 0)
    {
        return -1;
    }
    return convertedResult;
}

//Ïîëó÷åíèå îáùåé ïëîùàäè ôèãóð â çàâèñèìîñòè îò àðãóìåíòà
void commands::getFullArea(const std::vector<kuzn::Polygon>& polygons)
{
    std::string argument;
    std::cin >> argument;
    int number = convertToNumber(argument);
    auto accumulatePolygonsArea = //ïðèáàâëåíèå ïëîùàäè ïîëèãîíà ê îáùåé ïî íóæíûì ïðàâèëàì
        [&polygons, &number](double accumulatedArea, const kuzn::Polygon& current, const std::string method)
        {
            double result = accumulatedArea;
            if (method == "EVEN" && current.points.size() % 2 == 0)
            {
                result += current.getArea();
            }
            else if (method == "ODD" && current.points.size() % 2 != 0)
            {
                result += current.getArea();
            }
            else if (method == "MEAN")
            {
                result += current.getArea();
            }
            else if (method == "SPECIAL" && current.points.size() == static_cast<size_t>(number))
            {
                result += current.getArea();
            }
            return result;
        };
    if (number == -1)
    {
        if (argument == "EVEN" || argument == "ODD")
        {
            std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, //ñëîæåíèå ïëîùàäåé âñåõ ïîëèãîíîâ
                std::bind(accumulatePolygonsArea, _1, _2, argument)) << std::endl;
        }
        else if (argument == "MEAN" && polygons.size() != 0)
        {
            std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                std::bind(accumulatePolygonsArea, _1, _2, argument)) / polygons.size() << std::endl;
        }
        else
        {
            throw I_C;
        }
    }
    else if (number > 2) //åñëè àðãóìåíò öèôðà
    {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            std::bind(accumulatePolygonsArea, _1, _2, "SPECIAL")) << std::endl;
    }
    else
    {
        throw I_C;
    }
}

// Ôóíêöèÿ ñðàâíåíèÿ, êîòîðàÿ âîçâðàùàåò true, åñëè ïåðâûé ïîëèãîí èìååò ìåíüøå âåðøèí, ÷åì âòîðîé
bool comparePolygonsByVerticesCount(const kuzn::Polygon& a, const kuzn::Polygon& b) {
    return a.points.size() < b.points.size();
}

//âû÷èñëåíèå ìèíèìàëüíîé ïëîùàäè/ðàçìåðà
void commands::getMin(const std::vector<kuzn::Polygon>& data)
{
    std::string arg;

    std::cin >> arg;

    if (data.size() == 0)
        throw I_C;

    if (arg == "AREA")
    {
        //ïîëèãîí ñ íàèìåíüøîé ïëîùàäüþ
        auto poly = std::min_element(data.begin(), data.end());
        std::cout << poly->getArea() << std::endl;
    }
    else if (arg == "VERTEXES")
    {
        //ïîëèãîí ñ íàèìåíüøèì êîë-âîì âåðøèí
        auto minSize = std::min_element(data.begin(), data.end(), comparePolygonsByVerticesCount);
        std::cout << minSize->points.size() << std::endl;
    }
    else
    {
        throw I_C;
    }
}

//âû÷èñëåíèå ìàêñèìàëüíîé ïëîùàäè/ðàçìåðà
void commands::getMax(const std::vector<kuzn::Polygon>& data)
{
    std::string arg;

    std::cin >> arg;

    if (data.size() == 0)
        throw I_C;

    std::vector<size_t> sizeVec(data.size());

    std::transform(data.begin(), data.end(), sizeVec.begin(),
        [](const Polygon& poly) { return poly.points.size(); }); //êîë-âî òî÷åê â ïîëèãîíå
    auto poly = std::max_element(data.begin(), data.end());
    auto maxSize = std::max_element(sizeVec.begin(), sizeVec.end()); //ìàêñèìóì òî÷åê ó ïîëèãîíà

    if (arg == "AREA")
        std::cout << poly->getArea() << std::endl;
    else if (arg == "VERTEXES")
        std::cout << *maxSize << std::endl;
    else
        throw I_C;
}

//âû÷èñëåíèå êîëè÷åñòâà ôèãóð â çàâèñèìîñòè îò àðãóìåíòà
void commands::countFigures(const std::vector<kuzn::Polygon>& polygons)
{
    std::string argument;
    std::cin >> argument;
    int number = convertToNumber(argument);

    //ïðîõîäèìñÿ ïî ïîëèãîíàì è óâåëè÷èâàåì ñ÷åò÷èê, åñëè èõ ðàçìåð ïîäõîäèò ïîä óñëîâèå
    auto count = [&number](const kuzn::Polygon& poly, const std::string& method)
        {
            if (method == "EVEN")
            {
                return poly.points.size() % 2 == 0;
            }
            else if (method == "ODD")
            {
                return poly.points.size() % 2 != 0;
            }
            else if (method == "SPECIAL")
            {
                return poly.points.size() == static_cast<size_t>(number);
            }
            return false;
        };

    if (number == -1)
    {
        if (argument == "EVEN" || argument == "ODD")
        {
            std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, argument)) << std::endl;
        }
        else
        {
            throw I_C;
        }
    }
    else if (number > 2)
    {
        std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, "SPECIAL")) << std::endl;
    }
    else
    {
        throw I_C;
    }
}

//êîë-âî ïîëèãîíîâ ñ ïëîùàäüþ ìåíüøå, ÷åì ó ïåðåäàííîãî ïîëèãîíà
void commands::lessarea(std::vector<kuzn::Polygon>& value)
{
    kuzn::Polygon mainEl, otherEl;
    std::cin >> mainEl; //îñíîâíîé ïîëèãîí

    if (!std::cin || std::cin.peek() != '\n')
    {
        throw I_C;
    }

    auto calcConcur = [&](const kuzn::Polygon tPolygon)
        {
            otherEl = tPolygon;
            bool rez = mainEl.getArea() > otherEl.getArea(); //ïîäñ÷¸ò ïîëèãîíîâ
            return rez;
        };
    std::cout << std::count_if(value.begin(), value.end(), calcConcur) << "\n";
}

//êîë-âî ïîëèãîíîâ, ñ êîòîðûìè ïåðåñåêàåòñÿ
void commands::intersections(const std::vector<kuzn::Polygon>& data)
{
    Polygon trg;

    std::cin >> trg;

    if (!std::cin || std::cin.peek() != '\n')
    {
        throw I_C;
    }
    // Èñïîëüçóåì std::bind äëÿ ñîçäàíèÿ îáúåêòà ôóíêöèè
    auto cntFunc = std::bind(&Polygon::isIntersect, _1, std::ref(trg));

    // Âûçûâàåì std::count_if ñ îáúåêòîì ôóíêöèè, ñîçäàííûì ñ ïîìîùüþ std::bind
    std::cout << std::count_if(data.begin(), data.end(), cntFunc) << std::endl;
}