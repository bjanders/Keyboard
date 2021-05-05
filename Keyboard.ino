#include <I2CDevice.h>
#include <MCP23017.h>
#include <Wire.h>
#include <usb_keyboard.h>
#include <stdint.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "Bitmap.h"
#include "Key.h"
#include "Layer.h"

// Configurable items

constexpr unsigned long screensaver_millis{ 30 * 60 * 1000 }; // 30 minutes

// Other constnts
constexpr auto usb_led_num_lock{ 0 };
constexpr auto usb_led_caps_lock{ 1 };
constexpr auto usb_led_scroll_lock{ 2 };
constexpr auto usb_led_compose{ 3 };
constexpr auto usb_led_kana{ 4 };

constexpr int screen_width{ 128 }; // OLED display width, in pixels
constexpr int screen_height{ 64 }; // OLED display height, in pixels

constexpr int oled_dc{ 14 };
constexpr int oled_cs{ 10 };
constexpr int oled_reset{ 15 };


constexpr int rowPin[]{ 0, 1, 2, 3 };
constexpr int colPin[]{ 4, 5, 6, 7, 8, 9 };


void initKeyMap(Layer *m, int layers);

int current_keymap{ 0 };

unsigned long time{ 0 };
int layer{ 0 };			// current keyboard layer
extern KeyList keyList;
extern int keySlot;			// key slot being used 0 - 5
extern int mediaKeySlot;		// media key slot being used 0 - 3
extern Layer layers[LAYERS];

int presses{ 0 };

// keyboard_keys, keyboard_consumer_keys and keyboard_modifier_keys are
// defined in usb_keyboard.h
byte mouse_keys[3]{ 0, };
byte old_mouse_keys[3]{ 0, };
byte old_keyboard_keys[6]{ 0, };
unsigned short old_keymedia_consumer_keys[4]{ 0, };
byte old_keyboard_modifier_keys{ 0 };
byte old_keyboard_leds{ 0 };
int old_layer{ 0 };
unsigned long millisKeyPressed{ 0 };
bool screenSaverOn = false;
unsigned long millisLastKeyScan{ 0 };
unsigned int usb_events{ 0 };

Adafruit_SSD1306 leftDisplay(screen_width, screen_height, &SPI, oled_dc, oled_reset, oled_cs);
Adafruit_SSD1306 rightDisplay(screen_width, screen_height, &Wire, -1);
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
	initKeyMap(layers, LAYERS);
	renderLeftDisplay();
	delay(100);
	memset(keyboard_keys, 0, sizeof(keyboard_keys));
	memset(keymedia_consumer_keys, 0, sizeof(keymedia_consumer_keys));
	keyboard_modifier_keys = 0;
	usb_keyboard_send();
	usb_keymedia_send();
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
		for (int i = 0; i < keyList.keypressListLen; i++) {
			// keyboard_keys and keyboard_modifier_keys are defined in usb_keyboard.h
			memcpy(keyboard_keys, keyList.keypressList[i].keyCodes, 6);
			keyboard_modifier_keys = keyList.keypressList[i].modifiers;
			stateChange = memcmp(keyboard_keys, old_keyboard_keys, 6) != 0 || keyboard_modifier_keys != old_keyboard_modifier_keys;
			if (stateChange) {
				//Serial.printf("Sending %d\n", usb_events++);
				printkeys();
				// send keys that are in keyboard_keys and keyboard_modifier_keys
				usb_keyboard_send();
				memcpy(old_keyboard_keys, keyboard_keys, 6);
				old_keyboard_modifier_keys = keyboard_modifier_keys;
				renderDisplays();
			}
		}
		if (memcmp(keymedia_consumer_keys, old_keymedia_consumer_keys, sizeof(keymedia_consumer_keys)) != 0) {
			usb_keymedia_send();
			memcpy(old_keymedia_consumer_keys, keymedia_consumer_keys, sizeof(keymedia_consumer_keys));
		}
		if (memcmp(mouse_keys, old_mouse_keys, sizeof(mouse_keys)) != 0) {
			Mouse.set_buttons(mouse_keys[0], mouse_keys[1], mouse_keys[2]);
			memcpy(old_mouse_keys, mouse_keys, sizeof(mouse_keys));
		}
		if (layer != old_layer || keyboard_leds != old_keyboard_leds) {
			old_layer = layer;
			old_keyboard_leds = keyboard_leds;
			renderDisplays();
		}

	}
	if (millisNow - millisKeyPressed > screensaver_millis) {
		clearDisplays();
		screenSaverOn = true;
	} else if (screenSaverOn) {
		renderDisplays();
		screenSaverOn = false;
	}
}

//void serialEvent() {
//	uint8_t serialChar = Serial.read();
//	leftDisplay.setTextSize(2);
//	leftDisplay.setCursor(25, 25);
//	leftDisplay.write(serialChar);
//	leftDisplay.display();
//}

void printkeys()
{
	Serial.printf("%d %04x  ", layer, keyboard_modifier_keys);
	for (int i{ 0 }; i < 6; ++i) {
		Serial.printf("%02x", keyboard_keys[i]);
		Serial.print(' ');
	}
	Serial.println();
}

void initPins(void)
{
	for (int row{ 0 }; row < ROWS; ++row) {
		pinMode(rowPin[row], INPUT_PULLUP);
	}

	for (int col{ 0 }; col < COLS_PER_HAND; ++col) {
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
void initKeyMap(Layer *m, int layers)
{
	for (int layer{ 1 }; layer < layers; ++layer) {
		for (int row{ 0 }; row < ROWS; ++row) {
			for (int col{ 0 }; col < TOTAL_COLS; ++col) {
				if (m[layer].keys[row][col] == NULL && layer > 0) {
					m[layer].keys[row][col] = m[layer - 1].keys[row][col];
				}
			}
		}
	}
}

void scanKeys(unsigned long millisNow)
{
	keyList.reset();

	memset(keymedia_consumer_keys, 0, sizeof(keymedia_consumer_keys));
	memset(mouse_keys, 0, sizeof(mouse_keys));
	mediaKeySlot = 0;

	// Left hand on Teensy
	for (int row{ 0 }; row < ROWS; ++row) {
		Key *key;
		pinMode(rowPin[row], OUTPUT);
		digitalWrite(rowPin[row], LOW);
		for (int col{ 0 }; col < COLS_PER_HAND; ++col) {
			int val;
			bool isPressed;
			val = digitalRead(colPin[col]);
			key = layers[layer].keys[row][col];
			if (key == NULL) continue;
			isPressed = val == LOW;
			key->setPressed(isPressed);
			key->exe();
			if (isPressed) {
				millisKeyPressed = millisNow;
			}
		}
		pinMode(row, INPUT_PULLUP);
	}

	// Right hand on MCP23017
	for (int row{ 0 }; row < ROWS; ++row) {
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

		for (int col{ 0 }; col < COLS_PER_HAND; ++col) {
			bool isPressed;
			key = layers[layer].keys[row][col+COLS_PER_HAND];
			if (key == NULL) continue;
			isPressed = (colStat & (1 << col)) == 0;
			key->setPressed(isPressed);
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
	leftDisplay.printf("%s", layers[layer].name);
	if (layer != L_SELECT) {
		Key *key;
		leftDisplay.fillRect(0, 8, 128, 64 - 8, BLACK);
		for (int row{ 0 }; row < 4; ++row) {
			for (int col{ 0 }; col < 6; ++col) {
				key = layers[layer].keys[row][col];
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
	const char *num{ "" };
	const char *caps{ "" };
	const char *scroll{ "" };

	rightDisplay.clearDisplay();
	if (keyboard_leds & (1 << usb_led_num_lock)) {
		num = "NUM";
	}
	if (keyboard_leds & (1 << usb_led_caps_lock)) {
		caps = "CAPS";
	}
	if (keyboard_leds & (1 << usb_led_scroll_lock)) {
		scroll = "SCROLL";
	}
	rightDisplay.setTextSize(1);
	rightDisplay.setCursor(0, 0);
	rightDisplay.printf("%3s %4s %3s", num, caps, scroll);
	rightDisplay.setCursor(0, 56);
	if (layer != L_SELECT) {
		Key *key;
		rightDisplay.fillRect(0, 8, 128, 64 - 8, BLACK);
		for (int row{ 0 }; row < 4; ++row) {
			for (int col{ 6 }; col < 12; ++col) {
				key = layers[layer].keys[row][col];
				key->render(&rightDisplay, (col - 6) * 21 + 3, 9 + row * 14);
			}
		}
		rightDisplay.writeFastHLine(0, 50, 127, WHITE);
		rightDisplay.writeFastVLine(23, 50, 63, WHITE);
	}
	rightDisplay.writeFastHLine(0, 8, 127, WHITE);
	rightDisplay.display();
}
