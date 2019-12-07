//#include <Adafruit_SSD1306.h>
#include "Key.h"
#include "usb_keyboard.h"
#include "Keyboard.h"

int mediaKeySlot;
extern int layer;

KeyList key_list;

//extern Adafruit_SSD1306 display;
Key::Key() {
	_mod = 0;
	_key = 0;
	_pressed = false;
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
		keypress_t *keypress = key_list.current_key();
		keypress->modifiers |= _mod;
		if (keypress->slot < 6 && _key != 0) {
			keypress->keys[keypress->slot++] = _key;
		}
	}
}

void DeadKey::exe()
{
	if (_pressed) {
		keypress_t *keypress = key_list.current_key();
		keypress->modifiers |= _mod;
		if (keypress->slot < 5 && _key != 0) {
			keypress->keys[keypress->slot++] = _key;
			keypress->keys[keypress->slot++] = (byte)KEY_SPACE;
		}
	}
}

void ShiftedDeadKey::exe()
{
	if (_pressed) {
		keypress_t *keypress = key_list.current_key();
		keypress->modifiers |= _mod;
		if (_key == 0) {
			return;
		}
		if ((keypress->modifiers & MODIFIERKEY_SHIFT) && keypress->slot < 5) {
			keypress->keys[keypress->slot++] = _key;
			keypress->keys[keypress->slot++] = (byte)KEY_SPACE;
		} else if (keypress->slot < 6) {
			keypress->keys[keypress->slot++] = _key;
		}
	}
}

void UmlautKey::exe()
{
	if (_pressed && _modified) {
		keypress_t *keypress = key_list.current_key();
		keypress->modifiers |= _mod;
		if (_key == 0) {
			return;
		}
		byte temp_modifiers = keypress->modifiers;
		keypress->keys[0] = (byte)KEY_U;
		keypress->modifiers = (unsigned short)MODIFIERKEY_ALT;
		key_list.keypress_list_len++;
		keypress = key_list.current_key();
		keypress->keys[0] = _key;
		keypress->modifiers = temp_modifiers | _mod;
		keypress->slot = 1;
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
		Serial.println("LayerKey");
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
	if (_modified && !_pressed) {
		layer = _layer;
		Serial.println(layer);
	}
}

MediaKey::MediaKey(int key) : Key(key) {}

void MediaKey::exe()
{
	if (_pressed) {
		if (mediaKeySlot < 4 && _key != 0) {
			keymedia_consumer_keys[mediaKeySlot++] = _key;
		}
	}
}

KeyList::KeyList()
{
	reset();
}

void KeyList::reset()
{
	keypress_list_len = 1;
	memset(keypress_list, 0, sizeof(keypress_list));
}

keypress_t *KeyList::current_key()
{
	return &keypress_list[keypress_list_len - 1];
}