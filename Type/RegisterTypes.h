/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#ifndef REGISTRTYPES_H
#define REGISTRTYPES_H

#include "Type/Types/OneDecimalNumber.h"
#include "Type/Types/TwoDecimalNumbers.h"
#include "Type/Types/ThreeDecimalNumbers.h"
#include "Type/Types/Hydrogenium.h"
#include "Type/Types/Oxid.h"
#include "Type/Types/Methan.h"
#include "Type/Types/CarbonDioxide.h"
#include "Type/Types/Water.h"

/*!
 * \brief Funkce pro registraci konstruktorů typů.
 */
void registerTypes();

#endif // REGISTRTYPES_H
