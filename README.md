# PlaybackGame
IoT project using an Arduino Uno

### Goal:
* understand LED output
* understand pushbutton input
* understand piezo buzzer output

### Idea:
* red, yellow, green LEDs each with a corresponding pushbutton
* program plays random LED sequence of length 5 and then listened for 5 pushbutton inputs
* the the sequence is matched correctly a high tone will buzz, otherwise a low tone


### Learnings:
* how to use the Serial Monitor with an Arduino Uno (9600 baud)
* pulldown resistors are needed to prevent pushbuttons from being in a floating state when open
* debounce pushbuttons when listening for a sequence of inputs to prevent one push from being read as multiple 
