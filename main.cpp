#include "GlobalWidget/globalwidget.h"
#include "SFMLWidget/sfmlwidget.h"
#include "mainwindow.h"
#include <QApplication>
#include <ui_form.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlobalWidget widget;
    widget.show();

    Ui::MainWindow ui;
    ui.setupUi(&widget);

    return a.exec();
}
