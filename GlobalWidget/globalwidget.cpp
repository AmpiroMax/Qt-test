#include "globalwidget.h"
#include <QApplication>
#include <QDesktopWidget>

GlobalWidget::GlobalWidget(QWidget *parent) : QWidget(parent)
{
    QRect rec = QApplication::desktop()->screenGeometry();
    printf("%d, %d \n", rec.width(), rec.height());

    int height = rec.height() / 2;
    int width = rec.width() / 2;
    resize(width, height);

    // grid = new QGridLayout(this);
    sfmlWidget1 = new SFMLWidget(this);
    sfmlWidget1->setGeometry(0, 0, width, height);
    // grid->addWidget(sfmlWidget1, 0, 0);
    // grid->setSpacing(0);
}
