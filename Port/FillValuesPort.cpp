/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "Port/FillValuesPort.h"

FillValuesPort::FillValuesPort(Port *somePort, QWidget *parent) : QDialog(parent), ui(new Ui::FillValues) {
    ui->setupUi(this);
    this->port = somePort;

    setWindowTitle("Fill in-port value/s");

    auto layout = new QVBoxLayout();
    QHBoxLayout *groupLineLayout = nullptr;
    QLineEdit *firstLine = nullptr;
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("([\\+-].)?\\d*\\.?\\d*"), this);
    QLineEdit *line = nullptr;
    QLabel *labelLine = new QLabel("IN-port of type \"" + this->port->getDataType()->getType() + "\": ");

    labelLine->setStyleSheet("font-weight: bold");
    layout->addWidget(labelLine);

    // vytvoreni policek pro vechny hodnoty portu
    for(int i = 0; i < this->port->getDataType()->getValuesLength(); i++) {
        groupLineLayout = new QHBoxLayout();
        labelLine = new QLabel(this->port->getDataType()->getValueName(i)+ ": ");
        line = new QLineEdit();
        if (firstLine == nullptr) { firstLine = line; }
        line->setValidator(validator);
        line->setText(QString::number(this->port->getDataType()->getValue(i)));
        line->setObjectName(QString::number(i));
        groupLineLayout->addWidget(labelLine);
        groupLineLayout->addWidget(line);
        layout->addLayout(groupLineLayout);
    }

    // pridani tlacitek
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacing(200);
    buttonLayout->addWidget(ui->pushButton_2);
    buttonLayout->addWidget(ui->pushButton);
    layout->addLayout(buttonLayout);

    // nastaveni vytvoreneho do okna
    this->setLayout(layout);
    this->setFixedSize(layout->minimumSize());

    // nastaveni focusu na prvni policko
    firstLine->setFocus();

    // nastaveni okna na stred parent okna
    this->move((qobject_cast<MainWindow *>(this->port->myParent->myParent->parent()))->x() + ((qobject_cast<MainWindow *>(this->port->myParent->myParent->parent()))->width() - this->width()) / 2,
                 (qobject_cast<MainWindow *>(this->port->myParent->myParent->parent()))->y() + ((qobject_cast<MainWindow *>(this->port->myParent->myParent->parent()))->height() - this->height()) / 2);
}

FillValuesPort::~FillValuesPort() {
    delete ui;
}

void FillValuesPort::on_pushButton_clicked() {

    // ulozeni hodnot zadanych uzivatelem
    for(int i = 0; i < this->port->getDataType()->getValuesLength(); i++) {
            this->port->getDataType()->setValue(i, this->findChild<QLineEdit *>(QString::number(i))->text().toDouble());
            this->port->getDataType()->setValuesSet(true);
            this->port->update();
    }
    this->done(1);
}
