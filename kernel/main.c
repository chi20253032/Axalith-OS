#include <stdint.h>
#include <stddef.h>
#include "axalith/bootinfo.h"

#define COM1 0x3F8u

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}
static void serial_init(void) {
    outb(COM1 + 1, 0x00); outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03); outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03); outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}
static void serial_putc(char c) {
    for (uint32_t timeout = 0; timeout < 100000u; ++timeout) {
        if ((inb(COM1 + 5) & 0x20u) != 0u) { outb(COM1, (uint8_t)c); return; }
    }
}
static void serial_write(const char *text) {
    while (*text != '\0') {
        if (*text == '\n') serial_putc('\r');
        serial_putc(*text++);
    }
}
static void halt_forever(void) {
    for (;;) __asm__ volatile ("cli; hlt");
}
static void fill_rect(volatile uint32_t *pixels, uint32_t pitch_pixels,
                      uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                      uint32_t color) {
    for (uint32_t row = 0; row < height; ++row) {
        volatile uint32_t *line = pixels + (size_t)(y + row) * pitch_pixels + x;
        for (uint32_t col = 0; col < width; ++col) line[col] = color;
    }
}
static void draw_splash(const struct axalith_mb2_framebuffer_tag *fb) {
    if (fb == NULL || fb->framebuffer_type != 1u || fb->bpp != 32u ||
        fb->width < 64u || fb->height < 64u || fb->pitch < fb->width * 4u) {
        serial_write("AXALITH: framebuffer unavailable; serial mode only.\n");
        return;
    }
    volatile uint32_t *pixels = (volatile uint32_t *)(uintptr_t)fb->address;
    const uint32_t pitch_pixels = fb->pitch / 4u;
    fill_rect(pixels, pitch_pixels, 0, 0, fb->width, fb->height, 0x000D1224u);

    const uint32_t cx = fb->width / 2u;
    const uint32_t cy = fb->height / 2u;
    const uint32_t min_side = fb->width < fb->height ? fb->width : fb->height;
    const uint32_t u = min_side / 12u == 0u ? 1u : min_side / 12u;

    fill_rect(pixels, pitch_pixels, cx - 3u*u, cy - 2u*u, 2u*u, 4u*u, 0x0038D9E8u);
    fill_rect(pixels, pitch_pixels, cx - 1u*u, cy - 2u*u, 4u*u, 2u*u, 0x006C78FFu);
    fill_rect(pixels, pitch_pixels, cx + 1u*u, cy, 2u*u, 2u*u, 0x009B70F2u);
    fill_rect(pixels, pitch_pixels, cx - 1u*u, cy + 2u*u, 4u*u, u, 0x0038D9E8u);

    const uint32_t panel_w = fb->width / 3u;
    fill_rect(pixels, pitch_pixels, cx - panel_w/2u, cy + 4u*u,
              panel_w, u, 0x00202B45u);
    fill_rect(pixels, pitch_pixels, cx - panel_w/2u, cy + 4u*u,
              panel_w / 3u, u, 0x0038D9E8u);
}

void kmain(uint64_t mbi_address, uint32_t boot_magic) {
    serial_init();
    serial_write("\nAXALITH OS 0.1 Developer Preview\n");
    serial_write("Boot stage: x86-64 kernel entry\n");

    if (boot_magic != AXALITH_MULTIBOOT2_BOOT_MAGIC || mbi_address == 0u) {
        serial_write("FATAL: invalid Multiboot2 handoff.\n");
        halt_forever();
    }

    const struct axalith_mb2_info *info =
        (const struct axalith_mb2_info *)(uintptr_t)mbi_address;
    if (info->total_size < sizeof(*info)) {
        serial_write("FATAL: malformed boot information.\n");
        halt_forever();
    }

    const struct axalith_mb2_framebuffer_tag *framebuffer = NULL;
    const uint8_t *cursor = (const uint8_t *)info + 8u;
    const uint8_t *end = (const uint8_t *)info + info->total_size;
    while (cursor + sizeof(struct axalith_mb2_tag) <= end) {
        const struct axalith_mb2_tag *tag = (const struct axalith_mb2_tag *)cursor;
        if (tag->size < sizeof(*tag) || cursor + tag->size > end) break;
        if (tag->type == AXALITH_MB2_TAG_FRAMEBUFFER &&
            tag->size >= sizeof(struct axalith_mb2_framebuffer_tag)) {
            framebuffer = (const struct axalith_mb2_framebuffer_tag *)tag;
        }
        if (tag->type == AXALITH_MB2_TAG_END) break;
        cursor += (tag->size + 7u) & ~7u;
    }

    draw_splash(framebuffer);
    serial_write("Kernel status: ONLINE\n");
    serial_write("Next: memory map, allocator, interrupts, and input.\n");
    halt_forever();
}
