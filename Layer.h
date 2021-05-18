#pragma once
#include <arduino.h>
#include "Key.h"


constexpr int max_layer_name_len{ 20 };
constexpr int LAYERS = 11;
constexpr int L_SELECT{ 10 };


struct Layer {
	const char name[max_layer_name_len];
	Key* keys[ROWS][TOTAL_COLS];
};