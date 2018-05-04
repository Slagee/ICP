/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#ifndef BLOCKSFACTORY_H
#define BLOCKSFACTORY_H

#include "Block/Blocks/Adder.h"
#include "Block/Blocks/Subtractor.h"
#include "Block/Blocks/Multiplier.h"
#include "Block/Blocks/Divider.h"
#include "Block/Blocks/Adder1w1a2w1to1w1a2w2a3w3.h"
#include "Block/Blocks/Adder1w1a2w2a3w3to1w1a2w1.h"
#include "Block/Blocks/Adder1w2to1w1.h"
#include "Block/Blocks/Adder1w3to1w1a2w1.h"
#include "Block/Blocks/Round.h"
#include "Block/Blocks/WaterLaboratory.h"

/*!
 * \brief NUMBER_OF_BLOCKS - konstanta pro nastavení počtu používaný bloků
 */
const int NUMBER_OF_BLOCKS = 10;

/*!
 * \brief BLOCKS_CLASSES[] - pole názvů tříd používaných bloků
 */
const QString BLOCKS_CLASSES[NUMBER_OF_BLOCKS] = {"Adder", "Subtractor", "Multiplier", "Divider", "Round", "Adder1w1a2w1to1w1a2w2a3w3", "Adder1w1a2w2a3w3to1w1a2w1", "Adder1w2to1w1", "Adder1w3to1w1a2w1", "WaterLaboratory"};

/*!
 * \brief Funkce pro vytvořené bloku id jména jeho třídy
 * \param classId - id jména třídy bloku
 * \param x - x-ová souřadnice umístění bloku
 * \param y - y-nová souřadnice umístění bloku
 * \param parent - ukazatel na rodiče bloku (scéna)
 */
void blocksFactory(int classId, int x, int y, QGraphicsScene *parent = 0);

/*!
 * \brief Funkce pro získání id trídy z jejího názvu.
 * \param name - jméno třídy
 * \return Vrací id třídy
 */
int getClassIdFromClassName(QString name);

#endif // BLOCKSFACTORY_H
