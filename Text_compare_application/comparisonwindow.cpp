#include "comparisonwindow.h"
#include "ui_comparisonwindow.h"
//#include "mainwindow.h"


ComparisonWindow::ComparisonWindow(QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::ComparisonWindow)
{
    ui->setupUi(this);
}

/*!
 * \brief ComparisonWindow::ComparisonWindow ctor, initialize the comparison widget
 * \param filePath1 the path to the first file from which we will read the content
 * \param filePath2 the path to the second file from which we will read the content
 * \param parent parent widget, extend MainWindow
 *
 * create and initialize new window,
 * gets file addresses, reads their contents and places them in QTextEdit's, runs An O(ND) Difference Algorithm and Its Variations
 *
 */
ComparisonWindow::ComparisonWindow(QString filePath1, QString filePath2, QWidget *parent) :
    MainWindow(parent),
    ui(new Ui::ComparisonWindow)
{
    ui->setupUi(this);

    this->filePath1 = filePath1;
    this->filePath2 = filePath2;

    QString fileContent1 = FileWorker::readTextFile(this->filePath1);
    ui->textEdit1->setPlainText(fileContent1);
    QString fileContent2 = FileWorker::readTextFile(this->filePath2);
    //ui->textEdit2->setPlainText(fileContent2);


    std::string str1 = fileContent1.toStdString();
    std::string str2 = fileContent2.toStdString();

    std::string content = "";

    /*PROBABLY WILL BE ERROR*/
    V::MyersDiff(fileContent1.toStdString().c_str(), sizeof(std::string) * str1.length() / sizeof(std::string) - 1,
                 fileContent2.toStdString().c_str(), sizeof(std::string) * str2.length() / sizeof(std::string) - 1);
    V::SES(fileContent1.toStdString().c_str(), sizeof(std::string) * str1.length() / sizeof(std::string) - 1,
        fileContent2.toStdString().c_str(), sizeof(std::string) * str2.length() / sizeof(std::string) - 1, &content);

    content += '\n';
    ui->textEdit2->setPlainText(QString::fromStdString(content)+fileContent2);

    /*
    // this is a struct which keeps information about each difference in text which should be highlighted
    struct DiffEntry
    {
      int pos = -1;
      int length = -1;
      QColor background;
      QColor foreground;
    };

    // and this is the code which does the actual formatting

    QList<QTextEdit::ExtraSelection> extraSelections;

    for (auto diffEntry : diffEntries)
    {
      QTextCursor textCursor = QTextCursor(textEdit->document());
      textCursor.setPosition(diffEntry.pos);
      textCursor.setPosition(diffEntry.pos + diffEntry.length, QTextCursor::KeepAnchor);
      auto extraSelection = QTextEdit::ExtraSelection();
      extraSelection.cursor = textCursor;
      extraSelection.format.setBackground( diffEntry.background );
      extraSelection.format.setForeground( diffEntry.foreground );
      extraSelections.append( extraSelection );
    }

    textEdit->setExtraSelections(extraSelections);
    */
}

ComparisonWindow::~ComparisonWindow()
{
    delete ui;
}

/*!
 * \brief changes the color of the text
 *
 * calls the QColorDialog dialog box that allows you to select a color
 * of the text in QTextEdit
 */
void ComparisonWindow::on_actionColor_triggered()
{
    QPalette palette1 = ui->textEdit1->palette();
    QColor color1 = palette1.color(QPalette::WindowText);

    QColor chosenColor = QColorDialog::getColor(color1, this, "Choose text color");

    if(chosenColor.isValid())
    {
        ui->textEdit1->setTextColor(chosenColor);
        QString str1 = ui->textEdit1->toPlainText();
        ui->textEdit1->clear();
        ui->textEdit1->insertPlainText(str1);

        ui->textEdit2->setTextColor(chosenColor);
        QString str2 = ui->textEdit2->toPlainText();
        ui->textEdit2->clear();
        ui->textEdit2->insertPlainText(str2);
    }
    else
    {
        qDebug() << "User chose invalid color";
    }
}

/*!
 * \brief changes text style of the text
 *
 * calls the QFontDialog dialog box that allows you to select a font
 * of the text in QTextEdit
 */
void ComparisonWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx", 10), this);
    if (ok)
    {
        ui->textEdit1->setFont(font);
        ui->textEdit2->setFont(font);
    }
    else
    {
        qDebug() << "User didn't choose color";
    }

}


void ComparisonWindow::on_actionName_triggered()
{

}



