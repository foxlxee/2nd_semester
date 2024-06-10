#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

// Число пи это обратный косинус от -1
const double PI = acos(-1);

class KinematicSolver {
private:
    double m_alpha; // Угол alpha
    double m_beta;  // Угол beta
    double m_L1; // Длина звена L1
    double m_L2; // Длина звена L2
public:
    // Длины L1 и L2 задаются в конструкторе
    KinematicSolver(double L1, double L2) : m_L1(L1), m_L2(L2), m_alpha(0.0), m_beta(0.0) {}

    // Метод, который вычисляет углы alpha и beta
    void Solve(double x, double y) {
        // Проведём прямую B, соединяющую начало координат O с заданной точкой (x, y)
        // По теормере Пифагора длина отрезка B равна корню из суммы квадратов координат
        double B = sqrt(x * x + y * y);

        // Выходим из метода если точка недоступна
        if (!(B < m_L1 + m_L2 && x > 0 && y > 0)) {
            return;
        }

        // Обозначим Q1 угол между осью OX и прямой B, а Q2 угол между прямой B и звеном L1
        // Обозначим Q2 угол между прямой B и плечом L1
        
        // Найдем Q1 через обратный тангенс y/x
        double Q1 = std::atan(y / x);

        // Найдем Q2 при помощи теоремы косинусов
        double Q2 = std::acos((m_L1 * m_L1 - m_L2 * m_L2 + B * B) / (2.0 * B * m_L1));

        // Найдём alpha
        m_alpha = Q1 - Q2;

        // Найдём beta при помощи теоремы косинусов
        m_beta = PI - std::acos(
            (m_L1 * m_L1 + m_L2 * m_L2 - B * B) /
            (2 * m_L1 * m_L2));
    }

    // Метод, который возвращает длину L1
    double L1() {
        return m_L1;
    }

    // Метод, который возвращает длину L2
    double L2() {
        return m_L2;
    }

    // Метод, который возвращает угол alpha в радианах
    double alpha() const {
        return m_alpha;
    }

    // Метод, который возвращает угол beta в радианах
    double beta() const {
        return m_beta;
    }
};

// Класс, который хранит координаты точки и имеет статический метод для поворота
class Point {
private:
    float m_x;
    float m_y;
public:
    Point(float x, float y) : m_x(x), m_y(y) { }

    float x() const {
        return m_x;
    }

    float y() const {
        return m_y;
    }

    static Point rotate(float cx, float cy, float angle, Point p) {
        float s = sin(angle);
        float c = cos(angle);

        p.m_x -= cx;
        p.m_y -= cy;

        float xnew = p.m_x * c - p.m_y * s;
        float ynew = p.m_x * s + p.m_y * c;

        p.m_x = xnew + cx;
        p.m_y = ynew + cy;

        return p;
    }
};

// Класс, который содержит информацию о звене и имеет методы для
// изменения поворота, позиции и рисования в окне
class Link {
private:
    sf::RectangleShape m_rectangleShape;
public:
    // Конструктор, который принимает длину, позицию и поворот в градусах
    Link(float length, Point position, float initialRotation) {
        m_rectangleShape.setSize(sf::Vector2f(length, 10));
        m_rectangleShape.setOrigin(0, 0.5);
        m_rectangleShape.setPosition(position.x(), position.y());
        m_rectangleShape.setFillColor(sf::Color(40, 40, 40));
        m_rectangleShape.rotate(initialRotation);
    }

    void move(Point position) {
        m_rectangleShape.setPosition(position.x() - 5, position.y() + 5);
    }

    void rotate(float angle) {
        m_rectangleShape.setRotation(angle);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_rectangleShape);
    }
};

// Класс, который содержит информацию о шарнире между L1 и L2
class Joint {
private:
    sf::CircleShape m_circle;
public:
    Joint() {
        m_circle.setRadius(15);
        m_circle.setFillColor(sf::Color::Black);
        m_circle.setPointCount(100);
    }

    void move(Point position) {
        float radius = m_circle.getRadius();
        m_circle.setPosition(position.x() - radius, position.y() - radius);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(m_circle);
    }
};

// Функция, которая переводит радианы в градусы
double radiansToDegrees(double radians) {
    return radians * (180.0 / PI);
}

int main() {
    // Создаём экзепляр класса KinematicSolver и передаём размеры звеньев L1 и L2 в конструктор
    KinematicSolver kinematicSolver(350, 350);

    // Создаём экземпляр главного окна
    sf::RenderWindow mainWindow(
        sf::VideoMode(800, 600),
        "Inverse Kinematics",
        sf::Style::Close);
    mainWindow.setFramerateLimit(60);

    // Создаём экземпляры звеньев L1 и L2
    Link L1(kinematicSolver.L1(), Point(0.0, 600.0), 0.0);
    Link L2(kinematicSolver.L2(), Point(kinematicSolver.L1(), 600.0), 0.0);

    // Создаём экземпляр шарнира
    Joint joint;

    // Запускаем главный цикл
    // В условии при нажатии клавиши ESCAPE выходим из цикла
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }
        }

        if (!mainWindow.isOpen()) {
            break;
        }

        mainWindow.clear(sf::Color::White);

        // Двигаемся к локальной позиции курсора в окне
        // Получаем координаты курсора
        sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(mainWindow);

        // Вычитаем из высоты окна позицию по y, потому что у нас координаты растут снизу вверх
        mouseLocalPosition.y = 600.0 - mouseLocalPosition.y;

        // Передаём координаты в экземпляр класса KinematicSolver
        kinematicSolver.Solve(mouseLocalPosition.x, mouseLocalPosition.y);

        // Умножаем на -1 чтобы поворот был против часовой стрелки
        float alpha = kinematicSolver.alpha() * -1;
        float beta = kinematicSolver.beta() * -1;

        // Вращаем L1
        L1.rotate(radiansToDegrees(alpha));

        // Вычисляем новую позицию и поворот L2 
        Point L2_position = Point::rotate(0, 600.0, alpha, Point(kinematicSolver.L1(), 600.0));
        L2.move(L2_position);
        L2.rotate(radiansToDegrees(alpha + beta));

        // Рисуем L1 и L2
        L1.draw(mainWindow);
        L2.draw(mainWindow);

        // Рисуем шарнир
        joint.move(L2_position);
        joint.draw(mainWindow);

        mainWindow.display();
    }
}