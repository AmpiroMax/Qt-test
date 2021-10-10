#include "globalwidget.h"
#include <QApplication>
#include <QDesktopWidget>

GlobalWidget::GlobalWidget(QWidget *parent) : QWidget(parent)
{
    QRect rec = QApplication::desktop()->screenGeometry();

    int height = rec.height() / 2;
    int width = rec.width() / 2;
    resize(width, height);

    sfmlWidget1 = new SFMLWidget(this);
    sfmlWidget1->setGeometry(0, 0, width, height);

    grid = new QGridLayout(this);
    grid->addWidget(sfmlWidget1);
    printf("Global W, H = %d, %d", width, height);
}
