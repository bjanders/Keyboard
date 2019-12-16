#pragma once

#include <arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


constexpr int MAX_KEYPRESS_LEN = 255;

constexpr int ROWS = 4;
constexpr int TOTAL_COLS = 12;
constexpr int COLS_PER_HAND = 6;


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
	int KeyCode();
	int Modifiers();
	void pressed(bool p); // sets the pressed state during scan
	bool isModified();    // has the state of the key changed since last scan
	virtual void render(Adafruit_SSD1306 *display, int x, int y);
	virtual void exe();
	void setBitmap(uint8_t mod, const uint8_t *bitmap);
	void setText(uint8_t mod, const char *text);
protected:
	const uint8_t *_bitmap[8];   // bitmaps for key
	const char *_text[8];		// text for key
	int modifiers;			// modifiers pressed
	int keyCode;			// key code
	int bounce;		// debounce time out, not currently used
	bool _pressed;		// is the key being pressed (after debouncing)
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

// UmlautKey is for MacOS to generate an umlaut, i.e.
// adds two dots above the key. This is adding
// command + u before the actual key.
class UmlautKey : public Key
{
	using Key::Key;
public:
	void exe();
};

// ShiftedDeadKey is like DeadKey, but will only add a space after
// the key is pressed if shift is also pressed. 
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
	void render(Adafruit_SSD1306 *display, int x, int y) override;
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
	void render(Adafruit_SSD1306 *display, int x, int y) override;
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

typedef Key *keylayer_t[ROWS][TOTAL_COLS];