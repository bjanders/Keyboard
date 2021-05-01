#pragma once

const uint8_t capslock[] PROGMEM = { // 'caps', 20x13px
0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xe0, 0x00, 0x01, 0xf0, 0x00, 0x03, 0xf8, 0x00, 0x07,
0xfc, 0x00, 0x01, 0xf0, 0x00, 0x01, 0xf0, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0,
0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00 };
const uint8_t ctrl[] PROGMEM = { // 'ctrl', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x40, 0x40, 0x22, 0x40, 0x40, 0x20,
0xeb, 0x40, 0x20, 0x4c, 0x40, 0x20, 0x48, 0x40, 0x22, 0x48, 0x40, 0x1e, 0x48, 0x40, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t wingui[] PROGMEM = { // 'gui2', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xbc, 0x00, 0x07, 0xbc, 0x00, 0x07, 0xbc, 0x00, 0x07,
0xbc, 0x00, 0x00, 0x00, 0x00, 0x07, 0xbc, 0x00, 0x07, 0xbc, 0x00, 0x07, 0xbc, 0x00, 0x07, 0xbc,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t mute[] PROGMEM = { // 'mute', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x03, 0x80, 0x00, 0x1f, 0x91, 0x00, 0x1f,
0x8a, 0x00, 0x1f, 0x84, 0x00, 0x1f, 0x8a, 0x00, 0x1f, 0x91, 0x00, 0x03, 0x80, 0x00, 0x01, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t pagedown[] PROGMEM = { // 'pagedown', 20x13px
0x00, 0x40, 0x00, 0x07, 0xf0, 0x00, 0x04, 0x58, 0x00, 0x04, 0x5c, 0x00, 0x04, 0x44, 0x00, 0x04,
0x44, 0x00, 0x05, 0xf4, 0x00, 0x04, 0xe4, 0x00, 0x04, 0x44, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04,
0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00 };
const uint8_t pageup[] PROGMEM = { // 'pageup', 20x13px
0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x04, 0x18, 0x00, 0x04, 0x1c, 0x00, 0x04, 0x04, 0x00, 0x04,
0x44, 0x00, 0x04, 0xe4, 0x00, 0x05, 0xf4, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44, 0x00, 0x04, 0x44,
0x00, 0x07, 0xfc, 0x00, 0x00, 0x40, 0x00 };
const uint8_t playpause[] PROGMEM = { // 'playpause', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0xa0, 0x00, 0x0d, 0xb0, 0x00, 0x0d, 0xb8, 0x00, 0x0d,
0xbc, 0x00, 0x0d, 0xbe, 0x00, 0x0d, 0xbc, 0x00, 0x0d, 0xb8, 0x00, 0x0d, 0xb0, 0x00, 0x0d, 0xa0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t enter[] PROGMEM = { // 'return', 20x13px
0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x02,
0x07, 0x00, 0x06, 0x0f, 0x00, 0x0f, 0xff, 0x00, 0x1f, 0xfe, 0x00, 0x0f, 0xfc, 0x00, 0x06, 0x00,
0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t shift[] PROGMEM = { // 'shift', 20x13px
0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xa0, 0x00, 0x01, 0x10, 0x00, 0x02, 0x08, 0x00, 0x06,
0x0c, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10,
0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00 };
const uint8_t space[] PROGMEM = { // 'space', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x01, 0xc0, 0x20, 0x00, 0x40, 0x20, 0x00, 0x40, 0x20,
0x00, 0x40, 0x20, 0x00, 0x40, 0x20, 0x00, 0x40, 0x20, 0x00, 0x40, 0x20, 0x00, 0x40, 0x38, 0x01,
0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t tab[] PROGMEM = { // 'tab', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40, 0x00, 0x0c, 0x40, 0x00, 0x0e, 0x40, 0x00,
0x0f, 0x40, 0x3f, 0xff, 0xc0, 0x00, 0x0f, 0x40, 0x00, 0x0e, 0x40, 0x00, 0x0c, 0x40, 0x00, 0x08,
0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t voldown[] PROGMEM = { // 'voldown', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x03, 0x80, 0x00, 0x1f, 0x90, 0x00, 0x1f,
0x88, 0x00, 0x1f, 0x88, 0x00, 0x1f, 0x88, 0x00, 0x1f, 0x90, 0x00, 0x03, 0x80, 0x00, 0x01, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t volup[] PROGMEM = { // 'volup', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0x00, 0x03, 0x84, 0x80, 0x1f, 0x92, 0x80, 0x1f,
0x8a, 0x80, 0x1f, 0x8a, 0x80, 0x1f, 0x8a, 0x80, 0x1f, 0x92, 0x80, 0x03, 0x84, 0x80, 0x01, 0x81,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t backspace[] PROGMEM = { // 'backspace', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x03, 0xff, 0x80, 0x07, 0xdd, 0x80, 0x0f,
0xeb, 0x80, 0x1f, 0xf7, 0x80, 0x0f, 0xeb, 0x80, 0x07, 0xdd, 0x80, 0x03, 0xff, 0x80, 0x01, 0xff,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t altgr[] PROGMEM = { // 'altgr', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x8c, 0x00, 0x95, 0xd2, 0x00, 0x94,
0x90, 0xb0, 0xf4, 0x90, 0xc0, 0x94, 0x96, 0x80, 0x94, 0x92, 0x80, 0x94, 0x8c, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// Mouse buttons
const uint8_t mouseleft[] PROGMEM = { // 'mouseleft', 20x13px
0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x03, 0x28, 0x00, 0x07, 0x24, 0x00, 0x07, 0x24, 0x00, 0x07,
0x24, 0x00, 0x07, 0xfc, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04,
0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00 };
const uint8_t mousemiddle[] PROGMEM = { // 'mousemiddle', 20x13px
0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x02, 0xe8, 0x00, 0x04, 0xe4, 0x00, 0x04, 0xe4, 0x00, 0x04,
0xe4, 0x00, 0x07, 0xfc, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04,
0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00 };
const uint8_t mouseright[] PROGMEM = {  // 'mouseright', 20x13px
0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x02, 0x98, 0x00, 0x04, 0x9c, 0x00, 0x04, 0x9c, 0x00, 0x04,
0x9c, 0x00, 0x07, 0xfc, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04, 0x00, 0x04, 0x04,
0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00 };

// Mac
const uint8_t command[] PROGMEM = {// 'command', 20x13px
0x00, 0x00, 0x00, 0x06, 0x0e, 0x00, 0x09, 0x12, 0x00, 0x09, 0x12, 0x00, 0x07, 0xfc, 0x00, 0x01,
0x10, 0x00, 0x01, 0x10, 0x00, 0x01, 0x10, 0x00, 0x07, 0xfc, 0x00, 0x09, 0x12, 0x00, 0x09, 0x12,
0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00 };
const uint8_t mac_opt[] PROGMEM = { // 'macopt', 20x13px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3f, 0x00, 0x01,
0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x40, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// Photoshop

const uint8_t ps_crop[] PROGMEM = { // 'crop', 20x13px
0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x36, 0xfe, 0x00, 0x36, 0xfe, 0x00, 0x06, 0x06, 0x00, 0x06,
0x06, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x00, 0x07, 0xf6, 0xc0, 0x07, 0xf6,
0xc0, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00 };
const uint8_t ps_lasso[] PROGMEM = { // 'lasso', 20x13px
0x01, 0xf0, 0x00, 0x06, 0x0e, 0x00, 0x08, 0x01, 0x00, 0x10, 0x00, 0x80, 0x20, 0x00, 0x80, 0x40,
0x00, 0x80, 0x40, 0x00, 0x80, 0x4c, 0x01, 0x00, 0x52, 0x02, 0x00, 0x3a, 0x0c, 0x00, 0x17, 0xf0,
0x00, 0x0a, 0x00, 0x00, 0x02, 0x00, 0x00 };
const uint8_t ps_marquee[] PROGMEM = { // 'marquee', 20x13px
0x1c, 0xf3, 0x80, 0x10, 0x00, 0x80, 0x10, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
0x00, 0x80, 0x10, 0x00, 0x80, 0x10, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
0x80, 0x10, 0x00, 0x80, 0x1c, 0xf3, 0x80 };
const uint8_t ps_move[] PROGMEM = { // 'move', 20x13px
0x00, 0x40, 0x00, 0x00, 0xe0, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x40, 0x00, 0x04, 0x44, 0x00, 0x0c,
0x46, 0x00, 0x1f, 0xff, 0x00, 0x0c, 0x46, 0x00, 0x04, 0x44, 0x00, 0x00, 0x40, 0x00, 0x01, 0xf0,
0x00, 0x00, 0xe0, 0x00, 0x00, 0x40, 0x00 };
const uint8_t ps_objselect[] PROGMEM = { // 'objselect', 20x13px
0x00, 0x00, 0x00, 0x05, 0x54, 0x00, 0x00, 0x00, 0x00, 0x05, 0xf4, 0x00, 0x01, 0xf0, 0x00, 0x05,
0x84, 0x00, 0x01, 0xa0, 0x00, 0x05, 0xb0, 0x00, 0x00, 0x38, 0x00, 0x05, 0x3c, 0x00, 0x00, 0x3e,
0x00, 0x00, 0x3e, 0x00, 0x00, 0x38, 0x00 };
const uint8_t ps_brush[] PROGMEM = { // 'brush', 20x13px
0x00, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x38, 0x00, 0x00,
0x78, 0x00, 0x00, 0x30, 0x00, 0x01, 0x80, 0x00, 0x03, 0xc0, 0x00, 0x07, 0xc0, 0x00, 0x07, 0x80,
0x00, 0x0f, 0x00, 0x00, 0x1c, 0x00, 0x00 };
const uint8_t ps_hand[] PROGMEM = { // 'hand', 20x13px
0x00, 0x40, 0x00, 0x01, 0x6c, 0x00, 0x03, 0x6c, 0x00, 0x03, 0x6c, 0x80, 0x03, 0x6c, 0x80, 0x33,
0x6d, 0x80, 0x3b, 0xff, 0x00, 0x1f, 0xff, 0x00, 0x0f, 0xff, 0x00, 0x07, 0xfe, 0x00, 0x03, 0xfc,
0x00, 0x01, 0xfc, 0x00, 0x00, 0xf8, 0x00 };
const uint8_t ps_frame[] PROGMEM = { // 'frame', 20x13px
0x30, 0x01, 0x80, 0x3f, 0xff, 0x80, 0x14, 0x05, 0x00, 0x12, 0x09, 0x00, 0x11, 0x11, 0x00, 0x10,
0xa1, 0x00, 0x10, 0x41, 0x00, 0x10, 0xa1, 0x00, 0x11, 0x11, 0x00, 0x12, 0x09, 0x00, 0x14, 0x05,
0x00, 0x3f, 0xff, 0x80, 0x30, 0x01, 0x80 };
const uint8_t ps_eyedrop[] PROGMEM = { // 'eyedrop', 20x13px
0x00, 0x07, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x7c, 0x00, 0x00,
0xbe, 0x00, 0x01, 0x1c, 0x00, 0x02, 0x28, 0x00, 0x04, 0x40, 0x00, 0x08, 0x80, 0x00, 0x11, 0x00,
0x00, 0x12, 0x00, 0x00, 0x0c, 0x00, 0x00 };
const uint8_t ps_healing[] PROGMEM = { // 'healing', 20x13px
0x00, 0x08, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x6f, 0x00, 0x00, 0xf6, 0x00, 0x01,
0x58, 0x00, 0x03, 0xf8, 0x00, 0x03, 0x50, 0x00, 0x0d, 0xe0, 0x00, 0x1e, 0xc0, 0x00, 0x0f, 0x00,
0x00, 0x07, 0x00, 0x00, 0x02, 0x00, 0x00 };
const uint8_t ps_clone[] PROGMEM = { // 'clone', 20x13px
0x00, 0x70, 0x00, 0x00, 0xf8, 0x00, 0x01, 0xfc, 0x00, 0x01, 0xfc, 0x00, 0x00, 0xf8, 0x00, 0x00,
0x70, 0x00, 0x00, 0x70, 0x00, 0x00, 0x70, 0x00, 0x01, 0xfc, 0x00, 0x07, 0xff, 0x00, 0x07, 0xff,
0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00 };  
const uint8_t ps_history[] PROGMEM = { // 'history brush', 20x13px
0x00, 0x03, 0x00, 0x01, 0xe6, 0x00, 0x0a, 0x0e, 0x00, 0x1c, 0x1c, 0x00, 0x3e, 0x39, 0x00, 0x00,
0x78, 0x00, 0x00, 0x31, 0x00, 0x01, 0x80, 0x00, 0x03, 0xc2, 0x00, 0x07, 0xc0, 0x00, 0x07, 0x88,
0x00, 0x0f, 0x00, 0x00, 0x1c, 0x00, 0x00 };
const uint8_t ps_eraser[] PROGMEM = { // 'eraser', 20x13px
0x00, 0x08, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x7f, 0x00, 0x00, 0xff, 0x00, 0x01,
0xfe, 0x00, 0x02, 0xfc, 0x00, 0x04, 0x78, 0x00, 0x08, 0x30, 0x00, 0x04, 0x20, 0x00, 0x02, 0x40,
0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00 };
const uint8_t ps_bucket[] PROGMEM = { // 'bucket', 20x13px
0x01, 0x80, 0x00, 0x01, 0x50, 0x00, 0x01, 0x28, 0x00, 0x00, 0xe4, 0x00, 0x00, 0xb2, 0x00, 0x01,
0x21, 0x00, 0x02, 0x00, 0x80, 0x04, 0x01, 0x40, 0x02, 0x02, 0x60, 0x01, 0x04, 0xe0, 0x00, 0x88,
0x40, 0x00, 0x50, 0x00, 0x00, 0x20, 0x00 };
const uint8_t ps_dodge[] PROGMEM = { // 'dodge', 20x13px
0x00, 0x38, 0x00, 0x00, 0xfc, 0x00, 0x01, 0xfe, 0x00, 0x03, 0xff, 0x00, 0x03, 0xff, 0x00, 0x03,
0xff, 0x00, 0x03, 0xff, 0x00, 0x01, 0xfe, 0x00, 0x03, 0xfc, 0x00, 0x06, 0x78, 0x00, 0x0c, 0x00,
0x00, 0x18, 0x00, 0x00, 0x30, 0x00, 0x00 };
const uint8_t ps_pen[] PROGMEM = { // 'pen', 20x13px
0x00, 0x08, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x3e, 0x00, 0x00, 0xcf, 0x00, 0x03, 0x06, 0x00, 0x04,
0x04, 0x00, 0x04, 0x88, 0x00, 0x08, 0xc8, 0x00, 0x09, 0x10, 0x00, 0x0a, 0x10, 0x00, 0x0c, 0x60,
0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00 };
const uint8_t ps_text[] PROGMEM = { // 'text', 20x13px
0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x07, 0xfe, 0x00, 0x06, 0x66, 0x00, 0x00, 0x60, 0x00, 0x00,
0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x01, 0xf8,
0x00, 0x01, 0xf8, 0x00, 0x00, 0x00, 0x00 };
const uint8_t ps_select[] PROGMEM = { // 'select', 20x13px
0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x80, 0x00, 0x03, 0xc0, 0x00, 0x03, 0xe0, 0x00, 0x03,
0xf0, 0x00, 0x03, 0xf8, 0x00, 0x03, 0xfc, 0x00, 0x03, 0xe0, 0x00, 0x03, 0x70, 0x00, 0x02, 0x30,
0x00, 0x00, 0x38, 0x00, 0x00, 0x18, 0x00 };
const uint8_t ps_polygon[] PROGMEM = { // 'polygon', 20x13px
0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x02, 0x04, 0x00, 0x04, 0x02, 0x00, 0x0c, 0x03, 0x00, 0x08,
0x01, 0x00, 0x18, 0x01, 0x80, 0x08, 0x01, 0x00, 0x0c, 0x03, 0x00, 0x04, 0x02, 0x00, 0x02, 0x04,
0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00 };
const uint8_t ps_zoom[] PROGMEM = { // 'zoom', 20x13px
0x01, 0xc0, 0x00, 0x06, 0x30, 0x00, 0x08, 0x08, 0x00, 0x08, 0xc8, 0x00, 0x10, 0x24, 0x00, 0x10,
0x14, 0x00, 0x10, 0x04, 0x00, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x06, 0x3c, 0x00, 0x01, 0xce,
0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0x00 };
const uint8_t ps_switchfb[] PROGMEM = { // 'switchfb', 20x13px
0x00, 0x00, 0x00, 0xfe, 0x08, 0x00, 0xfe, 0x18, 0x00, 0xfe, 0x3f, 0x80, 0xfe, 0xd8, 0x80, 0xfe,
0x48, 0x80, 0xfe, 0x40, 0x80, 0xfe, 0x43, 0xe0, 0x00, 0x41, 0xc0, 0x10, 0x40, 0x80, 0x1f, 0xc0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t ps_defaultfb[] PROGMEM = { // 'defaultfb', 20x13px
0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x07, 0xf0, 0x00, 0x07, 0xf0, 0x00, 0x07, 0xf6, 0x00, 0x07,
0xf2, 0x00, 0x07, 0xf2, 0x00, 0x07, 0xf2, 0x00, 0x00, 0x02, 0x00, 0x00, 0x82, 0x00, 0x00, 0xfe,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t ps_rotateview[] PROGMEM = { // 'rotate', 20x13px
0x00, 0xe0, 0x00, 0x03, 0x34, 0x00, 0x04, 0x0e, 0x00, 0x00, 0x1f, 0x00, 0x01, 0x00, 0x00, 0x05,
0x46, 0x00, 0x05, 0x57, 0x00, 0x05, 0x57, 0x80, 0x27, 0xd7, 0x00, 0x17, 0xe6, 0x00, 0x1f, 0xec,
0x00, 0x0f, 0xc8, 0x00, 0x07, 0x80, 0x00 };