#include "GlobalWidget/globalwidget.h"
#include "SFMLWidget/sfmlwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlobalWidget widget;
    widget.show();

    return a.exec();
}
