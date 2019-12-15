//#include <Adafruit_SSD1306.h>

#include "Key.h"
#include "usb_keyboard.h"
#include "Keyboard.h"
#include "Bitmap.h"

int mediaKeySlot;
extern int layer;
extern keylayer_t keyMap[10];
extern Adafruit_SSD1306 leftDisplay;
KeyList key_list;

//extern Adafruit_SSD1306 display;
Key::Key() : 
	modifiers {},
	keyCode{},
	_pressed{false},
	modified{false},
	pressCount{0}
{
	memset(_bitmap, 0, sizeof(_bitmap));
	memset(_text, 0, sizeof(_text));
}

Key::Key(int key) : Key(0, key)
{
}

Key::Key(int mod, int key) : Key()
{
	modifiers = mod;
	keyCode = key;
}


Key::Key(int mod, int key, const uint8_t *bitmap) : Key(mod, key)
{
	_bitmap[0] = bitmap;
}

Key::Key(int key, const uint8_t *bitmap) : Key(0, key)
{
	_bitmap[0] = bitmap;
}

int Key::KeyCode()
{
	return keyCode;
}

int Key::Modifiers()
{
	return modifiers;
}

void Key::pressed(bool p)
{
	if (p != _pressed) {
		modified = true;
		_pressed = p;
		if (p) {
			pressCount++;
		}
	} else {
		modified = false;
	}
}

bool Key::isModified()
{
	return modified;
}

void Key::setBitmap(uint8_t mod, const uint8_t *bitmap)
{
	if (mod < 8) {
		_bitmap[mod] = bitmap;
	}
}

void Key::setText(uint8_t mod, const char *text)
{
	if (mod < 8?) {
		_text[mod] = text;
	}
}


// max 14 pixels high
// and 21 pixels wide -> 20*13 pixel icons
// or 3 chars (18 * 8 pixels)
void Key::render(Adafruit_SSD1306 *display, int x, int y)
{
	const char *str = NULL;
	const uint8_t *bitmap = NULL;

	if (_bitmap[0] != NULL) {
		bitmap = _bitmap[0];
	} else {
		switch (keyCode) {
		case KEY_A: str = " A"; break;
		case KEY_B: str = " B"; break;
		case KEY_C: str = " C"; break;
		case KEY_D: str = " D"; break;
		case KEY_E: str = " E"; break;
		case KEY_F: str = " F"; break;
		case KEY_G: str = " G"; break;
		case KEY_H: str = " H"; break;
		case KEY_I: str = " I"; break;
		case KEY_J: str = " J"; break;
		case KEY_K: str = " K"; break;
		case KEY_L: str = " L"; break;
		case KEY_M: str = " M"; break;
		case KEY_N: str = " N"; break;
		case KEY_O: str = " O"; break;
		case KEY_P: str = " P"; break;
		case KEY_Q: str = " Q"; break;
		case KEY_R: str = " R"; break;
		case KEY_S: str = " S"; break;
		case KEY_T: str = " T"; break;
		case KEY_U: str = " U"; break;
		case KEY_V: str = " V"; break;
		case KEY_W: str = " W"; break;
		case KEY_X: str = " X"; break;
		case KEY_Y: str = " Y"; break;
		case KEY_Z: str = " Z"; break;
		case KEY_F1: str = "F1"; break;
		case KEY_F2: str = "F2"; break;
		case KEY_F3: str = "F3"; break;
		case KEY_F4: str = "F4"; break;
		case KEY_F5: str = "F5"; break;
		case KEY_F6: str = "F6"; break;
		case KEY_F7: str = "F7"; break;
		case KEY_F8: str = "F8"; break;
		case KEY_F9: str = "F9"; break;
		case KEY_F10: str = "F10"; break;
		case KEY_F11: str = "F11"; break;
		case KEY_F12: str = "F12"; break;
			//case KEY_: str = " "; break;
		case KEY_TAB: bitmap = tab; break;
		case KEY_SPACE: bitmap = space; break;
		case KEY_RETURN: bitmap = enter; break;
		case KEY_BACKSPACE: bitmap = backspace; break;
		case KEY_ESC: str = "Esc"; break;
		case KEY_DELETE: str = "Del"; break;
		case KEY_INSERT: str = "Ins"; break;
		case KEY_UP: str = " \x18"; break;
		case KEY_LEFT: str = " \x1b"; break;
		case KEY_RIGHT: str = " \x1a"; break;
		case KEY_DOWN: str = " \x19"; break;
		case KEY_HOME: str = " \x11"; break;
		case KEY_END: str = " \x10"; break;
		case KEY_PAGE_DOWN: bitmap = pagedown; break;
		case KEY_PAGE_UP: bitmap = pageup; break;
		case KEY_PAUSE: str = "Pau"; break;
		case KEY_SCROLL_LOCK: str = "ScL"; break;
		case KEY_PRINTSCREEN: str = "Prn"; break;
		case KEY_CAPS_LOCK: bitmap = capslock; break;
		default: str = NULL;
		}
		if (modifiers == 0) {
			switch (keyCode) {
			case KEY_0: str = " 0"; break;
			case KEY_1: str = " 1"; break;
			case KEY_2: str = " 2"; break;
			case KEY_3: str = " 3"; break;
			case KEY_4: str = " 4"; break;
			case KEY_5: str = " 5"; break;
			case KEY_6: str = " 6"; break;
			case KEY_7: str = " 7"; break;
			case KEY_8: str = " 8"; break;
			case KEY_9: str = " 9"; break;
			case KEY_LEFT_BRACE: str = " ["; break;
			case KEY_RIGHT_BRACE: str = " ]"; break;
			case KEY_TILDE: str = " `"; break;
			case KEY_QUOTE: str = " '"; break;
			case KEY_MINUS: str = " -"; break;
			case KEY_EQUAL: str = " ="; break;
			case KEY_SLASH: str = " /"; break;
			case KEY_PERIOD: str = " ."; break;
			case KEY_COMMA: str = " ,"; break;
			case KEY_SEMICOLON: str = " ;"; break;
			case KEY_BACKSLASH: str = " \\"; break;
			}
		}
		if (modifiers == MODIFIERKEY_LEFT_SHIFT || modifiers == MODIFIERKEY_RIGHT_SHIFT) {
			switch (keyCode) {
			case KEY_0: str = " )"; break;
			case KEY_1: str = " !"; break;
			case KEY_2: str = " @"; break;
			case KEY_3: str = " #"; break;
			case KEY_4: str = " $"; break;
			case KEY_5: str = " %"; break;
			case KEY_6: str = " ^"; break;
			case KEY_7: str = " &"; break;
			case KEY_8: str = " *"; break;
			case KEY_9: str = " ("; break;
			case KEY_TILDE: str = " ~"; break;
			case KEY_EQUAL: str = " +"; break;
			case KEY_SEMICOLON: str = " :"; break;
			}
		}
		if (modifiers == MODIFIERKEY_RIGHT_ALT) {
			switch (keyCode) {
			case KEY_Q: str = " \x8e"; break;
			case KEY_P: str = " \x99"; break;
			case KEY_W: str = " \x8f"; break;
			}
		}
		if (keyCode == 0) {
			switch (modifiers) {
			case MODIFIERKEY_SHIFT:
			case MODIFIERKEY_RIGHT_SHIFT:
				bitmap = shift; break;
			case MODIFIERKEY_CTRL:
			case MODIFIERKEY_RIGHT_CTRL:
				bitmap = ctrl; break;
			case MODIFIERKEY_ALT: str = "Alt"; break;
			case MODIFIERKEY_RIGHT_ALT: bitmap = altgr; break;
			case MODIFIERKEY_GUI: bitmap = wingui; break;
			}
		}
	}
	if (bitmap != NULL) {
		display->drawBitmap(x, y, bitmap, 20, 13, WHITE);
	} else if (str != NULL) {
		display->setCursor(x + 1, y + 3);
		display->print(str);
	} else {
		switch (keyCode) {
		//case KEY_UP: display->write(24);
		}
	}
}

void Key::exe()
{
	if (_pressed) {
		keypress_t *keypress = key_list.currentKey();
		keypress->modifiers |= modifiers;
		if (keypress->keyIndex < 6 && keyCode != 0) {
			keypress->keyCodes[keypress->keyIndex++] = keyCode;
		}
	}
}

void DeadKey::exe()
{
	if (_pressed) {
		keypress_t *keypress = key_list.currentKey();
		keypress->modifiers |= modifiers;
		if (keypress->keyIndex < 5 && keyCode != 0) {
			keypress->keyCodes[keypress->keyIndex++] = keyCode;
			keypress->keyCodes[keypress->keyIndex++] = (uint8_t)KEY_SPACE;
		}
	}
}

void ShiftedDeadKey::exe()
{
	if (_pressed) {
		keypress_t *keypress = key_list.currentKey();
		keypress->modifiers |= modifiers;
		if (keyCode == 0) {
			return;
		}
		if ((keypress->modifiers & MODIFIERKEY_SHIFT) && keypress->keyIndex < 5) {
			keypress->keyCodes[keypress->keyIndex++] = keyCode;
			keypress->keyCodes[keypress->keyIndex++] = (uint8_t)KEY_SPACE;
		} else if (keypress->keyIndex < 6) {
			keypress->keyCodes[keypress->keyIndex++] = keyCode;
		}
	}
}

void UmlautKey::exe()
{
	if (_pressed && modified) {
		keypress_t *keypress = key_list.currentKey();
		keypress->modifiers |= modifiers;
		if (keyCode == 0) {
			return;
		}
		uint8_t temp_modifiers = keypress->modifiers;
		keypress->keyCodes[0] = (uint8_t)KEY_U;
		keypress->modifiers = (uint8_t)MODIFIERKEY_ALT;
		key_list.keypressListLen++;
		keypress = key_list.currentKey();
		keypress->keyCodes[0] = keyCode;
		keypress->modifiers = temp_modifiers | modifiers;
		keypress->keyIndex = 1;
	}
}

LayerKey::LayerKey(int layer) :
	Key(),
	_layer{layer},
	oldLayer{0}
{
}
 
void LayerKey::exe()
{	if (modified) {
		if (_pressed) {
			Serial.printf("Layer change %d -> %d\n", layer, _layer);
			oldLayer = layer;
			layer = _layer;
		} else {
			Serial.printf("Layer change %d -> %d\n", _layer, oldLayer);
			layer = oldLayer;
		}
	}
}

void LayerKey::render(Adafruit_SSD1306 *display, int x, int y)
{
	display->setCursor(x + 4, y + 3);
	display->printf("L%d", _layer);		
}


void LockLayerKey::exe() 
{
	if (modified && !_pressed) {
		layer = _layer;
		Serial.println(layer);
		leftDisplay.fillRect(0, 8, 128, 64 - 8, BLACK);
	 // 	for (int y = 64 - 8; y > 0; y -= 8) {
		//	leftDisplay.fillRect(0, y, 128, 8, BLACK);
		//	delay(50);
		//	leftDisplay.display();
		//}
	}
}


void SelectLayerKey::exe()
{
	LockLayerKey::exe();
	if (modified && !_pressed) {
		Serial.println("Settings screen");
		leftDisplay.clearDisplay();
		leftDisplay.setTextSize(1);                                     
		leftDisplay.setCursor(0, 0);
		leftDisplay.println("Select layer");
		//leftDisplay.display();                            
		//delay(50);
		leftDisplay.println("A: Win");
		//leftDisplay.display();
		//delay(50);
		leftDisplay.println("S: Mac");
		//leftDisplay.display();
		//delay(50);
		leftDisplay.println("D: Gaming");
		leftDisplay.println("F: Photoshop");
		leftDisplay.display();
	}
}

MediaKey::MediaKey(int key) : Key(key) {}


void MediaKey::exe()
{
	if (_pressed) {
		if (mediaKeySlot < 4 && keyCode != 0) {
			keymedia_consumer_keys[mediaKeySlot++] = keyCode;
		}
	}
}


void MediaKey::render(Adafruit_SSD1306 *display, int x, int y)
{
	const uint8_t *bitmap = NULL;

	switch (keyCode) {
	case KEY_MEDIA_MUTE: bitmap = mute; break;
	case KEY_MEDIA_VOLUME_DEC: bitmap = voldown; break;
	case KEY_MEDIA_VOLUME_INC: bitmap = volup; break;
	case KEY_MEDIA_PLAY_PAUSE: bitmap = playpause; break;
	}

	if (bitmap != NULL) {
		display->drawBitmap(x, y, bitmap, 20, 13, WHITE);
	}
}

KeyList::KeyList()
{
	reset();
}

void KeyList::reset()
{
	keypressListLen = 1;
	memset(keypressList, 0, sizeof(keypressList));
	//Serial.printf("keypress_list %d\n", sizeof(keypress_list));
}

keypress_t *KeyList::currentKey()
{
	return &keypressList[keypressListLen - 1];
}