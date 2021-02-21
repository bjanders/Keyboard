# Keyboard
Arduino based split keyboard with 2 * 24 keys and two OLED displays

This uses the Teensyduino library. To make the keyboard code compile you have to make the `usb_keymedia_send()` public in the Teensyduino library.

In `usb_keyboard.h`:

   #ifdef KEYMEDIA_INTERFACE
   int usb_keymedia_send(void);
   extern uint16_t keymedia_consumer_keys[4];
   extern uint8_t keymedia_system_keys[3];
   #endif

And remove `static` from `usb_keymedia_send()` in `usb_keyboard.c` 
