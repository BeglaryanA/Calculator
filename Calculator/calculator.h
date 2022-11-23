#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
private slots:
    void digit_numbers();
    void on_dot_clicked();
    void operation();
    void on_clear_clicked();

    void on_equal_clicked();
    void math_operation();
private:
    Ui::Calculator *ui;

};
#endif // CALCULATOR_H
