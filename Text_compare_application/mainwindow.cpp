#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "comparisonwindow.h"

/*!
 * \brief MainWindow::MainWindow initialize the main window
 * \param parent parent widget, extend QMainWindow
 *
 * responsible for the operation of the window that opens when the program is launched
 * saves and loads the program theme
 *
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QString css = FileWorker::readTextFile(":/styles/King Yna.qss");
  if (css.length() > 0) {
    this->setStyleSheet(css);
  }

  loadSettings();
}

MainWindow::~MainWindow() { delete ui; }

/*!
 * \brief changes the theme of the program to King Yna
 */
void MainWindow::on_actionKing_Yna_triggered()
{
    QString css = FileWorker::readTextFile(":/styles/King Yna.qss");
    if (css.length() > 0) {
      this->setStyleSheet(css);
    }
    saveSettings();
}

/*!
 * \brief changes the theme of the program to Deep Space
 */
void MainWindow::on_actionDeep_Space_triggered()
{
    QString css = FileWorker::readTextFile(":/styles/Deep Space.qss");
    if (css.length() > 0) {
      this->setStyleSheet(css);
    }
    saveSettings();
}

/*!
 * \brief changes the theme of the program to Ukraine
 */
void MainWindow::on_actionUkraine_triggered()
{
    QString css = FileWorker::readTextFile(":/styles/Ukraine.qss");
    if (css.length() > 0) {
      this->setStyleSheet(css);
    }
    saveSettings();
}

/*!
 * \brief starts the file comparison process
 *
 * reads file addresses and passes them as parameters to ComparisonWindow
 */
void MainWindow::on_compareButton_clicked()
{

    ComparisonWindow *window = new ComparisonWindow(ui->lineEdit->text(), ui->lineEdit_2->text(), this);
    //ComparisonWindow *window = new ComparisonWindow(this);
    window->show();

}

/*!
 * \brief saves application settings
 *
 * saves the program theme to QSettings file
 */
void MainWindow::saveSettings()
{
    QSettings setting("MyOrganization", "MyApplication");
    setting.beginGroup("MainWindow");
    setting.setValue("theme", this->styleSheet());
    setting.endGroup();
}

/*!
 * \brief load application settings
 *
 * load and apply the program theme from QSettings file
 */
void MainWindow::loadSettings()
{
    QSettings setting("MyOrganization", "MyApplication");
    setting.beginGroup("MainWindow");
    QString style = setting.value("theme").toString();
    this->setStyleSheet(style);
}


/*!
 * \brief button to read first file
 */
void MainWindow::on_chooseFileButton1_clicked()
{
    //QString fileContent;
    //Save the file to disk
    QString filename = QFileDialog::getOpenFileName(this, "Open File");

    if(filename.isEmpty())
        return;

    /*QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull())
    {
        fileContent.append(line);
        line = in.readLine();
    }

    file.close();*/

    ui->lineEdit->clear();
    ui->lineEdit->setText(filename);
}

/*!
 * \brief button to read second file
 */
void MainWindow::on_chooseFileButton2_clicked()
{
    //QString fileContent;
    //Save the file to disk
    QString filename = QFileDialog::getOpenFileName(this, "Open File");

    if(filename.isEmpty())
        return;

    /*QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull())
    {
        fileContent.append(line);
        line = in.readLine();
    }

    file.close();*/

    ui->lineEdit_2->clear();
    ui->lineEdit_2->setText(filename);
}

