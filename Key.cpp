//#include <Adafruit_SSD1306.h>

#include "Key.h"
#include "usb_keyboard.h"
#include "Keyboard.h"
#include "Bitmap.h"

int mediaKeySlot;
extern int layer;
extern Adafruit_SSD1306 leftDisplay;
extern byte mouse_keys[3];
KeyList keyList;

Key::Key(int mod, int key) :
	bitmaps{ 0 },
	texts{ 0 },
	modifiers{ mod },
	keyCode{ key },
	bounce{ 0 },
	pressed{ false },
	modified{ false },
	pressCount{ 0 }
{ }

Key::Key() : Key(0, 0)
{ }

Key::Key(int key) : Key(0, key)
{ }

Key::Key(int mod, int key, const uint8_t *bitmap) : Key(mod, key)
{
	bitmaps[0] = bitmap;
}

Key::Key(int key, const uint8_t *bitmap) : Key(0, key)
{
	bitmaps[0] = bitmap;
}

void Key::setPressed(bool p)
{
	if (p != pressed) {
		modified = true;
		pressed = p;
		if (p) {
			pressCount++;
		}
	} else {
		modified = false;
	}
}

void Key::setBitmap(uint8_t mod, const uint8_t *bitmap)
{
	if (mod < 8) {
		bitmaps[mod] = bitmap;
	}
}

void Key::setText(uint8_t mod, const char *text)
{
	if (mod < 8) {
		texts[mod] = text;
	}
}


// render should render the key text or symbol starting
// from the top left corner x,y. The rendering area is 
// 20*13 pixel icons or max 3 chars (18 * 8 pixels)
void Key::render(Adafruit_SSD1306 *display, int x, int y) const
{
	// FIX: Implmenent this as a table instead, with modifiers and the key for each row
	const char *str = NULL;
	const uint8_t *bitmap = NULL;

	if (bitmaps[0] != NULL) {
		bitmap = bitmaps[0];
	}  else if (texts[0] != NULL) {
		str = texts[0];
	} else {
		switch (keyCode) {
		case KEY_A: str = "A"; break;
		case KEY_B: str = "B"; break;
		case KEY_C: str = "C"; break;
		case KEY_D: str = "D"; break;
		case KEY_E: str = "E"; break;
		case KEY_F: str = "F"; break;
		case KEY_G: str = "G"; break;
		case KEY_H: str = "H"; break;
		case KEY_I: str = "I"; break;
		case KEY_J: str = "J"; break;
		case KEY_K: str = "K"; break;
		case KEY_L: str = "L"; break;
		case KEY_M: str = "M"; break;
		case KEY_N: str = "N"; break;
		case KEY_O: str = "O"; break;
		case KEY_P: str = "P"; break;
		case KEY_Q: str = "Q"; break;
		case KEY_R: str = "R"; break;
		case KEY_S: str = "S"; break;
		case KEY_T: str = "T"; break;
		case KEY_U: str = "U"; break;
		case KEY_V: str = "V"; break;
		case KEY_W: str = "W"; break;
		case KEY_X: str = "X"; break;
		case KEY_Y: str = "Y"; break;
		case KEY_Z: str = "Z"; break;
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
		case KEY_TAB: bitmap = tab; break;
		case KEY_SPACE: bitmap = space; break;
		case KEY_RETURN: bitmap = enter; break;
		case KEY_BACKSPACE: bitmap = backspace; break;
		case KEY_ESC: str = "Esc"; break;
		case KEY_DELETE: str = "Del"; break;
		case KEY_INSERT: str = "Ins"; break;
		case KEY_UP: str = "\x18"; break;
		case KEY_LEFT: str = "\x1b"; break;
		case KEY_RIGHT: str = "\x1a"; break;
		case KEY_DOWN: str = "\x19"; break;
		case KEY_HOME: str = "\x11"; break;
		case KEY_END: str = "\x10"; break;
		case KEY_PAGE_DOWN: bitmap = pagedown; break;
		case KEY_PAGE_UP: bitmap = pageup; break;
		case KEY_PAUSE: str = "Pau"; break;
		case KEY_SCROLL_LOCK: str = "ScL"; break;
		case KEY_PRINTSCREEN: str = "Prn"; break;
		case KEY_CAPS_LOCK: bitmap = capslock; break;
		default: str = NULL;
		}
		if (modifiers == 0) {
			if (keyboard_modifier_keys & (MODIFIERKEY_SHIFT | MODIFIERKEY_RIGHT_SHIFT)) {
				switch (keyCode) {
				case KEY_0: str = ")"; break;
				case KEY_1: str = "!"; break;
				case KEY_2: str = "@"; break;
				case KEY_3: str = "#"; break;
				case KEY_4: str = "$"; break;
				case KEY_5: str = "%"; break;
				case KEY_6: str = "^"; break;
				case KEY_7: str = "&"; break;
				case KEY_8: str = "*"; break;
				case KEY_9: str = "("; break;
				case KEY_LEFT_BRACE: str = "{"; break;
				case KEY_RIGHT_BRACE: str = "}"; break;
				case KEY_TILDE: str = "~"; break;
				case KEY_QUOTE: str = "\""; break;
				case KEY_MINUS: str = "_"; break;
				case KEY_EQUAL: str = "+"; break;
				case KEY_SLASH: str = "?"; break;
				case KEY_PERIOD: str = ">"; break;
				case KEY_COMMA: str = "<"; break;
				case KEY_SEMICOLON: str = ":"; break;
				case KEY_BACKSLASH: str = "|"; break;
				}
			} else {
				switch (keyCode) {
				case KEY_0: str = "0"; break;
				case KEY_1: str = "1"; break;
				case KEY_2: str = "2"; break;
				case KEY_3: str = "3"; break;
				case KEY_4: str = "4"; break;
				case KEY_5: str = "5"; break;
				case KEY_6: str = "6"; break;
				case KEY_7: str = "7"; break;
				case KEY_8: str = "8"; break;
				case KEY_9: str = "9"; break;
				case KEY_LEFT_BRACE: str = "["; break;
				case KEY_RIGHT_BRACE: str = "]"; break;
				case KEY_TILDE: str = "`"; break;
				case KEY_QUOTE: str = "'"; break;
				case KEY_MINUS: str = "-"; break;
				case KEY_EQUAL: str = "="; break;
				case KEY_SLASH: str = "/"; break;
				case KEY_PERIOD: str = "."; break;
				case KEY_COMMA: str = ","; break;
				case KEY_SEMICOLON: str = ";"; break;
				case KEY_BACKSLASH: str = "\\"; break;
				}
			}
		}
		if (modifiers == MODIFIERKEY_LEFT_SHIFT || modifiers == MODIFIERKEY_RIGHT_SHIFT) {
			switch (keyCode) {
			case KEY_0: str = ")"; break;
			case KEY_1: str = "!"; break;
			case KEY_2: str = "@"; break;
			case KEY_3: str = "#"; break;
			case KEY_4: str = "$"; break;
			case KEY_5: str = "%"; break;
			case KEY_6: str = "^"; break;
			case KEY_7: str = "&"; break;
			case KEY_8: str = "*"; break;
			case KEY_9: str = "("; break;
			case KEY_TILDE: str = "~"; break;
			case KEY_EQUAL: str = "+"; break;
			case KEY_SEMICOLON: str = ":"; break;
			}
		}
		if (modifiers == MODIFIERKEY_RIGHT_ALT) {
			// Scandinavian characters
			switch (keyCode) {
			case KEY_Q: str = "\x8e"; break;
			case KEY_P: str = "\x99"; break;
			case KEY_W: str = "\x8f"; break;
			}
		}
		if (keyCode == 0 && modifiers != 0) {
			// Just the modifier with no key attache
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
		size_t n = strlen(str);
		display->setCursor(x + (3 - n)*3 + 1, y + 3);
		display->print(str);
	}
}

void Key::exe()
{
	if (pressed) {
		keypress_t *keypress = keyList.currentKey();
		keypress->modifiers |= modifiers;
		if (keypress->keyIndex < 6 && keyCode != 0) {
			keypress->keyCodes[keypress->keyIndex++] = keyCode;
		}
	}
}

void DeadKey::exe()
{
	if (pressed) {
		keypress_t *keypress = keyList.currentKey();
		keypress->modifiers |= modifiers;
		if (keypress->keyIndex < 5 && keyCode != 0) {
			keypress->keyCodes[keypress->keyIndex++] = keyCode;
			keypress->keyCodes[keypress->keyIndex++] = (uint8_t)KEY_SPACE;
		}
	}
}

void ShiftedDeadKey::exe()
{
	if (pressed) {
		keypress_t *keypress = keyList.currentKey();
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
	if (pressed && modified) {
		keypress_t *keypress = keyList.currentKey();
		keypress->modifiers |= modifiers;
		if (keyCode == 0) {
			return;
		}
		uint8_t temp_modifiers = keypress->modifiers;
		keypress->keyCodes[0] = (uint8_t)KEY_U;
		keypress->modifiers = (uint8_t)MODIFIERKEY_ALT;
		keyList.keypressListLen++;
		keypress = keyList.currentKey();
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
		if (pressed) {
			Serial.printf("Layer change %d -> %d\n", layer, _layer);
			oldLayer = layer;
			layer = _layer;
		} else {
			Serial.printf("Layer change %d -> %d\n", _layer, oldLayer);
			layer = oldLayer;
		}
	}
}

void LayerKey::render(Adafruit_SSD1306 *display, int x, int y) const
{
	display->setCursor(x + 4, y + 3);
	display->printf("L%d", _layer);		
}


void LockLayerKey::exe() 
{
	if (modified && !pressed) {
		layer = _layer;
		Serial.println(layer);
//		leftDisplay.fillRect(0, 8, 128, 64 - 8, BLACK);
	}
}


void SelectLayerKey::exe()
{
	LockLayerKey::exe();
	if (modified && !pressed) {
		Serial.println("Settings screen");
		leftDisplay.clearDisplay();
		leftDisplay.setTextSize(1);                                     
		leftDisplay.setCursor(0, 0);
		leftDisplay.println("Select layer");
		leftDisplay.println("A: Win");
		leftDisplay.println("S: Mac");
		leftDisplay.println("D: Gaming");
		leftDisplay.println("F: Photoshop");
		leftDisplay.display();
	}
}

MediaKey::MediaKey(int key) : Key(key) {}


void MediaKey::exe()
{
	if (pressed) {
		if (mediaKeySlot < 4 && keyCode != 0) {
			keymedia_consumer_keys[mediaKeySlot++] = keyCode;
		}
	}
}


void MediaKey::render(Adafruit_SSD1306 *display, int x, int y) const
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

MouseButton::MouseButton(int button) :
	mouseButton{ button }
{
	if (mouseButton < 0 || mouseButton > 2) {
		mouseButton = 0;
	}

	switch (mouseButton) {
	case MOUSE_BUTTON_LEFT: bitmap = mouseleft; break;
	case MOUSE_BUTTON_MIDDLE: bitmap = mousemiddle; break;
	case MOUSE_BUTTON_RIGHT: bitmap = mouseright; break;
	}
}

void MouseButton::exe()
{
	if (pressed) {
		mouse_keys[mouseButton] = 1;
	}

}

void MouseButton::render(Adafruit_SSD1306 *display, int x, int y) const
{
	if (bitmap != NULL) {
		display->drawBitmap(x, y, bitmap, 20, 13, WHITE);
	}
}


MouseMove::MouseMove(MouseDir dir)
{
	switch (dir) {
	case MouseDir::N:
		x = 0;
		y = -1;
		bitmap = mouse_n;
		break;
	case MouseDir::NE:
		x = 1;
		y = -1;
		bitmap = mouse_ne;
		break;
	case MouseDir::E:
		x = 1;
		y = 0;
		bitmap = mouse_e;
		break;
	case MouseDir::SE:
		x = 1;
		y = 1;
		bitmap = mouse_se;
		break;
	case MouseDir::S:
		x = 0;
		y = 1;
		bitmap = mouse_s;
		break;
	case MouseDir::SW:
		x = -1;
		y = 1;
		bitmap = mouse_sw;
		break;
	case MouseDir::W:
		x = -1;
		y = 0;
		bitmap = mouse_w;
		break;
	case MouseDir::NW:
		x = -1;
		y = -1;
		bitmap = mouse_nw;
		break;
	}
}

void MouseMove::exe()
{
	if (pressed) {
		Mouse.move(MouseMove::speed * x, MouseMove::speed * y);
	}
}

void MouseMove::render(Adafruit_SSD1306 *display, int x, int y) const
{
	display->drawBitmap(x, y, bitmap, 20, 13, WHITE);
}

MouseSpeed::MouseSpeed(int speed) : speed{ speed } {}

void MouseSpeed::exe()
{
	if (modified)
	{
		if (pressed) {
			old_speed = MouseMove::speed;
			MouseMove::speed = speed;
		} else {
			MouseMove::speed = default_mouse_speed;
		}
	}
}

MouseScroll::MouseScroll(int steps, unsigned int scroll_interval) : 
	steps{ steps },
	scroll_interval{ scroll_interval }
{
	if (steps > 0) {
		bitmap = mouse_scroll_up;
	} else {
		bitmap = mouse_scroll_down;
	}
}

void MouseScroll::exe()
{
	unsigned long millis_now{ millis() };
	if (pressed && millis_now - scroll_time > scroll_interval) {
		Mouse.scroll(steps);
		scroll_time = millis_now;
	}
}


void MouseScroll::render(Adafruit_SSD1306 *display, int x, int y) const
{
	display->drawBitmap(x, y, bitmap, 20, 13, WHITE);
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