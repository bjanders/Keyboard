#include "I2CDevice.h"
#include "MCP23017.h"
#include <Wire.h>
#include <usb_keyboard.h>
#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "Key.h"

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

const int LAYERS = 4;
const int ROWS = 4;
const int TOTAL_COLS = 12;
const int COLS_PER_HAND = 6;

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

Key *keyMap[LAYERS][ROWS][TOTAL_COLS] = {
	{
		{ new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W), new Key(KEY_E), new Key(KEY_R), new Key(KEY_T), /**/ new Key(KEY_Y), new Key(KEY_U), new Key(KEY_I), new Key(KEY_O), new Key(KEY_P), new Key(RALT, KEY_Q) },
		{ new Key(SHFT, 0), new Key(KEY_A), new Key(KEY_S), new Key(KEY_D), new Key(KEY_F), new Key(KEY_G), /**/ new Key(KEY_H), new Key(KEY_J), new Key(KEY_K), new Key(KEY_L), new Key(RALT, KEY_P), new Key(RSHFT, 0) },
		{ new Key(CTRL, 0),	new Key(KEY_Z), new Key(KEY_X), new Key(KEY_C), new Key(KEY_V), new Key(KEY_B), /**/ new Key(KEY_N), new Key(KEY_M), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	new LayerKey(2), new LayerKey(1), new LayerKey(3), new LockLayerKey(1), new Key(CTRL, KEY_B), /**/ 	new Key(RGUI, 0), new Key(ALT, 0),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	{
		{ new DeadKey(SHFT, KEY_TILDE), new Key(KEY_DELETE), new Key(KEY_HOME), new Key(KEY_UP), new Key(KEY_END), new Key(KEY_PAGE_UP), /**/ NULL, new Key(KEY_LEFT_BRACE), new Key(KEY_RIGHT_BRACE), new DeadKey(KEY_QUOTE), new Key(SHFT, KEY_EQUAL), new Key(RALT, KEY_W) },
		{ NULL,	new Key(KEY_ESC),new Key(KEY_LEFT),	new Key(KEY_DOWN), new Key(KEY_RIGHT), new Key(KEY_PAGE_DOWN), /**/ NULL, new Key(SHFT, KEY_9), new Key(SHFT, KEY_0), new Key(KEY_MINUS), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_INSERT), new Key(KEY_PRINTSCREEN), new Key(KEY_SCROLL_LOCK), new Key(KEY_PAUSE), new MediaKey(KEY_MEDIA_PLAY_PAUSE), /**/ NULL, NULL, new Key(KEY_SEMICOLON), new Key(SHFT, KEY_SEMICOLON), new Key(KEY_BACKSLASH), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/ NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	{
		{ new DeadKey(KEY_TILDE), new Key(KEY_F9), new Key(KEY_F10), new Key(KEY_F11), new Key(KEY_F12), new MediaKey(KEY_MEDIA_VOLUME_INC), /**/ NULL, new Key(KEY_7), new Key(KEY_8), new Key(KEY_9), new Key(KEY_0), new Key(CTRL | ALT, KEY_DELETE) },
		{ NULL,	new Key(KEY_F5),new Key(KEY_F6), new Key(KEY_F7), new Key(KEY_F8), new MediaKey(KEY_MEDIA_VOLUME_DEC),	/**/ NULL, new Key(KEY_4), new Key(KEY_5), new ShiftedDeadKey(KEY_6), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_F1), new Key(KEY_F2), new Key(KEY_F3), new Key(KEY_F4), new MediaKey(KEY_MEDIA_MUTE), /**/ NULL, new Key(KEY_1), new Key(KEY_2), new Key(KEY_3), new Key(KEY_PERIOD), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/ NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	{
		{ new Key(KEY_NUM_LOCK), NULL, NULL, NULL, NULL, NULL, /**/ NULL, new Key(SHFT, KEY_7), new Key(SHFT, KEY_8), new Key(SHFT, KEY_9), new Key(SHFT, KEY_0), new Key(CTRL | ALT, KEY_DELETE) },
		{ new Key(KEY_CAPS_LOCK), NULL, NULL, NULL, NULL, NULL, /**/ NULL, new Key(SHFT, KEY_4), new Key(SHFT, KEY_5), new ShiftedDeadKey(SHFT, KEY_6), new Key(SHFT, KEY_EQUAL), NULL },
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/ NULL, new Key(SHFT, KEY_1), new Key(SHFT, KEY_2), new Key(SHFT, KEY_3), new Key(KEY_PERIOD), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/ NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	}
};

#undef SHFT
#undef CTRL
#undef ALT
#undef RALT

unsigned long time = 0;
int layer = 0;
int keySlot = 0;
int mediaKeySlot = 0;
int presses = 0;

byte old_keyboard_keys[6] = { 0, };
unsigned short old_keymedia_consumer_keys[4] = { 0, };
byte old_keyboard_modifier_keys = 0;
byte old_keyboard_leds = 0;
int old_layer = 0;
unsigned long millisKeyPressed = 0;
bool screenSaverOn = false;
unsigned long millisLastKeyScan = 0;

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
	Serial.println("Hello");
	initDisplay();
	initPins();
	initKeyMap();
	renderLeftDisplay();
	delay(100);
}

void loop()
{	
	unsigned long millisNow = millis();
	if (millisNow - millisLastKeyScan > 10) {
		scanKeys(millisNow);
		millisLastKeyScan = millisNow;
		bool stateChange;
		stateChange = memcmp(keyboard_keys, old_keyboard_keys, 6) != 0 || keyboard_modifier_keys != old_keyboard_modifier_keys;

		// redraw the display if any of the following has changed:
		// - modifier keys (shift, ctrl, alt etc.)
		// - keyboard leds (num lock, caps lock, scroll lock)
		// - keyboard layer
		if (keyboard_modifier_keys != old_keyboard_modifier_keys || layer != old_layer || keyboard_leds != old_keyboard_leds) {
			old_layer = layer;
			old_keyboard_leds = keyboard_leds;
			renderDisplays();
		}

		if (stateChange) {
			usb_keyboard_send();
			memcpy(old_keyboard_keys, keyboard_keys, 6);
			old_keyboard_modifier_keys = keyboard_modifier_keys;
		}
		if (memcmp(keymedia_consumer_keys, old_keymedia_consumer_keys, sizeof(keymedia_consumer_keys)) != 0) {
			usb_keymedia_send();
			memcpy(old_keymedia_consumer_keys, keymedia_consumer_keys, sizeof(keymedia_consumer_keys));
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
	//	resetDisplay();
	//	display.setTextSize(2);
	//	display.setCursor(25, 25);
	//	printChar(serialChar);
	//}
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
	//Wire.write(0xff);
	Wire.endTransmission();
	// Set pullup on A0-A6
	Wire.beginTransmission(MCP23017_ADDR);
	Wire.write(MCP23017_GPPUA);
	Wire.write(0x7f); // A0-A6
	// pullup on GPPUB B0-B3
	Wire.write(0x0f); // B0-B3
	Wire.endTransmission();
}

// Sends a reset to the right display using the port expander
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

// Copies the keys from the previous lower layer if a key in the 
// current layer is set to NULL
void initKeyMap(void)
{
	for (int layer = 1; layer < LAYERS; layer++) {
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < TOTAL_COLS; col++) {
				if (keyMap[layer][row][col] == NULL) {
					keyMap[layer][row][col] = keyMap[layer - 1][row][col];
				}
			}
		}
	}
}

void scanKeys(unsigned long millisNow)
{
	keyboard_modifier_keys = 0;
	for (int i = 0; i < 6; i++) {
		keyboard_keys[i] = 0;
	}
	for (int i = 0; i < 4; i++) {
		keymedia_consumer_keys[i] = 0;
	}
	mediaKeySlot = 0;
	keySlot = 0;

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
	renderDisplays();
};

void clearDisplays(void) {
	leftDisplay.clearDisplay();
	leftDisplay.display();
	rightDisplay.clearDisplay();
	rightDisplay.display();
}

//void printChar(byte c) {
//	leftDisplay.write(c);
//	leftDisplay.display();
//}
//
//void testdrawchar(void) {
//	// Not all the characters will fit on the display. This is normal.
//	// Library will draw what it can and the rest will be clipped.
//	leftDisplay.setCursor(0, 0);
//	for (byte i = 0; i < 50; i++) {
//		if (i == '\n') leftDisplay.write(' ');
//		else          leftDisplay.write(i);
//	}
//
//	leftDisplay.display();
//}


void renderDisplays(void) {
	renderLeftDisplay();
	renderRightDisplay();
}

void renderLeftDisplay(void) {
	const char *num = "";
	const char *caps = "";
	const char *scroll = "";
	const char *shift = "";
	const char *alt = "";
	const char *ctrl = "";
	const char *gui = "";

	leftDisplay.clearDisplay();
	if (keyboard_leds & (1 << USB_LED_NUM_LOCK)) {
		num = "NUM";
	}
	if (keyboard_leds & (1 << USB_LED_CAPS_LOCK)) {
		caps = "CAPS";
	}
	if (keyboard_leds & (1 << USB_LED_SCROLL_LOCK)) {
		scroll = "SCROLL";
	}
	leftDisplay.setTextSize(1);
	leftDisplay.setCursor(0, 0);
	leftDisplay.printf("%3s %4s %3s", num, caps, scroll);
//	display.printf("%d", renders++);
	leftDisplay.setCursor(0, 56);
	//display.printf("%x", keyboard_modifier_keys);
	if (keyboard_modifier_keys & MODIFIERKEY_SHIFT) {
		shift = "SHIFT";
	}
	if (keyboard_modifier_keys & MODIFIERKEY_CTRL) {
		ctrl = "CTRL";
	}
	if (keyboard_modifier_keys & MODIFIERKEY_ALT) {
		alt = "ALT";
	}
	if (keyboard_modifier_keys & MODIFIERKEY_GUI) {
		gui = "GUI";
	}
	leftDisplay.printf("%5s %4s %3s %3s L%d", shift, ctrl, alt, gui, layer);
	leftDisplay.display();
}

void renderRightDisplay(void) {
	const char *num = "";
	const char *caps = "";
	const char *scroll = "";
	const char *shift = "";
	const char *alt = "";
	const char *ctrl = "";
	const char *gui = "";

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
	//	display.printf("%d", renders++);
	rightDisplay.setCursor(0, 56);
	//display.printf("%x", keyboard_modifier_keys);
	if (keyboard_modifier_keys & MODIFIERKEY_RIGHT_SHIFT) {
		shift = "SHIFT";
	}
	if (keyboard_modifier_keys & MODIFIERKEY_RIGHT_CTRL) {
		ctrl = "CTRL";
	}
	if (keyboard_modifier_keys & MODIFIERKEY_RIGHT_ALT) {
		alt = "ALT";
	}
	if (keyboard_modifier_keys & MODIFIERKEY_RIGHT_GUI) {
		alt = "GUI";
	}
	rightDisplay.printf("%5s %4s %3s %3s L%d", shift, ctrl, alt, gui, layer);
	rightDisplay.display();
}
