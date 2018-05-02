#include "Port/port.h"

Values::Values(port *parentPort, QWidget *parent) : QDialog(parent), ui(new Ui::Values)
{
    ui->setupUi(this);
    setWindowTitle("Fill in-port value(s)");
    auto layout = new QVBoxLayout();
    blockPort = parentPort;
    QLineEdit *firstLine = nullptr;
    for(int i = 0; i < blockPort->getDataType()->getValuesLength(); i++) {
        auto groupLineLayout = new QHBoxLayout();
        QLabel *lblLine = new QLabel(blockPort->getDataType()->getValueName(i)+ ": ");
        line = new QLineEdit();
        if (firstLine == nullptr) { firstLine = line; }
        QRegExp re("([\\+-].)?\\d*\\.?\\d*");
        QRegExpValidator *validator = new QRegExpValidator(re, this);
        line->setValidator(validator);
        line->setText(QString::number(blockPort->getDataType()->getValue(i)));
        line->setObjectName(QString::number(i));
        groupLineLayout->addWidget(lblLine);
        groupLineLayout->addWidget(line);
        layout->addLayout(groupLineLayout);
    }
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacing(200);
    buttonLayout->addWidget(ui->pushButton);
    buttonLayout->addWidget(ui->pushButton_2);
    layout->addLayout(buttonLayout);
    this->setLayout(layout);
    this->layout()->setSpacing(5);
    firstLine->setFocus();
    this->move((qobject_cast<MainWindow *>(parentPort->myParent->myParent->parent()))->x() + ((qobject_cast<MainWindow *>(parentPort->myParent->myParent->parent()))->width() - this->width()) / 2,
                 (qobject_cast<MainWindow *>(parentPort->myParent->myParent->parent()))->y() + ((qobject_cast<MainWindow *>(parentPort->myParent->myParent->parent()))->height() - this->height()) / 2);
}

Values::~Values()
{
    delete ui;
}

void Values::on_pushButton_clicked()
{
    for(int i = 0; i < blockPort->getDataType()->getValuesLength(); i++) {
            blockPort->getDataType()->setValue(i, this->findChild<QLineEdit *>(QString::number(i))->text().toDouble());
            blockPort->getDataType()->setValuesSet(true);
            blockPort->update();
    }
    this->done(1);
}
