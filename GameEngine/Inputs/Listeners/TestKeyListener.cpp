#include "TestKeyListener.h"

void TestKeyListener::onKeyChanged(KeyInput keyInput) {
    printf("Key: [%d] Pressed: [%d]\n", keyInput.key, keyInput.action);
}
