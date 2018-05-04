/*!
 * \title Projekt do ICP - Program pro tvorbu blokových schémat
 *
 * \authors Radek Hůlka (xhulka02), Lukáš Lazar (xlazar10)
 *
 * \date 3.5.2018
 */

#include "RegisterTypes.h"

void registerTypes() {
    qRegisterMetaType<OneDecimalNumber>("One Decimal Number");
    qRegisterMetaType<TwoDecimalNumbers>("Two Decimal Numbers");
    qRegisterMetaType<ThreeDecimalNumbers>("Three Decimal Numbers");
    qRegisterMetaType<Hydrogenium>("Hydrogenium");
    qRegisterMetaType<Oxid>("Oxid");
    qRegisterMetaType<Methan>("Methan");
    qRegisterMetaType<Water>("Water");
    qRegisterMetaType<CarbonDioxide>("Carbon Dioxide");
}
