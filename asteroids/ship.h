#pragma once
#include "structs.h"

void ShipInit(Ship& self);
void ShipUpdate(Ship& self, Asteroids& asters, Keys& keys);
void ShipDraw(Ship& self, Keys& keys);