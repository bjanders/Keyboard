#pragma once
#include <arduino.h>
#include "Key.h"

const int MAX_LAYER_NAME_LEN{ 20 };

//class Layer {
//public:
//	char name[MAX_LAYER_NAME_LEN];
//	Key *keys[ROWS][TOTAL_COLS];
//};

struct Layer {
	const char name[MAX_LAYER_NAME_LEN];
	Key *keys[ROWS][TOTAL_COLS];
};