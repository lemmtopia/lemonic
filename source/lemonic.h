#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef float f32;
typedef double f64;

typedef char b8;
typedef int b32;

#define TRUE 1
#define FALSE 0

void lemonic_open_window(const char* title, i32 width, i32 height);
b8 lemonic_is_running();
void lemonic_message_loop();
