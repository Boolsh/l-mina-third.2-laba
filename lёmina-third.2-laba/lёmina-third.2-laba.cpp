//
//
//#include <iostream>
//#include <Windows.h>
//#include <fstream>
//#include <map>
//#include <vector>
//#include <string>
//
//using point = std::pair<int, int>;
//using points_arr = std::points_arr;
//
//
//points_arr get_dots(std::string filename)
//{
//    points_arr res{};
//    std::ifstream file(filename);
//    if (!file.is_open())
//    {
//        std::cerr << "File read error";
//    }
//    else
//    {
//        
//        int a, b;
//        while (file >> a and file >> b)
//            res.push_back({ a, b });
//    }
//    return res;
//
//}
//void print_arr(points_arr& arr)
//{
//    for (auto ptr : arr)
//        std::cout << ptr.first << "," << ptr.second << "; ";
//    std::cout << std::endl;
//        
//}
//float distance(point a, point b)
//{ return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));}
//
//
//// Функция вычисления периметра многоугольника
//float perimeter(points_arr& polygon) {
//    if (polygon.size() < 2) return 0.0f;
//
//    float p = 0.0f;
//    for (size_t i = 0; i < polygon.size(); ++i) {
//        size_t j = (i + 1) % polygon.size();
//        p += distance(polygon[i], polygon[j]);
//    }
//    return p;
//}
//
//// Функция проверки пересечения отрезков
//bool doIntersect(point p1, point q1, point p2, point q2) {
//    auto orientation = [](point p, point q, point r) {
//        int val = (q.second - p.second) * (r.first - q.first) -
//            (q.first - p.first) * (r.second - q.second);
//        if (val == 0) return 0;  // коллинеарны
//        return (val > 0) ? 1 : 2; // по или против часовой стрелки
//        };
//
//    auto onSegment = [](point p, point q, point r) {
//        return q.first <= max(p.first, r.first) &&
//            q.first >= min(p.first, r.first) &&
//            q.second <=max(p.second, r.second) &&
//            q.second >= min(p.second, r.second);
//        };
//
//    int o1 = orientation(p1, q1, p2);
//    int o2 = orientation(p1, q1, q2);
//    int o3 = orientation(p2, q2, p1);
//    int o4 = orientation(p2, q2, q1);
//
//    // Общий случай
//    if (o1 != o2 && o3 != o4)
//        return true;
//
//    // Специальные случаи
//    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
//    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
//    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
//    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
//
//    return false;
//}
//
//// Проверка на самопересечение многоугольника
//bool hasSelfIntersections(points_arr& polygon) {
//    if (polygon.size() < 4) return false;
//
//    for (size_t i = 0; i < polygon.size(); ++i) {
//        size_t next_i = (i + 1) % polygon.size();
//        for (size_t j = i + 2; j < polygon.size(); ++j) {
//            size_t next_j = (j + 1) % polygon.size();
//            // Пропускаем соседние ребра
//            if (next_i == j || next_j == i) continue;
//            if (doIntersect(polygon[i], polygon[next_i], polygon[j], polygon[next_j]))
//                return true;
//        }
//    }
//    return false;
//}
//
//// Рекурсивная функция для построения многоугольника с максимальным периметром
//void findMaxPerimeterPolygon(points_arr& points, points_arr& current, points_arr& result,
//    std::vector<bool>& used, float& max_perimeter) {
//    // Если текущий многоугольник валиден и имеет больший периметр, обновляем результат
//    if (current.size() >= 3 && !hasSelfIntersections(current)) {
//        float current_perimeter = perimeter(current);
//        if (current_perimeter > max_perimeter) {
//            max_perimeter = current_perimeter;
//            result = current;
//        }
//    }
//
//    // Перебираем все точки для добавления в многоугольник
//    for (size_t i = 0; i < points.size(); ++i) {
//        if (!used[i]) {
//            used[i] = true;
//            current.push_back(points[i]);
//
//            // Проверяем, не создали ли мы самопересечение
//            bool valid = true;
//            if (current.size() >= 4) {
//                size_t n = current.size();
//                // Проверяем последнее добавленное ребро на пересечение с другими
//                for (size_t j = 0; j < n - 3; ++j) {
//                    if (doIntersect(current[n - 2], current[n - 1], current[j], current[j + 1])) {
//                        valid = false;
//                        break;
//                    }
//                }
//            }
//
//            if (valid) {
//                findMaxPerimeterPolygon(points, current, result, used, max_perimeter);
//            }
//
//            current.pop_back();
//            used[i] = false;
//        }
//    }
//}
//
//// Основная функция для поиска многоугольника с максимальным периметром
//points_arr findMaxPerimeterPolygon(points_arr points) {
//    points_arr result;
//    float max_perimeter = 0.0f;
//
//    // Перебираем все возможные стартовые точки
//    for (size_t start = 0; start < points.size(); ++start) {
//        points_arr current;
//        std::vector<bool> used(points.size(), false);
//
//        used[start] = true;
//        current.push_back(points[start]);
//
//        findMaxPerimeterPolygon(points, current, result, used, max_perimeter);
//    }
//
//    return result;
//}
//
//int main() {
//    SetConsoleOutputCP(1251);
//    points_arr arr = get_dots("dots.txt");
//    std::cout << "Все точки: ";
//    print_arr(arr);
//
//    points_arr max_polygon = findMaxPerimeterPolygon(arr);
//    float p = perimeter(max_polygon);
//
//    std::cout << "Многоугольник с максимальным периметром: ";
//    print_arr(max_polygon);
//    std::cout << "Периметр: " << p << std::endl;
//
//    return 0;
//}
//

#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <algorithm>


struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

using points_arr = std::vector<Point>;

// Проверка с векторным произведением, лежат ли 3 точки на одной прямой
bool areCollinear(const Point& a, const Point& b, const Point& c) {
    return abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 1e-10;
}

// Проверка, лежат ли все точки текущего многоугольника на одной прямой
bool allCollinear(const points_arr& polygon) {
    if (polygon.size() < 3) return true;

    const Point& a = polygon[0];
    const Point& b = polygon[1];

    for (size_t i = 2; i < polygon.size(); ++i) {
        if (!areCollinear(a, b, polygon[i])) {
            return false;
        }
    }
    return true;
}

double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double perimeter(const points_arr& polygon) {
    double p = 0.0;
    for (size_t i = 0; i < polygon.size(); ++i) {
        p += distance(polygon[i], polygon[(i + 1) % polygon.size()]);
    }
    return p;
}

// Я 
bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) 
{
    auto orientation = [](const Point& p, const Point& q, const Point& r) //понимаем, как расположены три точки :по часовой стрелке, против или коллинеарно
        {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
        };

    auto onSegment = [](const Point& p, const Point& q, const Point& r) //лежит ли точка между двумя другими
        {
        return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
        };

    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    //Если ориентации разные - отрезки пересекаются
    //Если точки коллинеарны - проверяем перекрытие отрезков

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

bool isPolygonValid(const points_arr& polygon) {
    //проверяем, что больше 3 точек
    if (polygon.size() < 3) return false;
    if (allCollinear(polygon)) return false; // Отбрасываем коллинеарные точки


    // Проверка всех пар непоследовательных сторон
    for (size_t i = 0; i < polygon.size(); ++i) {
        for (size_t j = i + 2; j < polygon.size(); ++j) {
            size_t next_i = (i + 1) % polygon.size();
            size_t next_j = (j + 1) % polygon.size();

            // Пропускаем стороны-сомседи
            if (next_i == j || next_j == i) continue;

            if (doIntersect(polygon[i], polygon[next_i], polygon[j], polygon[next_j])) {
                return false;
            }
        }
    }
    return true;
}

void backtrack(const points_arr& points, points_arr& current,std::vector<bool>& used, double& max_perimeter,points_arr& best_polygon) 
{
    // Проверяем текущий многоугольник
    if (current.size() >= 3 && isPolygonValid(current)) {
        double current_perimeter = perimeter(current);
        if (current_perimeter > max_perimeter) {
            max_perimeter = current_perimeter;
            best_polygon = current;
        }
    }

    // Перебираем все точки
    for (size_t i = 0; i < points.size(); ++i) {
        if (!used[i]) {
            // Пропускаем точки, которые делают все точки коллинеарными
            if (current.size() >= 2)
            {
                bool allCol = true;
                for (size_t j = 0; j < current.size(); ++j) {
                    if (!areCollinear(current[j], current.back(), points[i])) {
                        allCol = false;
                        break;
                    }
                }
                if (allCol) continue;
            }

            used[i] = true;
            current.push_back(points[i]);

            backtrack(points, current, used, max_perimeter, best_polygon);

            current.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);

    std::ifstream input("dots.txt");
    points_arr points;

    double x, y;

    while (input >> x >> y) {
        points.emplace_back(x, y);
    }

    if (points.size() < 3) {
        std::cout << "Недостаточно точек (минимум 3)" << std::endl;
        return 0;
    }

    points_arr current_polygon, best_polygon;
    std::vector<bool> used(points.size(), false);
    double max_perimeter = 0;

    backtrack(points, current_polygon, used, max_perimeter, best_polygon);

    if (best_polygon.empty()) {
        std::cout << "Нельзя построить многоугольник :(" << std::endl;
    }
    else {
        std::cout << "Многоугольник с максимальным периметром (" << max_perimeter << "):" << std::endl;
        for (const auto& p : best_polygon)
            std::cout << "(" << p.x << ", " << p.y << ") ";

    }

    return 0;
}