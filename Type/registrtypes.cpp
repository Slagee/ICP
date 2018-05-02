#include "registrtypes.h"

void registrTypes() {
    qRegisterMetaType<oneDecimalNumber>("One Decimal Number");
    qRegisterMetaType<twoDecimalNumbers>("Two Decimal Numbers");
    qRegisterMetaType<threeDecimalNumbers>("Three Decimal Numbers");
}
