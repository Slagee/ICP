/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "FillValuesBlock.h"

FillValuesBlock::FillValuesBlock(AbstractBlock *someBlock, QWidget *parent) : QDialog(parent), ui(new Ui::FillValues) {
    ui->setupUi(this);
    this->block = someBlock;

    this->setWindowTitle("Fill IN-port value(s)");

    auto layout = new QVBoxLayout();
    QHBoxLayout *groupLineLayout = nullptr;
    QLineEdit *firstLine = nullptr;
    QLineEdit *line = nullptr;
    QLabel *labelLine = nullptr;
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("([\\+-].)?\\d*\\.?\\d*"), this);

    // vyvtvoreni policek pro vsechny hodnoty vstupnich portu
    for (int i = 0; i < this->block->getInPortsCount(); i++) {
        if (this->block->getInPort(i)->getWire() == nullptr) {

            // vytvoreni popisu pro port
            groupLineLayout = new QHBoxLayout();
            labelLine = new QLabel(QString::number(i + 1) + ". IN-port of type \"" + this->block->getInPort(i)->getDataType()->getType() + "\": ");
            labelLine->setStyleSheet("font-weight: bold");
            groupLineLayout->addWidget(labelLine);
            layout->addLayout(groupLineLayout);

            // vytvoreni policek pro hodnoty portu
            for (int j = 0; j < this->block->getInPort(i)->getDataType()->getValuesLength(); j++) {
                groupLineLayout = new QHBoxLayout();
                labelLine = new QLabel("          " + this->block->getInPort(i)->getDataType()->getValueName(j) + ": ");
                line = new QLineEdit();
                if (firstLine == nullptr) { firstLine = line; }
                line->setValidator(validator);
                line->setText(QString::number(this->block->getInPort(i)->getDataType()->getValue(j)));
                line->setObjectName(QString::number((i + 1) * 100 + j));
                groupLineLayout->addWidget(labelLine);
                groupLineLayout->addWidget(line);
                layout->addLayout(groupLineLayout);
            }
        }
    }

    // kdyz neni nic k vyplneni
    if (firstLine == nullptr) {
        groupLineLayout = new QHBoxLayout();
        labelLine = new QLabel("All IN-ports are wired... Nothing to fill.");
        groupLineLayout->addWidget(labelLine);
        layout->addLayout(groupLineLayout);
    }

    // pridani tlacitek
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addSpacing(200);
    buttonLayout->addWidget(ui->pushButton);
    buttonLayout->addWidget(ui->pushButton_2);
    layout->addLayout(buttonLayout);

    // pridani vseho do okynka
    this->setLayout(layout);
    this->setFixedSize(layout->minimumSize());

    // nastaveni focusu na prvni policko
    if (firstLine != nullptr) {
        firstLine->setFocus();
    }

    // umisteni okna na sted parent okna
    this->move((qobject_cast<MainWindow *>(this->block->myParent->parent()))->x() + ((qobject_cast<MainWindow *>(this->block->myParent->parent()))->width() - this->width()) / 2, (qobject_cast<MainWindow *>(this->block->myParent->parent()))->y() + ((qobject_cast<MainWindow *>(this->block->myParent->parent()))->height() - this->height()) / 2);
}

FillValuesBlock::~FillValuesBlock() { delete ui; }

void FillValuesBlock::on_pushButton_clicked() {

    // ulozeni zadanych hodnot uzivatelem
    for (int i = 0; i < this->block->getInPortsCount(); i++) {
        if (this->block->getInPort(i)->getWire() == nullptr) {
            for (int j = 0; j < this->block->getInPort(i)->getDataType()->getValuesLength(); j++) {
                this->block->getInPort(i)->getDataType()->setValue(j, this->findChild<QLineEdit *>(QString::number((i + 1) * 100 + j))->text().toDouble());
                this->block->getInPort(i)->getDataType()->setValuesSet(true);
                this->block->getInPort(i)->update();
            }
        }
    }
    this->done(1);
}
