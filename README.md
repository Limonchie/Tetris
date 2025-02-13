# Tetris
1. Общее описание
Это реализация классической игры "Тетрис" на языке программирования C++ с использованием графической библиотеки SFML. В игре присутствуют основные механики:

Падение фигур (тетромино).
Управление движением фигур (влево, вправо, ускоренное падение).
Вращение фигур.
Очистка заполненных строк.
Система очков и уровней сложности.
Главное меню и возможность паузы.
2. Структура проекта
Файлы проекта:
Main.cpp: Точка входа в программу. Создаёт окно игры, игровое поле и запускает игровой цикл.
GameField.h, GameField.cpp: Класс для управления игровым полем.
Tetramino.h, Tetramino.cpp: Класс для управления фигурами (тетромино).
GameController.h, GameController.cpp: Класс для управления логикой игры.
Score.h, Score.cpp: Класс для отслеживания счёта, уровня и удалённых строк.
MainMenu.h, MainMenu.cpp: Класс для реализации главного меню.
PauseMenu.h, PauseMenu.cpp: Класс для реализации меню паузы.
3. Классы и их описание
3.1. GameField
Класс, представляющий игровое поле.

Поля:
width: Ширина поля.
height: Высота поля.
tileSize: Размер плитки.
field: Матрица, представляющая состояние игрового поля.
Методы:
GameField(int width, int height, int tileSize): Конструктор, инициализирующий игровое поле.
void draw(RenderWindow& window) const: Рисует игровое поле.
bool checkCollision(const Tetramino& tetramino, int x, int y) const: Проверяет столкновение фигуры с границами поля или другими блоками.
void lockTetramino(const Tetramino& tetramino, int x, int y): Фиксирует фигуру на игровом поле.
int clearLines(): Очищает полностью заполненные строки и возвращает количество удалённых строк.
3.2. Tetramino
Класс, представляющий фигуру (тетромино).

Поля:
shape: Матрица, описывающая форму фигуры.
color: Цвет фигуры.
rotationCount: Счётчик вращений (максимум 3 раза за один ход).
previousShape: Предыдущая форма фигуры для отмены вращения.
Методы:
Tetramino(const vector<vector<int>>& shape, sf::Color color): Конструктор, инициализирующий форму и цвет фигуры.
void rotate(): Вращает фигуру против часовой стрелки.
void undoRotation(): Отменяет последнее вращение.
const vector<vector<int>>& getShape() const: Возвращает текущую форму фигуры.
sf::Color getColor() const: Возвращает цвет фигуры.
int getRotationCount() const: Возвращает количество выполненных вращений.
3.3. GameController
Класс, контролирующий основную логику игры.

Поля:
field: Ссылка на объект класса GameField.
window: Ссылка на окно SFML.
currentTetramino: Текущая фигура на игровом поле.
tetraminoX, tetraminoY: Координаты текущей фигуры.
score: Объект класса Score для отслеживания счёта.
fallSpeed: Скорость падения фигур.
Методы:
GameController(GameField& field, RenderWindow& window): Конструктор, инициализирующий игру.
void run(): Запускает основной игровой цикл.
void spawnTetramino(): Создаёт новую случайную фигуру.
void moveTetramino(int dx, int dy): Перемещает фигуру по горизонтали (dx) и вертикали (dy).
void handleInput(): Обрабатывает пользовательский ввод (движение, вращение, ускорение падения).
void updateUI(): Обновляет интерфейс (рисует поле, фигуру, счёт и уровень).
void gameOver(): Отображает сообщение "Game Over" и завершает игру.
3.4. Score
Класс для отслеживания счёта, уровня и удалённых строк.

Поля:
score: Текущий счёт игрока.
level: Текущий уровень сложности.
linesCleared: Количество удалённых строк.
Методы:
Score(): Конструктор, инициализирующий счёт, уровень и количество строк.
void addLines(int lines): Добавляет очки за удалённые строки и обновляет уровень.
void updateLevel(): Обновляет уровень сложности на основе счёта.
int getScore() const: Возвращает текущий счёт.
int getLevel() const: Возвращает текущий уровень.
int getLinesCleared() const: Возвращает количество удалённых строк.
void draw(RenderWindow& window, int fieldHeight, int tileSize) const: Рисует информацию о счёте, уровне и удалённых строках.
3.5. MainMenu
Класс для реализации главного меню.

Методы:
MainMenu(RenderWindow& window): Конструктор, принимающий ссылку на окно.
void show(): Отображает главное меню и ждёт нажатия клавиши Space для начала игры.
3.6. PauseMenu
Класс для реализации меню паузы.

Поля:
selectedOption: Индекс выбранного пункта меню.
options: Вектор текстовых элементов (пункты меню).
Методы:
PauseMenu(RenderWindow& window): Конструктор, создающий меню с пунктами "Продолжить" и "Выйти".
void show(): Отображает меню паузы и ждёт выбора пользователя.
int getChoice() const: Возвращает выбранный пункт меню (0 — продолжить, 1 — выйти).
4. Логика работы
4.1. Главный цикл игры
Основной цикл игры находится в методе run() класса GameController. Он включает следующие этапы:

Обработка событий: Проверка нажатий клавиш (Left, Right, Down, Up, Escape).
Обновление состояния: Перемещение и вращение фигуры, проверка столкновений.
Отрисовка: Рисование игрового поля, текущей фигуры, счёта и уровня.
4.2. Управление фигурой
Движение влево/вправо: Фигура двигается через определённые интервалы времени (задержка moveDelay).
Ускоренное падение: При нажатии клавиши Down скорость падения увеличивается.
Вращение: Фигура вращается при нажатии клавиши Up с задержкой (rotateDelay).
4.3. Очистка строк
Когда строка полностью заполнена, она удаляется, а остальные строки опускаются вниз. За каждую удалённую строку начисляются очки.

4.4. Уровни сложности
Скорость падения фигур увеличивается с каждым уровнем. Уровень рассчитывается как (score / 1000) + 1.

5. Управление
Клавиша Left: Двигает фигуру влево.
Клавиша Right: Двигает фигуру вправо.
Клавиша Down: Ускоряет падение фигуры.
Клавиша Up: Вращает фигуру.
Клавиша Escape: Открывает меню паузы.
Клавиша Space (в главном меню): Начинает игру.
Клавиша R (в меню "Game Over"): Перезапускает игру.
6. Графика
6.1. Отрисовка игрового поля
Игровое поле рисуется с помощью класса GameField. Каждая ячейка представляет собой прямоугольник размером tileSize x tileSize. Занятые ячейки окрашиваются в цвет Cyan, а свободные — в цвет Black.

6.2. Отрисовка фигуры
Текущая фигура рисуется поверх игрового поля. Каждый блок фигуры имеет свой цвет, который определяется при её создании.

6.3. Текстовая информация
Информация о счёте, уровне и удалённых строках отображается в нижней части экрана с помощью класса Score.

7. Настройка проекта
7.1. Библиотеки
SFML: Необходима для работы с графикой, вводом и таймерами. Установите через NuGet:
bash
Копировать
1
Install-Package sfml
Шрифт: Для отображения текста используется шрифт "Times New Roman". Если вы хотите избежать внешних файлов, можно использовать встроенный массив данных шрифта.
7.2. Компиляция
Создайте проект в Visual Studio.
Добавьте все .cpp файлы (Main.cpp, GameField.cpp, Tetramino.cpp, GameController.cpp, Score.cpp, MainMenu.cpp, PauseMenu.cpp).
Убедитесь, что пути к заголовочным файлам и библиотекам SFML правильно настроены.
8. Возможные доработки
Добавление звука: Используйте модуль sf::Sound для добавления звуковых эффектов.
Графическое оформление: Добавьте фоновое изображение и более красивое оформление меню.
Различные режимы игры: Реализуйте режимы с различными правилами (например, "Без ограничения времени" или "С ограниченным временем").
Таблица рекордов: Сохраняйте лучшие результаты в файл.
9. Пример использования
9.1. Запуск игры
cpp
#include "GameField.h"
#include "GameController.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(450, 650), "Tetris");
    GameField field(15, 20, 30); // Ширина 15, высота 20, размер плитки 30px
    MainMenu menu(window);

    menu.show(); // Показываем главное меню

    GameController controller(field, window);
    controller.run(); // Запускаем игру

    return 0;
}
9.2. Главное меню
cpp
class MainMenu {
public:
    MainMenu(RenderWindow& window) : window(window) {}

    void show() {
        Font font;
        if (!font.loadFromFile("Times New Roman - Italic.ttf")) {
            cout << "Failed to load font!" << endl;
            return;
        }

        Text title("Тетрис", font, 60);
        title.setFillColor(Color::White);
        title.setPosition(100, 100);

        Text startText("Нажмите пробел для начала игры", font, 30);
        startText.setFillColor(Color::Green);
        startText.setPosition(100, 300);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                    return; // Начинаем игру
                }
            }

            window.clear();
            window.draw(title);
            window.draw(startText);
            window.display();
        }
    }

private:
    RenderWindow& window;
};
9.3. Меню паузы
cpp
class PauseMenu {
public:
    PauseMenu(RenderWindow& window) : window(window) {}

    void show() {
        Font font;
        if (!font.loadFromFile("Times New Roman - Italic.ttf")) {
            cout << "Failed to load font!" << endl;
            return;
        }

        Text title("Пауза", font, 40);
        title.setFillColor(Color::Yellow);
        title.setPosition(150, 150);

        Text continueText("Продолжить", font, 30);
        continueText.setFillColor(Color::White);
        continueText.setPosition(150, 250);

        Text exitText("Выйти", font, 30);
        exitText.setFillColor(Color::White);
        exitText.setPosition(150, 300);

        int selectedOption = 0;

        while (true) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Up) {
                        selectedOption = max(0, selectedOption - 1);
                    } else if (event.key.code == Keyboard::Down) {
                        selectedOption = min(1, selectedOption + 1);
                    } else if (event.key.code == Keyboard::Enter) {
                        return selectedOption; // Возвращаем выбранную опцию
                    } else if (event.key.code == Keyboard::Escape) {
                        return -1; // Отмена паузы
                    }
                }
            }

            window.clear(Color::Black);

            if (selectedOption == 0) {
                continueText.setFillColor(Color::Green);
                exitText.setFillColor(Color::White);
            } else {
                continueText.setFillColor(Color::White);
                exitText.setFillColor(Color::Green);
            }

            window.draw(title);
            window.draw(continueText);
            window.draw(exitText);
            window.display();
        }
    }

private:
    RenderWindow& window;
};
10. Зависимости
SFML: Версия 2.5.1 или выше.
C++ Standard Library: Используется для работы с векторами, случайными числами и таймерами.
11. Авторские права
Шрифт "Times New Roman" является стандартным шрифтом Windows. Если вы используете его в коммерческих целях, убедитесь, что это допустимо согласно лицензии.

12. Заключение
Проект демонстрирует использование принципов объектно-ориентированного программирования (ООП) для создания игры "Тетрис". Каждый класс отвечает за свою конкретную задачу, что делает код читаемым и легко поддерживаемым.
