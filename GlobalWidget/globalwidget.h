#ifndef GLOBALWIDGET_H
#define GLOBALWIDGET_H

#include "SFMLWidget/sfmlwidget.h"
#include <QGridLayout>
#include <QWidget>

class GlobalWidget : public QWidget
{
    Q_OBJECT
  private:
    SFMLWidget *sfmlWidget1;

    QGridLayout *grid;

  public:
    explicit GlobalWidget(QWidget *parent = nullptr);
};

#endif // GLOBALWIDGET_H
