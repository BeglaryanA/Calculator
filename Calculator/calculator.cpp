#include "calculator.h"
#include "./ui_calculator.h"


double calcVal = 0.0;
bool divid = false;
bool mult = false;
bool plus = false;
bool minus = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->precent, SIGNAL(clicked()), this, SLOT(operation()));
    connect(ui->plus_minus, SIGNAL(clicked()), this, SLOT(operation()));
    connect(ui->plus, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->div, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->mul, SIGNAL(clicked()), this, SLOT(math_operation()));
    connect(ui->minus, SIGNAL(clicked()), this, SLOT(math_operation()));
    ui->Line->setText(QString::number(calcVal));
    QPushButton* numButton[10];
    for (int i = 0; i < 10; ++i) {
        QString butName = "button" + QString::number(i);
        numButton[i] = Calculator::findChild<QPushButton*>(butName);
        connect(numButton[i], SIGNAL(released()), this, SLOT(digit_numbers()));
    }
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::operation() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    if (button->text() == "+/-") {
        double LineVal = ui->Line->text().toDouble();
        LineVal *= -1;
        ui->Line->setText(QString::number(LineVal));
    } else {
        double LineVal = ui->Line->text().toDouble();
        LineVal *= 0.01;
        ui->Line->setText(QString::number(LineVal));
    }
}


void Calculator::on_clear_clicked() {
    ui->Line->setText("");
    calcVal = 0.0;
    divid = false;
    mult = false;
    plus = false;
    minus = false;
}

void Calculator::digit_numbers() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString butVal = button->text();
    QString LineVal = ui->Line->text();
    if ((butVal.toDouble() == 0) || (butVal.toDouble() == 0.0)) {
        ui->Line->setText(LineVal + butVal);
    } else {
        QString newVal = LineVal + butVal;
        double dbNewVal = newVal.toDouble();
        ui->Line->setText(QString::number(dbNewVal, 'g', 16));
    }

}


void Calculator::on_dot_clicked()
{
    if (!(ui->Line->text().contains('.'))) {
        ui->Line->setText(ui->Line->text() + ".");
    }
}

void Calculator::math_operation() {
    divid = false;
    mult = false;
    plus = false;
    minus = false;
    QString LineVal = ui->Line->text();
    calcVal = LineVal.toDouble();
    QPushButton* button = static_cast<QPushButton*> (sender());
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0) {
        divid = true;
    } else  if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {

        plus = true;
    } else     if (QString::compare(butVal, "X", Qt::CaseInsensitive) == 0) {
        mult = true;
    } else {
        minus = true;
    }
    ui->Line->setText("");
}


void Calculator::on_equal_clicked()
{
    double solution = 0.0;
    QString LineVal = ui->Line->text();
    double dbLineVal = LineVal.toDouble();
    if (plus || mult || divid || minus) {
        if (plus) {
            solution = calcVal + dbLineVal;
        } else if (minus) {
            solution = calcVal - dbLineVal;
        } else if (mult) {
            solution = calcVal * dbLineVal;
        } else {
            solution = calcVal / dbLineVal;
        }
    }
    ui->Line->setText(QString::number(solution, 'g', 16));
}

