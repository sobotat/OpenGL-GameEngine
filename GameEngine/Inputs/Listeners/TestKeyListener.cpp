#include "TestKeyListener.h"

void TestKeyListener::notify(KeyInput keyInput) {
    printf("Key: [%d] Pressed: [%d]\n", keyInput.key, keyInput.action);
}
