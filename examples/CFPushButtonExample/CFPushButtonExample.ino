#include <CFPushButton.h>                                                                                   // CF Push Button.

CFPushButton pushButton(D5);                                                                                // Push Button.

void setup() {
    Serial.begin(9600);
    // Button cofig.
    //pushButton.setPulledUp();   // Uncomment this line if you have a pulled up push button.
    //pushButton.setPulledDown(); // Pulled down is default.
    //pushButton.setShortPressTime(3000); // Time that identifies a short press in millis. 3 seconds default.
    //pushButton.setLongPressTime(10000); // Time that identifies a long press in millis. 10 seconds default.
    
    // Define callbacks.
    pushButton.setOnShortPressReachedCallback(onShortPressReachedCallback);
    pushButton.setOnLongPressReachedCallback(onLongPressReachedCallback);
    pushButton.setOnPressCallback(onPressCallback);
    pushButton.setOnShortPressCallback(onShortPressCallback);
    pushButton.setOnLongPressCallback(onLongPressCallback);
    
    // Start button.
    pushButton.begin();
}

void loop() {
    // Loop button.
    pushButton.loop();
}

// ====================
// Callbacks.
// ====================

void onShortPressReachedCallback() {
    Serial.println("SHORT time was reached.");
}

void onLongPressReachedCallback() {
    Serial.println("LONG time was reached.");
}

void onPressCallback() {
    Serial.println("Button was pressed.");
}

void onShortPressCallback() {
    Serial.println("Button was SHORT Pressed.");
}

void onLongPressCallback() {
    Serial.println("Button was LONG Pressed.");
}