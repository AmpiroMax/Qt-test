#include "globalwidget.h"
#include <QApplication>
#include <QDesktopWidget>

GlobalWidget::GlobalWidget(QWidget *parent) : QWidget(parent)
{
    // Получаем размеры экрана устройства
    QRect rec = QApplication::desktop()->screenGeometry();

    // Задаю размеры глобального виджета, как 1/2 и 1/2
    // от размеров всего экрана
    int height = rec.height() / 2;
    int width = rec.width() / 2;
    resize(width, height);

    // Создаю виджет с SFML и задаю ему его размеры
    sfmlWidget1 = new SFMLWidget(this);

    // Добавляю SFML виджет в QGridLayout, для корректного
    // изменения его размеров, при изменении размеров всего окна
    grid = new QGridLayout(this);
    grid->addWidget(sfmlWidget1);
}
