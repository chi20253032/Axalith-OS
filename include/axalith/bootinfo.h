#ifndef AXALITH_BOOTINFO_H
#define AXALITH_BOOTINFO_H

#include <stdint.h>

#define AXALITH_MULTIBOOT2_BOOT_MAGIC 0x36d76289u
#define AXALITH_MB2_TAG_END 0u
#define AXALITH_MB2_TAG_FRAMEBUFFER 8u

struct __attribute__((packed)) axalith_mb2_info {
    uint32_t total_size;
    uint32_t reserved;
};

struct __attribute__((packed)) axalith_mb2_tag {
    uint32_t type;
    uint32_t size;
};

struct __attribute__((packed)) axalith_mb2_framebuffer_tag {
    uint32_t type;
    uint32_t size;
    uint64_t address;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
    uint8_t framebuffer_type;
    uint16_t reserved;
};

#endif
