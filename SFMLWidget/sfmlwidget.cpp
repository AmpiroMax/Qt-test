#include "sfmlwidget.h"
#include <math.h>

#include <QPainter>

SFMLWidget::SFMLWidget(QWidget *parent)
    : QWidget(parent),
      sf::RenderWindow(sf::VideoMode(0, 0), "Widgets layout test", sf::Style::Default, sf::ContextSettings(24)),
      shape(10),
      vLine(sf::Lines, 2),
      hLine(sf::Lines, 2)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    velocity = 5;
    dx = 0;
    dy = 0;

    isInited = false;
    timer.setInterval(20);
    clearColor = sf::Color(0, 0, 0);
}

QPaintEngine *SFMLWidget::paintEngine() const
{
    return nullptr;
}

void SFMLWidget::paintEvent(QPaintEvent *)
{
    clear(clearColor);

    draw(shape);
    draw(vLine);
    draw(hLine);

    display();

    //    QPen pen(Qt::black, 2, Qt::SolidLine);
    //    QPainter qp(this);
    //    qp.setPen(pen);
    //    qp.setPen(QColor("#d4d4d4"));
    //    qp.drawLine(20, 40, 250, 40);
}

void SFMLWidget::showEvent(QShowEvent *)
{
    if (isInited)
        return;

    RenderWindow::create(sf::WindowHandle(winId()));
    minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

    connect(&timer, &QTimer::timeout, this, &SFMLWidget::onTimeout);
    timer.start();

    printf("SFML win size %d, %d \n", RenderWindow::getSize().x, RenderWindow::getSize().y);
    printf("width, height = %d, %d \n", size().width(), size().height());

    vLine[0].position = sf::Vector2f(0, size().height() / 2);
    vLine[1].position = sf::Vector2f(size().width(), size().height() / 2);

    hLine[0].position = sf::Vector2f(size().width() / 2, 0);
    hLine[1].position = sf::Vector2f(size().width() / 2, size().height());

    shape.setPosition(size().width() / 2 - 10, size().height() / 2 - 10);
    view.setCenter(size().width() / 2, size().height() / 2);
    isInited = true;
}

void SFMLWidget::resizeEvent(QResizeEvent *)
{
    setSize(sf::Vector2u(size().width(), size().height()));
    repaint();
}

void SFMLWidget::mousePressEvent(QMouseEvent *event)
{
    dx = event->pos().x() - float(size().width()) / 2;
    dy = event->pos().y() - float(size().height()) / 2;

    printf("-------- \n dx, dy = %f, %f \n", dx, dy);
    float olddx = dx;
    dx = dx / sqrt(dx * dx + dy * dy);
    dy = dy / sqrt(olddx * olddx + dy * dy);

    printf("dx, dy = %f, %f \n", dx, dy);
}

void SFMLWidget::onTimeout()
{
    shape.move(dx * velocity, dy * velocity);
    view.move(dx * velocity, dy * velocity);
    setView(view);
    repaint();
}
