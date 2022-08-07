#pragma once
#include "structs.h"

void ShipInit(Ship& self, int wdt);
void ShipUpdate(Ship& self, Asteroids& asters, KeysStatus& keys);
void ShipDraw(Ship& self);