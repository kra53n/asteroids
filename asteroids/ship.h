#pragma once
#include "structs.h"

void ShipInit(Ship& self);
void ShipUpdate(Ship& self, Asteroids& asters, KeysStatus& keys);
void ShipDraw(Ship& self, KeysStatus& keys);