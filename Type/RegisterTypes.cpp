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
