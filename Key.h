// Key.h

#ifndef _KEY_h
#define _KEY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


const int MAX_KEYPRESS_LEN = 255;

typedef struct {
	byte modifiers;
	byte keys[6];
	byte slot;
} keypress_t;

extern keypress_t keypress_list[MAX_KEYPRESS_LEN];
extern int keypress_list_len;

// Key is for normal keys
class Key
{
public:
	Key();
	Key(int key);
	Key(int mod, int key);
	int kc();
	int mod();
	void pressed(bool p);
	bool ismodified();
	virtual void exe();
protected:
	keypress_t * initkeylist();
	int _mod;			// modifiers pressed
	int _key;			// key code
	int _bounce;		// debounce time out, not currently used
	bool _pressed;		// is the key being pressed (after debouncing)
	bool _modified;		// has the state of the key changed since last scan
	int _presscount;	// how many times has the key been pressed, for statistics & debugging
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
protected:
	int _layer;
	int _old_layer;
};

// LockLayerKey changes layer and stays in that layer even after the key is released
class LockLayerKey : public LayerKey
{
	using LayerKey::LayerKey;
public:
	void exe() override;
};

// MediaKey is a media key, like volume up and down
class MediaKey : public Key
{
public:
	MediaKey(int key);
	void exe() override;
};
#endif