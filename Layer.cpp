#include <usb_keyboard.h>
#include "Layer.h"
#include "Bitmap.h"
#include <map>

#define SHFT MODIFIERKEY_SHIFT
#define RSHFT MODIFIERKEY_RIGHT_SHIFT
#define CTRL MODIFIERKEY_CTRL
#define RCTRL MODIFIERKEY_RIGHT_CTRL
#define ALT MODIFIERKEY_ALT
#define RALT MODIFIERKEY_RIGHT_ALT
#define GUI MODIFIERKEY_GUI
#define RGUI MODIFIERKEY_RIGHT_GUI

constexpr int L_WIN{ 0 };
constexpr int L_MAC{ 3 };
constexpr int L_GAMING{ 6 };
constexpr int L_PHOTOSHOP{ 7 };
constexpr int L_MOUSE{ 9 };

LayerKey *lk_mouse = new LayerKey(L_MOUSE);
NoKey *xxx = new NoKey();

Layer layers[LAYERS] = {
	// Layer 0
	"Windows US-Intl",
	{
		{ new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W), new Key(KEY_E), new Key(KEY_R), new Key(KEY_T), /**/ new Key(KEY_Y), new Key(KEY_U), new Key(KEY_I), new Key(KEY_O), new Key(KEY_P), new Key(RALT, KEY_Q) },
		{ new Key(SHFT, 0), new Key(KEY_A), new Key(KEY_S), new Key(KEY_D), new Key(KEY_F), new Key(KEY_G), /**/ new Key(KEY_H), new Key(KEY_J), new Key(KEY_K), new Key(KEY_L), new Key(RALT, KEY_P), new Key(RSHFT, 0) },
		{ new Key(CTRL, 0),	new Key(KEY_Z), new Key(KEY_X), new Key(KEY_C), new Key(KEY_V), new Key(KEY_B), /**/ new Key(KEY_N), new Key(KEY_M), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	new Key(GUI, 0), new LayerKey(1), new LayerKey(2), new Key(KEY_SPACE), new SelectLayerKey(L_SELECT), /**/ lk_mouse, new Key(ALT, 0), new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 1
	"Windows US-Intl 1",
	{
		{ new DeadKey(SHFT, KEY_TILDE), new Key(KEY_DELETE), new Key(KEY_HOME), new Key(KEY_UP), new Key(KEY_END), new Key(KEY_PAGE_UP), /**/ new Key(KEY_PRINTSCREEN), new Key(KEY_LEFT_BRACE), new Key(KEY_RIGHT_BRACE), new DeadKey(KEY_QUOTE), new Key(SHFT, KEY_EQUAL), new Key(RALT, KEY_W) },
		{ NULL,	new Key(KEY_ESC),new Key(KEY_LEFT),	new Key(KEY_DOWN), new Key(KEY_RIGHT), new Key(KEY_PAGE_DOWN), /**/	                      new Key(KEY_SCROLL_LOCK), new Key(SHFT, KEY_9), new Key(SHFT, KEY_0), new Key(KEY_MINUS), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_INSERT), new MouseButton(MOUSE_BUTTON_RIGHT), new MouseButton(MOUSE_BUTTON_MIDDLE), new MouseButton(MOUSE_BUTTON_LEFT), new MediaKey(KEY_MEDIA_PLAY_PAUSE), /**/               new Key(KEY_PAUSE), new Key(KEY_CAPS_LOCK), new Key(KEY_SEMICOLON), new Key(SHFT, KEY_SEMICOLON), new Key(KEY_BACKSLASH), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                            NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	// Layer 2
	"Windows US-Intl 2",
	{
		{ new DeadKey(KEY_TILDE), new Key(KEY_F9), new Key(KEY_F10), new Key(KEY_F11), new Key(KEY_F12), new MediaKey(KEY_MEDIA_VOLUME_INC), /**/ new Key(SHFT, KEY_8), new Key(KEY_7), new Key(KEY_8), new Key(KEY_9), new Key(KEY_0), xxx },
		{ NULL,	new Key(KEY_F5),new Key(KEY_F6), new Key(KEY_F7), new Key(KEY_F8), new MediaKey(KEY_MEDIA_VOLUME_DEC),	/**/                      new Key(KEY_MINUS), new Key(KEY_4), new Key(KEY_5), new ShiftedDeadKey(KEY_6), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_F1), new Key(KEY_F2), new Key(KEY_F3), new Key(KEY_F4), new MediaKey(KEY_MEDIA_MUTE), /**/                            new Key(SHFT, KEY_EQUAL), new Key(KEY_1), new Key(KEY_2), new Key(KEY_3), new Key(KEY_PERIOD), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                                NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},

	// Mac OS
	// Layer 3 = L_MAC
	"Mac",
	{
		{ new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W), new Key(KEY_E), new Key(KEY_R), new Key(KEY_T), /**/ new Key(KEY_Y), new Key(KEY_U), new Key(KEY_I), new Key(KEY_O), new Key(KEY_P), new UmlautKey(KEY_A) },
		{ new Key(SHFT, 0), new Key(KEY_A), new Key(KEY_S), new Key(KEY_D), new Key(KEY_F), new Key(KEY_G), /**/ new Key(KEY_H), new Key(KEY_J), new Key(KEY_K), new Key(KEY_L), new UmlautKey(KEY_O), new Key(RSHFT, 0) },
		{ new Key(CTRL, 0), new Key(KEY_Z), new Key(KEY_X), new Key(KEY_C), new Key(KEY_V), new Key(KEY_B), /**/ new Key(KEY_N), new Key(KEY_M), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0) },
		{ new Key(ALT, 0, mac_opt),	new Key(GUI, 0, command), new LayerKey(L_MAC + 1), new LayerKey(L_MAC + 2), new Key(KEY_SPACE), new SelectLayerKey(L_SELECT), /**/ 	 new SelectLayerKey(L_SELECT),  xxx, new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0, command), new Key(ALT, 0, mac_opt) }
	},
	// Layer 4 (L_MAC + 1)
	"Mac 1",
	{
		{ new Key(SHFT, KEY_TILDE), new Key(KEY_DELETE), new Key(KEY_HOME), new Key(KEY_UP), new Key(KEY_END), new Key(KEY_PAGE_UP), /**/             xxx, new Key(KEY_LEFT_BRACE), new Key(KEY_RIGHT_BRACE), new Key(KEY_QUOTE), new Key(SHFT, KEY_EQUAL), new Key(RALT, KEY_A) },
		{ NULL,	new Key(KEY_ESC),new Key(KEY_LEFT),	new Key(KEY_DOWN), new Key(KEY_RIGHT), new Key(KEY_PAGE_DOWN), /**/                               xxx, new Key(SHFT, KEY_9), new Key(SHFT, KEY_0), new Key(KEY_MINUS), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_INSERT), new MouseButton(MOUSE_BUTTON_RIGHT), new MouseButton(MOUSE_BUTTON_MIDDLE), new MouseButton(MOUSE_BUTTON_LEFT), new MediaKey(KEY_MEDIA_PLAY_PAUSE), /**/ xxx, xxx, new Key(KEY_SEMICOLON), new Key(SHFT, KEY_SEMICOLON), new Key(KEY_BACKSLASH), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                                    NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	// Layer 5 (L_MAC + 2)
	"Mac 2",
	{
		{ new Key(KEY_TILDE), new Key(KEY_F9), new Key(KEY_F10), new Key(KEY_F11), new Key(KEY_F12), new MediaKey(KEY_MEDIA_VOLUME_INC), /**/ new Key(SHFT, KEY_8), new Key(KEY_7), new Key(KEY_8), new Key(KEY_9), new Key(KEY_0), xxx },
		{ NULL,	new Key(KEY_F5),new Key(KEY_F6), new Key(KEY_F7), new Key(KEY_F8), new MediaKey(KEY_MEDIA_VOLUME_DEC),	/**/                  new Key(KEY_MINUS), new Key(KEY_4), new Key(KEY_5), new Key(KEY_6), new Key(KEY_EQUAL), NULL },
		{ NULL, new Key(KEY_F1), new Key(KEY_F2), new Key(KEY_F3), new Key(KEY_F4), new MediaKey(KEY_MEDIA_MUTE), /**/                        new Key(SHFT, KEY_EQUAL), new Key(KEY_1), new Key(KEY_2), new Key(KEY_3), new Key(KEY_PERIOD), NULL},
		{ NULL,	NULL, NULL,	NULL, NULL,	NULL, /**/                                                                                            NULL, NULL, NULL, new Key(KEY_BACKSPACE), NULL, NULL },
	},
	// Layer 6 = L_GAMING
	"Gaming",
	{
		{ new Key(KEY_1), new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W), new Key(KEY_E), new Key(KEY_R),  /**/ new Key(KEY_Y), new Key(KEY_U), new Key(KEY_I), new Key(KEY_O), new Key(KEY_P), new Key(RALT, KEY_Q) },
		{ new Key(KEY_2), new Key(SHFT, 0), new Key(KEY_A), new Key(KEY_S), new Key(KEY_D), new Key(KEY_F),  /**/ new Key(KEY_H), new Key(KEY_J), new Key(KEY_K), new Key(KEY_L), new Key(RALT, KEY_P), new Key(RSHFT, 0) },
		{ new Key(KEY_3), new Key(CTRL, 0),	new Key(KEY_Z), new Key(KEY_X), new Key(KEY_C), new Key(KEY_V),  /**/ new Key(KEY_N), new Key(KEY_M), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	new Key(KEY_V), new Key(KEY_SPACE), new Key(KEY_V), new Key(KEY_F1), new Key(KEY_V), /**/ new SelectLayerKey(L_SELECT), new Key(KEY_ESC),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 7 (L_PHOTOSHOP)
	"Photoshop",
	{
		{ new Key(KEY_TAB),	new Key(KEY_Q), new Key(KEY_W, ps_objselect), new Key(KEY_E, ps_eraser), new Key(KEY_R, ps_rotateview), new Key(KEY_T, ps_text), /**/ new Key(KEY_Y, ps_history), new Key(KEY_U, ps_polygon), new Key(KEY_I, ps_eyedrop), new Key(KEY_O, ps_dodge), new Key(KEY_P, ps_pen), new Key(RALT, KEY_Q) },
		{ new Key(SHFT, 0), new Key(KEY_A, ps_select), new Key(KEY_S, ps_clone), new Key(KEY_D, ps_defaultfb), new Key(KEY_F), new Key(KEY_G, ps_bucket), /**/ new Key(KEY_H, ps_hand), new Key(KEY_J, ps_healing), new Key(KEY_K, ps_frame), new Key(KEY_L, ps_lasso), new Key(RALT, KEY_P), new Key(RSHFT, 0) },
		{ new Key(CTRL, 0),	new Key(KEY_Z, ps_zoom), new Key(KEY_X, ps_switchfb), new Key(KEY_C, ps_crop), new Key(KEY_V, ps_move), new Key(KEY_B, ps_brush), /**/ new Key(KEY_N), new Key(KEY_M, ps_marquee), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	xxx, xxx, new LayerKey(L_PHOTOSHOP + 1), new Key(KEY_SPACE), new Key(KEY_RETURN), /**/ new SelectLayerKey(L_SELECT), new Key(ALT, 0),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 8 (L_PHOTOSHOP + 1)
	"Photoshop 1",
	{
		{ new Key(KEY_TAB), new Key(KEY_P, ps_pen), new Key(KEY_O, ps_dodge),new Key(KEY_I, ps_eyedrop),  new Key(KEY_U, ps_polygon),   new Key(KEY_Y, ps_history),   /**/ new Key(KEY_Y, ps_history), new Key(KEY_U, ps_polygon), new Key(KEY_I, ps_eyedrop), new Key(KEY_O, ps_dodge), new Key(KEY_P, ps_pen), new Key(RALT, KEY_Q) },
		{ new Key(SHFT, 0), new Key(KEY_A, ps_select), new Key(KEY_L, ps_lasso),    new Key(KEY_K, ps_frame),   new Key(KEY_J, ps_healing),  new Key(KEY_H, ps_hand),  /**/ new Key(KEY_H, ps_hand), new Key(KEY_J, ps_healing), new Key(KEY_K, ps_frame), new Key(KEY_L, ps_lasso), new Key(RALT, KEY_P), new Key(RSHFT, 0)  },
		{ new Key(CTRL, 0),	new Key(KEY_Z, ps_zoom), new Key(KEY_X, ps_switchfb), new Key(KEY_C, ps_crop), new Key(KEY_M, ps_marquee), new Key(KEY_B, ps_brush), /**/ new Key(KEY_N), new Key(KEY_M, ps_marquee), new Key(KEY_COMMA), new Key(KEY_PERIOD), new Key(KEY_SLASH), new Key(RCTRL, 0)},
		{ new Key(ALT, 0),	xxx, xxx, NULL, new Key(KEY_SPACE), new Key(KEY_RETURN), /**/ new SelectLayerKey(L_SELECT), new Key(ALT, 0),	new Key(KEY_RETURN), new Key(KEY_SPACE), new Key(GUI, 0), new Key(RALT, 0) }
	},
	// Layer 9: L_MOUSE
	"Mouse",
	{
		{ xxx, xxx, new MouseMove(MouseDir::NW), new MouseMove(MouseDir::N), new MouseMove(MouseDir::NE), xxx, /**/ xxx, xxx, xxx, xxx, xxx, xxx },
		{ xxx, xxx, new MouseMove(MouseDir::W), new MouseMove(MouseDir::S), new MouseMove(MouseDir::E), new MouseScroll(1, 50), /**/ xxx, new MouseSpeed(5), new MouseSpeed(15), new MouseSpeed(1), xxx, xxx },
		{ xxx, xxx, new MouseMove(MouseDir::SW), new MouseMove(MouseDir::S), new MouseMove(MouseDir::SE), new MouseScroll(-1, 50), /**/ xxx, xxx, xxx, xxx, xxx, xxx },
		{ NULL, NULL, new MouseButton(MOUSE_BUTTON_LEFT), NULL, NULL, NULL, /**/ lk_mouse, NULL, NULL, NULL, NULL, NULL }
	},
	// Layer 10: L_SELECT
	"Select layer",
	{
		{ NULL, NULL, NULL, NULL, NULL, NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, new LockLayerKey(L_WIN), new LockLayerKey(L_MAC), new LockLayerKey(L_GAMING), new LockLayerKey(L_PHOTOSHOP), NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL },
		{ NULL, NULL, NULL, NULL, NULL, NULL, /**/ NULL, NULL, NULL, NULL, NULL, NULL }
	},
	// LAYERS = 11
};
