#pragma once
#include <cstdio>

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}
