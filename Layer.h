#pragma once
#include <arduino.h>
#include "Key.h"


const int MAX_LAYER_NAME_LEN{ 20 };
constexpr int LAYERS = 10;
constexpr int L_SELECT = LAYERS - 1;

struct Layer {
	const char name[MAX_LAYER_NAME_LEN];
	Key* keys[ROWS][TOTAL_COLS];
};