#ifndef SFMLWIDGET_H
#define SFMLWIDGET_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QWidget>

class SFMLWidget : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
  private:
    sf::Color clearColor;
    sf::View view;
    sf::View minimapView;
    sf::VertexArray vLine;
    sf::VertexArray hLine;
    sf::CircleShape circle;
    QTimer timer;

    bool isInited;
    float velocity;
    float dx;
    float dy;

  public:
    explicit SFMLWidget(QWidget *parent = nullptr);

  private:
    virtual QPaintEngine *paintEngine() const override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void resizeEvent(QResizeEvent *) override;

    virtual void mouseMoveEvent(QMouseEvent *) override;

  private slots:
    void onTimeout();
};

#endif // SFMLWIDGET_H
