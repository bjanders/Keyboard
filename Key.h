#pragma once

#include <arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


constexpr int MAX_KEYPRESS_LEN = 255;

constexpr int ROWS = 4;
constexpr int TOTAL_COLS = 12;
constexpr int COLS_PER_HAND = 6;
enum {
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT
};


typedef struct {
	uint8_t modifiers;
	uint8_t keyCodes[6];
	uint8_t keyIndex;       // current index in keyCodes array
} keypress_t;

// Key is for normal keys
class Key
{
public:
	Key();
	Key(int key);
	Key(int mod, int key);
	Key(int mod, int key, const uint8_t *bitmap);
	Key(int key, const uint8_t *bitmap);
	int KeyCode() const { return keyCode; }
	int Modifiers() const { return modifiers; }
	void setPressed(bool p); // sets the pressed state during scan
	bool isModified() const { return modified; }    // has the state of the key changed since last scan
	virtual void render(Adafruit_SSD1306 *display, int x, int y) const;
	virtual void exe();
	void setBitmap(uint8_t mod, const uint8_t *bitmap);
	void setText(uint8_t mod, const char *text);
protected:
	const uint8_t *bitmaps[8];   // bitmaps for key
	const char *texts[8];		// text for key
	int modifiers;			// modifiers pressed
	int keyCode;			// key code
	int bounce;		// debounce time out, not currently used
	bool pressed;		// is the key being pressed (after debouncing)
	bool modified;		// has the state of the key changed since last scan
	int pressCount;	// how many times has the key been pressed, for statistics & debugging
};

// DeadKey automatically adds a space after the key is pressed so that
// a dead key does not seem dead
class DeadKey : public Key
{
	using Key::Key;
public:
	void exe();
};

// UmlautKey is for MacOS to generate an umlaut, i.e.,
// adds two dots above the character. This is done by sending
// command + u before the actual key.
class UmlautKey : public Key
{
	using Key::Key;
public:
	void exe();
};

// ShiftedDeadKey is like DeadKey, but will only add a space after
// the key is pressed if shift is also pressed. The purpose of this is,
// for example, when you want to press the key '6', and you there is a dead
// key when you press Shift-6. This is the case for the US Interntional layout.
// So normally you would only send '6', but when pressing Shift-6, you need to
// send a space after it.
class ShiftedDeadKey : public Key
{
	using Key::Key;
public:
	void exe();
};

// LayerKey changes layer while pressed
class LayerKey : public Key
{
public:
	LayerKey(int layer);
	void exe() override;
	void render(Adafruit_SSD1306 *display, int x, int y) const override;
protected:
	int _layer;
	int oldLayer;
};

// LockLayerKey changes layer and stays in that layer even after the key is released
class LockLayerKey : public LayerKey
{
	using LayerKey::LayerKey;
public:
	void exe() override;
};

class SelectLayerKey : public LockLayerKey
{
	using LockLayerKey::LockLayerKey;
public:
	void exe();
};

// NoKey does not send or do anything.
class NoKey : public Key
{
public:
	NoKey() {};
};

// MediaKey is a media key, like volume up and down
class MediaKey : public Key
{
public:
	MediaKey(int key);
	void exe() override;
	void render(Adafruit_SSD1306 *display, int x, int y) const override;
};


class MouseKey : public Key
{
public:
	MouseKey(int button);
	void exe() override;
	void render(Adafruit_SSD1306 *display, int x, int y) const override;
protected:
	int mouseButton;
};


class KeyList
{
public:
	KeyList();
	void reset();
	keypress_t *currentKey();
	// A list of keys sent in sequence
	keypress_t keypressList[MAX_KEYPRESS_LEN];
	// number of keys in the list
	int keypressListLen;
};