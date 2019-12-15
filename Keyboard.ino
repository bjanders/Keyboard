#include <I2CDevice.h>
#include <MCP23017.h>
#include <Wire.h>
#include <usb_keyboard.h>
#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "Key.h"
#include "Bitmap.h"

// Configurable items

const unsigned long SCREENSAVER_MILLIS = 30 * 60 * 1000;

// Other constants

constexpr auto USB_LED_NUM_LOCK = 0;
constexpr auto USB_LED_CAPS_LOCK = 1;
constexpr auto USB_LED_SCROLL_LOCK = 2;
constexpr auto USB_LED_COMPOSE = 3;
constexpr auto USB_LED_KANA = 4;

const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels

const int OLED_DC = 14;
const int OLED_CS = 10;
const int OLED_RESET = 15;


int rowPin[] = { 0, 1, 2, 3 };
int colPin[] = { 4, 5, 6, 7, 8, 9 };

#define SHFT MODIFIERKEY_SHIFT
#define RSHFT MODIFIERKEY_RIGHT_SHIFT
#define CTRL MODIFIERKEY_CTRL
#define RCTRL MODIFIERKEY_RIGHT_CTRL
#define ALT MODIFIERKEY_ALT
#define RALT MODIFIERKEY_RIGHT_ALT
#define GUI MODIFIERKEY_GUI
#define RGUI MODIFIERKEY_RIGHT_GUI


void initKeyMap(keylayer_t *m, int layers);

const int L_WIN = 0;
const int L_MAC = 3;
const int L_GAMING = 6;
const int L_PHOTOSHOP = 7;
const int LAYERS = 10;
const int L_SELECT = LAYERS - 1;

keylayer_t keyMap[LAYERS] = {
	// Layer 0
	{
		{ new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W), new Key(KEY_E), new Key(KEY_R), new Key(KEY_T), /**/ new Key(KEY_Y), new Key(KEY_U), new Key(KEY_I), new Key(KEY_O), new Key(KEY_P), new Key(RALT, KEY_Q) },
		{ new Key(SHFT, 0), new Key(KEY_A), new Key(KEY_S), new Key(KEY_D), new Key(KEY_F), new Key(KEY_G), /**/ new Key(KEY_H), new Key(KEY_J), new Key(KEY_K), new Key(KEY_L), new Key(RALT, KEY_P), new Key(RSHFT, 0) },
		{ new Key(CTRL, 0),	new Key(KEY_Z), new Key(KEY_X), new Key(KEY_C), new Key(KEY_V), new Key(KEY_B), /**/ new Key(KEY_N), new Key(KEY_M), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	new LayerKey(2), new LayerKey(1), new Key(GUI, 0), new Key(KEY_SPACE), new Key(KEY_RETURN), /**/ new SelectLayerKey(L_SELECT), new Key(ALT, 0),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 1
	{
		{ new DeadKey(SHFT, KEY_TILDE), new Key(KEY_DELETE), new Key(KEY_HOME), new Key(KEY_UP), new Key(KEY_END), new Key(KEY_PAGE_UP), /**/ new Key(KEY_PRINTSCREEN), new Key(KEY_LEFT_BRACE), new Key(KEY_RIGHT_BRACE), new DeadKey(KEY_QUOTE), new Key(SHFT, KEY_EQUAL), new Key(RALT, KEY_W) },
		{ NULL,	new Key(KEY_ESC),new Key(KEY_LEFT),	new Key(KEY_DOWN), new Key(KEY_RIGHT), new Key(KEY_PAGE_DOWN), /**/	                      new Key(KEY_SCROLL_LOCK), new Key(SHFT, KEY_9), new Key(SHFT, KEY_0), new Key(KEY_MINUS), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_INSERT), new NoKey(), new Key(KEY_CAPS_LOCK), new NoKey(), new MediaKey(KEY_MEDIA_PLAY_PAUSE), /**/               new Key(KEY_PAUSE), new NoKey(), new Key(KEY_SEMICOLON), new Key(SHFT, KEY_SEMICOLON), new Key(KEY_BACKSLASH), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                            NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	// Layer 2
	{
		{ new DeadKey(KEY_TILDE), new Key(KEY_F9), new Key(KEY_F10), new Key(KEY_F11), new Key(KEY_F12), new MediaKey(KEY_MEDIA_VOLUME_INC), /**/ new Key(SHFT, KEY_8), new Key(KEY_7), new Key(KEY_8), new Key(KEY_9), new Key(KEY_0), new NoKey() },
		{ NULL,	new Key(KEY_F5),new Key(KEY_F6), new Key(KEY_F7), new Key(KEY_F8), new MediaKey(KEY_MEDIA_VOLUME_DEC),	/**/                      new Key(KEY_MINUS), new Key(KEY_4), new Key(KEY_5), new ShiftedDeadKey(KEY_6), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_F1), new Key(KEY_F2), new Key(KEY_F3), new Key(KEY_F4), new MediaKey(KEY_MEDIA_MUTE), /**/                            new Key(SHFT, KEY_EQUAL), new Key(KEY_1), new Key(KEY_2), new Key(KEY_3), new Key(KEY_PERIOD), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                                NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},

	// Mac OS
	// Layer 3 = L_MAC
	{
		{ new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W), new Key(KEY_E), new Key(KEY_R), new Key(KEY_T), /**/ new Key(KEY_Y), new Key(KEY_U), new Key(KEY_I), new Key(KEY_O), new Key(KEY_P), new UmlautKey(KEY_A) },
		{ new Key(SHFT, 0), new Key(KEY_A), new Key(KEY_S), new Key(KEY_D), new Key(KEY_F), new Key(KEY_G), /**/ new Key(KEY_H), new Key(KEY_J), new Key(KEY_K), new Key(KEY_L), new UmlautKey(KEY_O), new Key(RSHFT, 0) },
		{ new Key(GUI, 0, command),	new Key(KEY_Z), new Key(KEY_X), new Key(KEY_C), new Key(KEY_V), new Key(KEY_B), /**/ new Key(KEY_N), new Key(KEY_M), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(GUI, 0, command)},
		{ new Key(ALT, 0, mac_opt),	new LayerKey(L_MAC + 2), new LayerKey(L_MAC + 1), new Key(CTRL, 0), new Key(KEY_SPACE), new Key(KEY_RETURN), /**/ 	 new SelectLayerKey(L_SELECT),  new Key(ALT, 0),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(RCTRL, 0), new Key(ALT, 0, mac_opt) }
	},
	// Layer 4 (L_MAC + 1)
	{
		{ new Key(SHFT, KEY_TILDE), new Key(KEY_DELETE), new Key(KEY_HOME), new Key(KEY_UP), new Key(KEY_END), new Key(KEY_PAGE_UP), /**/             new NoKey(), new Key(KEY_LEFT_BRACE), new Key(KEY_RIGHT_BRACE), new Key(KEY_QUOTE), new Key(SHFT, KEY_EQUAL), new Key(RALT, KEY_A) },
		{ NULL,	new Key(KEY_ESC),new Key(KEY_LEFT),	new Key(KEY_DOWN), new Key(KEY_RIGHT), new Key(KEY_PAGE_DOWN), /**/                               new NoKey(), new Key(SHFT, KEY_9), new Key(SHFT, KEY_0), new Key(KEY_MINUS), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_INSERT), new NoKey(), new NoKey(), new NoKey(), new MediaKey(KEY_MEDIA_PLAY_PAUSE), /**/ new NoKey(), new NoKey(), new Key(KEY_SEMICOLON), new Key(SHFT, KEY_SEMICOLON), new Key(KEY_BACKSLASH), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                                    NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	// Layer 5 (L_MAC + 2)
	{
		{ new Key(KEY_TILDE), new Key(KEY_F9), new Key(KEY_F10), new Key(KEY_F11), new Key(KEY_F12), new MediaKey(KEY_MEDIA_VOLUME_INC), /**/ new Key(SHFT, KEY_8), new Key(KEY_7), new Key(KEY_8), new Key(KEY_9), new Key(KEY_0), new NoKey() },
		{ NULL,	new Key(KEY_F5),new Key(KEY_F6), new Key(KEY_F7), new Key(KEY_F8), new MediaKey(KEY_MEDIA_VOLUME_DEC),	/**/                  new Key(KEY_MINUS), new Key(KEY_4), new Key(KEY_5), new Key(KEY_6), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_F1), new Key(KEY_F2), new Key(KEY_F3), new Key(KEY_F4), new MediaKey(KEY_MEDIA_MUTE), /**/                        new Key(SHFT, KEY_EQUAL), new Key(KEY_1), new Key(KEY_2), new Key(KEY_3), new Key(KEY_PERIOD), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                            NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	// Layer 6 = L_GAMING
	{
		{ new Key(KEY_1), new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W), new Key(KEY_E), new Key(KEY_R),  /**/ new Key(KEY_Y), new Key(KEY_U), new Key(KEY_I), new Key(KEY_O), new Key(KEY_P), new Key(RALT, KEY_Q) },
		{ new Key(KEY_2), new Key(SHFT, 0), new Key(KEY_A), new Key(KEY_S), new Key(KEY_D), new Key(KEY_F),  /**/ new Key(KEY_H), new Key(KEY_J), new Key(KEY_K), new Key(KEY_L), new Key(RALT, KEY_P), new Key(RSHFT, 0) },
		{ new Key(KEY_3), new Key(CTRL, 0),	new Key(KEY_Z), new Key(KEY_X), new Key(KEY_C), new Key (KEY_V),  /**/ new Key(KEY_N), new Key(KEY_M), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	new Key(KEY_V), new Key(KEY_SPACE), new Key(KEY_V), new Key(KEY_F1), new Key(KEY_V), /**/ new SelectLayerKey(L_SELECT), new Key(KEY_ESC),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 7 (L_PHOTOSHOP)
	{
		{ new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W, ps_objselect), new Key(KEY_E, ps_eraser), new Key(KEY_R, ps_rotateview), new Key(KEY_T, ps_text), /**/ new Key(KEY_Y, ps_history), new Key(KEY_U, ps_polygon), new Key(KEY_I, ps_eyedrop), new Key(KEY_O, ps_dodge), new Key(KEY_P, ps_pen), new Key(RALT, KEY_Q) },
		{ new Key(SHFT, 0), new Key(KEY_A, ps_select), new Key(KEY_S, ps_clone), new Key(KEY_D, ps_defaultfb), new Key(KEY_F), new Key(KEY_G, ps_bucket), /**/ new Key(KEY_H, ps_hand), new Key(KEY_J, ps_healing), new Key(KEY_K, ps_frame), new Key(KEY_L, ps_lasso), new Key(RALT, KEY_P), new Key(RSHFT, 0) },
		{ new Key(CTRL, 0),	new Key(KEY_Z, ps_zoom), new Key(KEY_X, ps_switchfb), new Key(KEY_C, ps_crop), new Key(KEY_V, ps_move), new Key(KEY_B, ps_brush), /**/ new Key(KEY_N), new Key(KEY_M, ps_marquee), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	new NoKey(), new NoKey(), new LayerKey(L_PHOTOSHOP + 1), new Key(KEY_SPACE), new Key(KEY_RETURN), /**/ new SelectLayerKey(L_SELECT), new Key(ALT, 0),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 8 (L_PHOTOSHOP + 1)
	{
		{ new Key(KEY_TAB), new Key(KEY_P, ps_pen), new Key(KEY_O, ps_dodge),new Key(KEY_I, ps_eyedrop),  new Key(KEY_U, ps_polygon),   new Key(KEY_Y, ps_history),   /**/ new Key(KEY_Y, ps_history), new Key(KEY_U, ps_polygon), new Key(KEY_I, ps_eyedrop), new Key(KEY_O, ps_dodge), new Key(KEY_P, ps_pen), new Key(RALT, KEY_Q) },
		{  new Key(SHFT, 0), new Key(KEY_A, ps_select), new Key(KEY_L, ps_lasso),    new Key(KEY_K, ps_frame),   new Key(KEY_J, ps_healing),  new Key(KEY_H, ps_hand),  /**/ new Key(KEY_H, ps_hand), new Key(KEY_J, ps_healing), new Key(KEY_K, ps_frame), new Key(KEY_L, ps_lasso), new Key(RALT, KEY_P), new Key(RSHFT, 0)  },
		{ new Key(CTRL, 0),	new Key(KEY_Z, ps_zoom), new Key(KEY_X, ps_switchfb), new Key(KEY_C, ps_crop), new Key(KEY_M, ps_marquee), new Key(KEY_B, ps_brush), /**/ new Key(KEY_N), new Key(KEY_M, ps_marquee), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	new NoKey(), new NoKey(), NULL, new Key(KEY_SPACE), new Key(KEY_RETURN), /**/ new SelectLayerKey(L_SELECT), new Key(ALT, 0),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 9: L_SELECTi
	{
		{ NULL, NULL, NULL, NULL, NULL, NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, new LockLayerKey(L_WIN), new LockLayerKey(L_MAC), new LockLayerKey(L_GAMING), new LockLayerKey(L_PHOTOSHOP), NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL }
	}
	// LAYERS = 8
};


const char *layerNames[LAYERS] = {
	"Windows US-Intl",
	"Windows US-Intl 1",
	"Windows US-Intl 2",
	"Mac",
	"Mac 1",
	"Mac 2",
	"Gaming",
	"Photoshop",
	"Photoshop 1",
	"Select layer"
};

int current_keymap = 0;

#undef SHFT
#undef CTRL
#undef ALT
#undef RALT

unsigned long time = 0;
int layer = 0;			// current keyboard layer
extern KeyList key_list;
extern int keySlot;			// key slot being used 0 - 5
extern int mediaKeySlot;		// media key slot being used 0 - 3
int presses = 0;


byte old_keyboard_keys[6] = { 0, };
unsigned short old_keymedia_consumer_keys[4] = { 0, };
byte old_keyboard_modifier_keys = 0;
byte old_keyboard_leds = 0;
int old_layer = 0;
unsigned long millisKeyPressed = 0;
bool screenSaverOn = false;
unsigned long millisLastKeyScan = 0;
unsigned int usb_events = 0;

Adafruit_SSD1306 leftDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 rightDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
I2CDevice portExpander(MCP23017_ADDR);

void setup()
{
	Serial.begin(9600);
	delay(200);
	Wire.begin();
	initMCP23017Pins();
	resetRightDisplay();
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!leftDisplay.begin(SSD1306_SWITCHCAPVCC, false)) {
		//Serial.println(F("SSD1306 allocation failed"));
		for (;;); // Don't proceed, loop forever
	}
	if (!rightDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3D, false)) {
		//Serial.println(F("SSD1306 allocation failed"));
		for (;;); // Don't proceed, loop forever
	}
	initDisplay();
	initPins();
	initKeyMap(keyMap, LAYERS);
	renderLeftDisplay();
	delay(100);
}

void loop()
{
	unsigned long millisNow = millis();
	if (millisNow - millisLastKeyScan > 10) {
		//scanKeys(millisNow, windowsKeyMap);
		scanKeys(millisNow);
		millisLastKeyScan = millisNow;
		bool stateChange;

		// redraw the display if any of the following has changed:
		// - modifier keys (shift, ctrl, alt etc.)
		// - keyboard leds (num lock, caps lock, scroll lock)
		// - keyboard layer

		// loop through the list of keys to send
		for (int i = 0; i < key_list.keypressListLen; i++) {
			// keyboard_keys and keyboard_modifier_keys are defined in usb_keyboard.h
			memcpy(keyboard_keys, key_list.keypressList[i].keyCodes, 6);
			keyboard_modifier_keys = key_list.keypressList[i].modifiers;
			stateChange = memcmp(keyboard_keys, old_keyboard_keys, 6) != 0 || keyboard_modifier_keys != old_keyboard_modifier_keys;
			if (stateChange) {
				//Serial.printf("Sending %d\n", usb_events++);
				printkeys();
				// send keys that are in keyboard_keys and keyboard_modifier_keys
				usb_keyboard_send();
				memcpy(old_keyboard_keys, keyboard_keys, 6);
				old_keyboard_modifier_keys = keyboard_modifier_keys;
			}
		}
		if (memcmp(keymedia_consumer_keys, old_keymedia_consumer_keys, sizeof(keymedia_consumer_keys)) != 0) {
			usb_keymedia_send();
			memcpy(old_keymedia_consumer_keys, keymedia_consumer_keys, sizeof(keymedia_consumer_keys));
		}
		if (layer != old_layer || keyboard_leds != old_keyboard_leds) {
			old_layer = layer;
			old_keyboard_leds = keyboard_leds;
			renderDisplays();
		}

	}
	if (millisNow - millisKeyPressed > SCREENSAVER_MILLIS) {
		clearDisplays();
		screenSaverOn = true;
	} else if (screenSaverOn) {
		renderDisplays();
		screenSaverOn = false;
	}
	//if (Serial.available()) {
	//	byte serialChar = Serial.read();
	//	//resetLeftDisplay();
	//	leftDisplay.setTextSize(2);
	//	leftDisplay.setCursor(25, 25);
	//	printChar(serialChar);
	//}
}

void printkeys()
{
	Serial.printf("%d %04x  ", layer, keyboard_modifier_keys);
	for (int i = 0; i < 6; i++) {
		Serial.printf("%02x", keyboard_keys[i]);
		Serial.print(' ');
	}
	Serial.println();
}

void initPins(void)
{
	for (int row = 0; row < ROWS; row++) {
		pinMode(rowPin[row], INPUT_PULLUP);
	}

	for (int col = 0; col < COLS_PER_HAND; col++) {
		pinMode(colPin[col], INPUT_PULLUP);
	}
}

void initMCP23017Pins(void)
{
	// Set to input (the default, but to be sure)
	Wire.beginTransmission(MCP23017_ADDR);
	Wire.write(MCP23017_IODIRA);
	Wire.write(0xff);
	// Same for IODIRB, GPB7 out for display
	Wire.write(0x7f);
	Wire.endTransmission();
	// Set pullup on A0-A6
	Wire.beginTransmission(MCP23017_ADDR);
	Wire.write(MCP23017_GPPUA);
	Wire.write(0x7f); // A0-A6
	// pullup on GPPUB B0-B3
	Wire.write(0x0f); // B0-B3
	Wire.endTransmission();
}

// resetRightDisplay sends a reset to the right display using the port expander
void resetRightDisplay(void) {
	byte regVal = portExpander.readRegister(MCP23017_GPIOB);
	// set high
	portExpander.writeRegister(MCP23017_GPIOB, regVal | 0x80);
	delay(1);
	// pull low
	portExpander.writeRegister(MCP23017_GPIOB, regVal & ~0x80);
	delay(10);
	// set high again
	portExpander.writeRegister(MCP23017_GPIOB, regVal | 0x80);
}

// initKeyMap copies the keys from the previous lower layer if a key in the 
// current layer is set to NULL
void initKeyMap(keylayer_t *m, int layers)
{
	for (int layer = 1; layer < layers; layer++) {
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < TOTAL_COLS; col++) {
				if (m[layer][row][col] == NULL && layer > 0) {
					m[layer][row][col] = m[layer - 1][row][col];
				}
			}
		}
	}
}

//void scanKeys(unsigned long millisNow, Key *keyMap[][ROWS][TOTAL_COLS])
void scanKeys(unsigned long millisNow)
{
	key_list.reset();

	for (int i = 0; i < 4; i++) {
		keymedia_consumer_keys[i] = 0;
	}
	mediaKeySlot = 0;

	// Left hand on Teensy
	for (int row = 0; row < ROWS; row++) {
		Key *key;
		pinMode(rowPin[row], OUTPUT);
		digitalWrite(rowPin[row], LOW);
		for (int col = 0; col < COLS_PER_HAND; col++) {
			int val;
			bool isPressed;
			val = digitalRead(colPin[col]);
			key = keyMap[layer][row][col];
			if (key == NULL) continue;
			isPressed = val == LOW;
			key->pressed(isPressed);
			key->exe();
			if (isPressed) {
				millisKeyPressed = millisNow;
			}
		}
		pinMode(row, INPUT_PULLUP);
	}

	// Right hand on MCP23017
	for (int row = 0; row < ROWS; row++) {
		Key *key;
		int colStat;
		// Set row to output
		portExpander.writeRegister(MCP23017_IODIRB, 0x7f & ~(1 << row));
		// Set to low
		portExpander.writeRegister(MCP23017_GPIOB, 0xff & ~(1 << row));
		// read the columns
		colStat = portExpander.readRegister(MCP23017_GPIOA);
		// Set all to input again
		portExpander.writeRegister(MCP23017_IODIRB, 0x7f);
		// and pull up
		portExpander.writeRegister(MCP23017_GPPUB, 0x0f);
		//Serial.print(row);
		//Serial.print(' ');
		//Serial.println(colStat, BIN);

		for (int col = 0; col < COLS_PER_HAND; col++) {
			bool isPressed;
			key = keyMap[layer][row][col+COLS_PER_HAND];
			if (key == NULL) continue;
			isPressed = (colStat & (1 << col)) == 0;
			key->pressed(isPressed);
			key->exe();
			if (isPressed) {
				millisKeyPressed = millisNow;
			}
		}
	}
}

void initDisplay(void) {
	clearDisplays();
	leftDisplay.setTextSize(2);
	leftDisplay.setTextColor(WHITE);
	leftDisplay.setCursor(30, 25);
	leftDisplay.print("Hello");
	leftDisplay.display();
	rightDisplay.setTextSize(2);
	rightDisplay.setTextColor(WHITE);
	rightDisplay.setCursor(25, 25);
	rightDisplay.print("World!");
	rightDisplay.display();
	delay(1000);
	leftDisplay.clearDisplay();
	rightDisplay.clearDisplay();
	renderDisplays();
};

void clearDisplays(void) {
	leftDisplay.clearDisplay();
	leftDisplay.display();
	rightDisplay.clearDisplay();
	rightDisplay.display();
}

void renderDisplays(void) {
	renderLeftDisplay();
	renderRightDisplay();
}

void renderLeftDisplay(void) {
	leftDisplay.fillRect(0, 0, 128, 8, BLACK);
	leftDisplay.setTextSize(1);
	leftDisplay.setCursor(0, 0);
	leftDisplay.printf("%s", layerNames[layer]);
	if (layer != L_SELECT) {
		Key *key;
		leftDisplay.fillRect(0, 8, 128, 64 - 8, BLACK);
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 6; col++) {
				key = keyMap[layer][row][col];
				key->render(&leftDisplay, col * 21, 9 + row * 14);
			}
		}
		leftDisplay.writeFastHLine(0, 50, 127, WHITE);
		leftDisplay.writeFastVLine(104, 50, 64, WHITE);
	}
	leftDisplay.writeFastHLine(0, 8, 127, WHITE);
	leftDisplay.display();
}

void renderRightDisplay(void) {
	const char *num = "";
	const char *caps = "";
	const char *scroll = "";

	rightDisplay.clearDisplay();
	if (keyboard_leds & (1 << USB_LED_NUM_LOCK)) {
		num = "NUM";
	}
	if (keyboard_leds & (1 << USB_LED_CAPS_LOCK)) {
		caps = "CAPS";
	}
	if (keyboard_leds & (1 << USB_LED_SCROLL_LOCK)) {
		scroll = "SCROLL";
	}
	rightDisplay.setTextSize(1);
	rightDisplay.setCursor(0, 0);
	rightDisplay.printf("%3s %4s %3s", num, caps, scroll);
	rightDisplay.setCursor(0, 56);
	if (layer != L_SELECT) {
		Key *key;
		rightDisplay.fillRect(0, 8, 128, 64 - 8, BLACK);
		for (int row = 0; row < 4; row++) {
			for (int col = 6; col < 12; col++) {
				key = keyMap[layer][row][col];
				key->render(&rightDisplay, (col - 6) * 21 + 3, 9 + row * 14);
			}
		}
		rightDisplay.writeFastHLine(0, 50, 127, WHITE);
		rightDisplay.writeFastVLine(23, 50, 63, WHITE);
	}
	rightDisplay.writeFastHLine(0, 8, 127, WHITE);
	rightDisplay.display();
}
