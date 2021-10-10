#include "sfmlwidget.h"
#include <math.h>

#include <QPainter>

constexpr int circleRadius = 10;

SFMLWidget::SFMLWidget(QWidget *parent)
    : QWidget(parent),
      sf::RenderWindow(sf::VideoMode(0, 0), "Widgets layout test", sf::Style::Default, sf::ContextSettings(24)),
      circle(circleRadius),
      vLine(sf::Lines, 2),
      hLine(sf::Lines, 2)
{
    // Отрибуты, необходимые для правильного отображения и использования
    // SFML в QWidget. Для чего необходимо каждое из них, написано в
    // документации Qt. Возможно в будующем я поясню для чего каждый
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Устанавливаю изначальную скорость
    // и начальные перемещения
    velocity = 5;
    dx = 0;
    dy = 0;

    isInited = false;
    timer.setInterval(20);
    clearColor = sf::Color(0, 0, 0);
}

QPaintEngine *SFMLWidget::paintEngine() const
{
    // В силу того, что мы рисуем в окне через SFML, были установлены
    // определенные отрибуты. Один из них требует установить возвращаемым
    // значением в данной функции nullptr, чтобы в случае, если кто-то захочет
    // что-то рисовать через Qt, у него это не получччилось, т.к. такой
    // возможности здесь неподразумевается
    return nullptr;
}

void SFMLWidget::paintEvent(QPaintEvent *)
{
    // Очишаем экран
    clear(clearColor);

    // Отрисовываем необходимые объекты
    draw(circle);
    draw(vLine);
    draw(hLine);

    // Отображаем всё в окне
    display();
}

void SFMLWidget::showEvent(QShowEvent *)
{
    // Проделываем данные операции только один раз,
    // когда наше окно было впервые отображено на экране
    if (isInited)
        return;

    // Создаю SFML окно, но не новое, а передаю контроль ему над
    // уже созданым QWidget, в котором и будет происходить отрисовка
    RenderWindow::create(sf::WindowHandle(winId()));

    // Соединяю сигнал таймера со слотом этого виджета.
    // Запускаю таймер
    connect(&timer, &QTimer::timeout, this, &SFMLWidget::onTimeout);
    timer.start();

    // Две _|_ линни, просто для ориентации шарика в пространстве
    // Мне нужно было что-то, относительно чего будет шарик двигаться
    vLine[0].position = sf::Vector2f(0, size().height() / 2);
    vLine[1].position = sf::Vector2f(size().width(), size().height() / 2);

    hLine[0].position = sf::Vector2f(size().width() / 2, 0);
    hLine[1].position = sf::Vector2f(size().width() / 2, size().height());

    // Устанавливаем позицию шарика, которым "условно" мы управляем
    // Также устанавливаем его центр координат (origin)
    circle.setOrigin(circleRadius, circleRadius);
    circle.setPosition(size().width() / 2, size().height() / 2);

    // Изначальные настройки положения камеры
    view.setCenter(size().width() / 2, size().height() / 2);
    view.setSize(size().width(), size().height());

    isInited = true;
}

void SFMLWidget::resizeEvent(QResizeEvent *)
{
    // В случае изменения размера виджета, необходимо поменять
    // размер и SFML RenderWindow окну, для правильного отображения
    // Также после смены размера, необходимо поставить центр обзора (view)
    // на новое положение
    setSize(sf::Vector2u(size().width(), size().height()));
    view.setSize(size().width(), size().height());
    repaint();
}

void SFMLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Обновленик вектора передвижения
    // Начальная точка - центр окна
    // Конечная точка - положение курсора
    dx = event->pos().x() - float(size().width()) / 2;
    dy = event->pos().y() - float(size().height()) / 2;

    // В случае, если dx или dy меньше epsilon,
    // то можно считать их достаточно малымми и обнулить
    // Это решает проблему деления на 0

    // Задал epsilon равным радиусу шарика, чтоб при нажатии на него
    // можно было остановаться
    float epsilon = circleRadius;
    if (abs(dx) < epsilon)
        dx = 0;
    if (abs(dy) < epsilon)
        dy = 0;

    // Получаю вектор единичной длины
    float olddx = dx;
    if (dx != 0 || dy != 0)
    {
        dx = dx / sqrt(dx * dx + dy * dy);
        dy = dy / sqrt(olddx * olddx + dy * dy);
    }
}

void SFMLWidget::onTimeout()
{
    // Раз в определенное время (оно задано в конструкторе)
    // обновляю экран, передвигая и по новой отрисовывая объекты
    circle.move(dx * velocity, dy * velocity);
    view.move(dx * velocity, dy * velocity);
    setView(view);

    repaint();
}
