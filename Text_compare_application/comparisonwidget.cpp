#include "comparisonwidget.h"
#include "ui_comparisonwidget.h"

ComparisonWidget::ComparisonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComparisonWidget)
{
    ui->setupUi(this);
}

ComparisonWidget::~ComparisonWidget()
{
    delete ui;
}
