// Key.h

#ifndef _KEY_h
#define _KEY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Keyboard.h>


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
	int _mod;
	int _key;
	int _bounce;
	bool _pressed;
	bool _modified;
	int _presscount;
};

class DeadKey : public Key
{
	using Key::Key;
public:
	void exe();
};

class ShiftedDeadKey : public Key
{
	using Key::Key;
public:
	void exe();
};

class LayerKey : public Key
{
public:
	LayerKey(int layer);
	void exe() override;
protected:
	int _layer;
	int _old_layer;
};

class LockLayerKey : public LayerKey
{
	using LayerKey::LayerKey;
public:
	void exe() override;
};

class MediaKey : public Key
{
public:
	MediaKey(int key);
	void exe() override;
};
#endif

