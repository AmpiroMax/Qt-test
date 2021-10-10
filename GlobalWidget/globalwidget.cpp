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
}
