#include "fillvaluesblock.h"

fillValuesVlock::fillValuesVlock(abstractBlock *parentBlock, QWidget *parent) : QDialog(parent), ui(new Ui::Values) {
    ui->setupUi(this);
    //this->move(200, 200);
    setWindowTitle("Fill IN-port value(s)");
    auto layout = new QVBoxLayout();
    parentBlock = parentBlock ;
    QLineEdit *firstLine = nullptr;
    for (int i = 0; i < parentBlock->getInPortsCount(); i++) {
        if (parentBlock->getInPort(i)->getWire() == nullptr) {
            auto groupLineLayout = new QHBoxLayout();
            QLabel *lblLine = new QLabel(QString::number(i + 1) + ". IN-port of type \"" + parentBlock->getInPort(i)->getDataType()->getType() + "\": ");
            groupLineLayout->addWidget(lblLine);
            layout->addLayout(groupLineLayout);
            for (int j = 0; j < parentBlock->getInPort(i)->getDataType()->getValuesLength(); j++) {
                auto groupLineLayout = new QHBoxLayout();
                QLabel *lblLine = new QLabel("          " + parentBlock->getInPort(i)->getDataType()->getValueName(j) + ": ");
                line = new QLineEdit();
                if(firstLine == nullptr) { firstLine = line; }
                QRegExp re("([\\+-].)?\\d*\\.?\\d*");
                QRegExpValidator *validator = new QRegExpValidator(re, this);
                line->setValidator(validator);
                line->setText(QString::number(parentBlock->getInPort(i)->getDataType()->getValue(j)));
                line->setObjectName(QString::number((i + 1) * 100 + j));
                groupLineLayout->addWidget(lblLine);
                groupLineLayout->addWidget(line);
                layout->addLayout(groupLineLayout);
            }
        }
    }

    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacing(200);
    buttonLayout->addWidget(ui->pushButton);
    buttonLayout->addWidget(ui->pushButton_2);
    layout->addLayout(buttonLayout);
    this->setLayout(layout);
    this->setFixedSize(layout->minimumSize());
    firstLine->setFocus();
    this->move((qobject_cast<MainWindow *>(parentBlock->myParent->parent()))->x() + ((qobject_cast<MainWindow *>(parentBlock->myParent->parent()))->width() - this->width()) / 2,
                 (qobject_cast<MainWindow *>(parentBlock->myParent->parent()))->y() + ((qobject_cast<MainWindow *>(parentBlock->myParent->parent()))->height() - this->height()) / 2);
}

fillValuesVlock::~fillValuesVlock() {
    delete ui;
}

void fillValuesVlock::on_pushButton_clicked() {
    for (int i = 0; i < parentBlock->getInPortsCount(); i++) {
        if (parentBlock->getInPort(i)->getWire() == nullptr) {
            for (int j = 0; j < parentBlock->getInPort(i)->getDataType()->getValuesLength(); j++) {
                parentBlock->getInPort(i)->getDataType()->setValue(j, this->findChild<QLineEdit *>(QString::number((i + 1) * 100 + j))->text().toDouble());
                parentBlock->getInPort(i)->getDataType()->setValuesSet(true);
                parentBlock->getInPort(i)->update();
            }
        }
    }
    this->done(1);
}
