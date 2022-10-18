#ifndef COMPARISONWIDGET_H
#define COMPARISONWIDGET_H

#include <QWidget>

namespace Ui {
class ComparisonWidget;
}

class ComparisonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComparisonWidget(QWidget *parent = nullptr);
    ~ComparisonWidget();

private:
    Ui::ComparisonWidget *ui;
};

#endif // COMPARISONWIDGET_H
