#include "Port/port.h"

Values::Values(QWidget *parent) : QDialog(parent), ui(new Ui::Values)
{
    ui->setupUi(this);
    setWindowTitle("Fill in-port value/s");
    groupBox = new QGroupBox("Value of type: " +blockPort->dataType->getType());
    groupBox->setParent(this);
    int spacing = 50;
    for(int i = 0; i < blockPort->dataType->getValuesLength(); i++) {
        line = new QLineEdit(groupBox);
        line->setText(QString::number(blockPort->dataType->getValue(i)));
        line->setObjectName(QString::number(i));
        line->move(0, spacing);
        spacing = spacing+50;
    }
   groupBox->resize(420, 200);
}

Values::~Values()
{
    delete ui;
}

void Values::on_pushButton_clicked()
{
    for(int i = 0; i < blockPort->dataType->getValuesLength(); i++) {
            blockPort->dataType->setValue(i, groupBox->findChild<QLineEdit *>(QString::number(i))->text().toDouble());
    }
    this->done(1);
}
