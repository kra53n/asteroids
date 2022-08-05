#pragma once
#include "structs.h"

void ShipInit(Ship& self, int wdt);
void ShipUpdate(Ship& self, KeysStatus& keys);
void ShipDraw(Ship& self);