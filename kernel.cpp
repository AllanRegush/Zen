#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static uint16_t *v_memory = (uint16_t*) 0xB8000;

void terminal_clear()
{
    for (uint32_t y = 0; y < VGA_HEIGHT; y++) {
        for (uint32_t x = 0; x < VGA_WIDTH; x++) {
            const uint32_t index = (y * VGA_WIDTH) + x;
            v_memory[index] = (v_memory[index] & 0xFF00) | ' ';
        }
    }
}

void print(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
        v_memory[i] = (v_memory[i] & 0xFF00) | str[i];
}

extern "C" void k_main()
{
    terminal_clear();
    const char *msg = "Hello, World";
    print(msg);
}

