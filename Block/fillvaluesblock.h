#ifndef FILLVALUESBLOCK_H
#define FILLVALUESBLOCK_H

#include <QGroupBox>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ui_values.h"
#include "abstractBlock.h"

class port;
class abstractBlock;

class fillValuesVlock : public QDialog
{
    Q_OBJECT

public:
    explicit fillValuesVlock(abstractBlock *parentBlock, QWidget *parent = 0);
    ~fillValuesVlock();
    QGroupBox *groupBox;
    QLineEdit *line;

private slots:
   void on_pushButton_clicked();

private:
    Ui::Values *ui;
    abstractBlock *parentBlock;
};


#endif // FILLVALUESBLOCK_H
