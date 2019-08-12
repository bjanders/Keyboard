//#include <Adafruit_SSD1306.h>
#include "Key.h"
#include "usb_keyboard.h"

extern int keySlot;
extern int mediaKeySlot;
extern int layer;
extern unsigned short keymedia_consumer_keys[4];

//extern Adafruit_SSD1306 display;
Key::Key() {
	_mod = 0;
	_key = 0;
	_pressed = true;
	_modified = false;
	_presscount = 0;
}
Key::Key(int key) : Key(0, key)
{
}

Key::Key(int mod, int key) : Key()
{
	_mod = mod;
	_key = key;
}

int Key::kc()
{
	return _key;
}

int Key::mod()
{
	return _mod;
}

void Key::pressed(bool p)
{
	if (p != _pressed) {
		_modified = true;
		_pressed = p;
		if (p) {
			_presscount++;
		}
	} else {
		_modified = false;
	}
}

bool Key::ismodified()
{
	return _modified;
}

void Key::exe()
{
	if (_pressed) {
		keyboard_modifier_keys |= _mod;
		if (keySlot < 6) {
			keyboard_keys[keySlot++] = _key;
		}
	}
}

void DeadKey::exe()
{
	if (_pressed) {
		keyboard_modifier_keys |= _mod;
		if (keySlot < 5) {
			keyboard_keys[keySlot++] = _key;
			keyboard_keys[keySlot++] = (byte)KEY_SPACE;
		}
	}
}

void ShiftedDeadKey::exe()
{
	if (_pressed) {
		keyboard_modifier_keys |= _mod;
		if ((keyboard_modifier_keys & MODIFIERKEY_SHIFT) && keySlot < 5) {
			keyboard_keys[keySlot++] = _key;
			keyboard_keys[keySlot++] = (byte)KEY_SPACE;
		} else if (keySlot < 6) {
			keyboard_keys[keySlot++] = _key;
		}
	}
}

LayerKey::LayerKey(int layer) : Key()
{
	_old_layer = 0;
	_layer = layer;
}

void LayerKey::exe()
{
	if (_modified) {
		if (_pressed) {
			_old_layer = layer;
			layer = _layer;
			
		} else {
			layer = _old_layer;
		}
	}
}

void LockLayerKey::exe()
{
	if (_modified && _pressed) {
		if (layer == _layer) {
			layer = _old_layer;
		} else {
			_old_layer = layer;
			layer = _layer;
		}
	}
}

MediaKey::MediaKey(int key) : Key(key) {}

void MediaKey::exe()
{
	if (_pressed) {
		keyboard_modifier_keys |= _mod;
		if (keySlot < 4) {
			keymedia_consumer_keys[mediaKeySlot++] = _key;
		}
	}
}
