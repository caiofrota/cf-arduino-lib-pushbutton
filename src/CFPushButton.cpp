/**
 * CFPushButton.cpp
 * 
 * A library for Arduino that helps interface for Push Buttons.
 * 
 * @author  Caio Frota <caiofrota@gmail.com>
 * @version 1.0
 * @since   Mar, 2021
 */

#include <CFPushButton.h>

/**
 * Constructor.
 *
 * @param pinPushButton Push Button pin.
 */
CFPushButton::CFPushButton(int pinPushButton):
        _pinPushButton(pinPushButton),
        _pulledHigh(false),
        _pressTime(0), _shortPressTime(3000), _longPressTime(10000),
        _callbackTime(0) {
    
}

/**
 * Initial setup.
 */
void CFPushButton::begin() {
    pinMode(_pinPushButton, INPUT);
}

/**
 * Control push button state.
 */
void CFPushButton::loop() {
    _state = digitalRead(_pinPushButton);
    
    /*
        Check if button is not pressed.
        - If the button is pulled up, LOW is pressed.
        - If the button is pulled down, HIGH is pressed.
    */
    if (_state == (isPulledUp()) ? LOW : HIGH) {
        // Button is pressed.
        // Check if _pressTime is zero, if true, this is the first loop when pressed.
        if (_pressTime == 0) {
            _pressTime = millis(); // Store the time it was pressed.
        } else {
            // If it is not the first loop, check the time pressed.
            if (millis() - _pressTime > _longPressTime && _callbackTime == 1) {
                // Long press time was reached.
                if (_onLongPressReachedCallback != NULL) {
                    _onLongPressReachedCallback();
                }
                _callbackTime++;
            } else if (millis() - _pressTime > _shortPressTime && _callbackTime == 0) {
                // Short press time was reached.
                if (_onShortPressReachedCallback != NULL) {
                    _onShortPressReachedCallback();
                }
                _callbackTime++;
            }
        }
    } else {
        // Button not pressed.
        // Check if _pressTime is greater than zero, if true, it was pressed.
        if (_pressTime > 0) {
            // Reset control values.
            _buttonReleased(millis() - _pressTime);
            _pressTime = 0;
            _callbackTime = 0;
        }
    }
}

/**
 * Called when the button is released.
 
 * @param pressedTime Time that button was pressed.
 */
void CFPushButton::_buttonReleased(int pressedTime) {
     if (pressedTime > _longPressTime) {
        if (_onLongPressCallback != NULL) {
            _onLongPressCallback();
        }
    } else if (pressedTime > _shortPressTime) {
        if (_onShortPressCallback != NULL) {
            _onShortPressCallback();
        }
    } else {
        if (_onPressCallback != NULL) {
            _onPressCallback();
        }
    }
}

/**
 * Get button state.
 * 
 * @returns Button state.
 */
int CFPushButton::getState() {
    return _state;
}

/**
 * True if button is pulled up.
 * 
 * @returns True if button is pulled high.
 */
bool CFPushButton::isPulledUp() {
    return _pulledHigh;
}

/**
 * Define button is pulled up.
 */
void CFPushButton::setPulledUp() {
    _pulledHigh = true;
}

/**
 * Define button is pulled down.
 */
void CFPushButton::setPulledDown() {
    _pulledHigh = false;
}

/**
 * Get short time in millis that the button should be pressed to call short press callback.
 *
 * @returns Short time in millis.
 */
int CFPushButton::getShortPressTime() {
    return _shortPressTime;
}

/**
 * Define short time in millis that the button should be pressed to call short press callback.
 * 
 * @param shortPressTime Short time in millis.
 */
void CFPushButton::setShortPressTime(int shortPressTime) {
    _shortPressTime = shortPressTime;
}

/**
 * Get long time in millis that the button should be pressed to call long press callback.
 *
 * @returns Long time in millis.
 */
int CFPushButton::getLongPressTime() {
    return _longPressTime;
}

/**
 * Define long time in millis that the button should be pressed to call long press callback.
 * 
 * @param longPressTime Long time in millis.
 */
void CFPushButton::setLongPressTime(int longPressTime) {
    _longPressTime = longPressTime;
}

/**
 * Define method that should be called when short time is reached.
 *
 * @param func No-parameter and no-return function.
 */
void CFPushButton::setOnShortPressReachedCallback(std::function<void()> func) {
    _onShortPressReachedCallback = func;
}

/**
 * Define method that should be called when long time is reached.
 *
 * @param func No-parameter and no-return function.
 */
void CFPushButton::setOnLongPressReachedCallback(std::function<void()> func) {
    _onLongPressReachedCallback = func;
}

/**
 * Define method that should be called when button is pressed.
 *
 * @param func No-parameter and no-return function.
 */
void CFPushButton::setOnPressCallback(std::function<void()> func) {
    _onPressCallback = func;
}

/**
 * Define method that should be called when button is short time pressed.
 *
 * @param func No-parameter and no-return function.
 */
void CFPushButton::setOnShortPressCallback(std::function<void()> func) {
    _onShortPressCallback = func;
}

/**
 * Define method that should be called when button is long time pressed.
 *
 * @param func No-parameter and no-return function.
 */
void CFPushButton::setOnLongPressCallback(std::function<void()> func) {
    _onLongPressCallback = func;
}