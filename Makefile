CC      ?= gcc
LD      ?= ld
GRUB_FILE ?= grub-file
GRUB_MKRESCUE ?= grub-mkrescue
QEMU    ?= qemu-system-x86_64

BUILD := build
ISO_ROOT := $(BUILD)/iso
KERNEL := $(BUILD)/axalith-kernel.elf
ISO := $(BUILD)/axalith-os-0.1-x86_64.iso

CFLAGS := -std=c11 -O2 -Wall -Wextra -Werror \
          -ffreestanding -fno-stack-protector -fno-pic -fno-pie \
          -fno-builtin -m64 -mno-red-zone -mcmodel=large \
          -fno-asynchronous-unwind-tables -fno-unwind-tables \
          -Iinclude
ASFLAGS := -m64 -ffreestanding -fno-pic -fno-pie
LDFLAGS := -m elf_x86_64 -nostdlib -static -z max-page-size=0x1000 -T linker.ld

.PHONY: all kernel iso check run run-serial clean

all: iso

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/boot.o: boot/x86_64/boot.S | $(BUILD)
	$(CC) $(ASFLAGS) -c $< -o $@

$(BUILD)/main.o: kernel/main.c include/axalith/bootinfo.h | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(BUILD)/boot.o $(BUILD)/main.o linker.ld
	$(LD) $(LDFLAGS) -o $@ $(BUILD)/boot.o $(BUILD)/main.o

kernel: $(KERNEL)

check: $(KERNEL)
	$(GRUB_FILE) --is-x86-multiboot2 $(KERNEL)
	@echo "Multiboot2 kernel header: OK"

$(ISO): $(KERNEL) grub/grub.cfg
	mkdir -p $(ISO_ROOT)/boot/grub
	cp $(KERNEL) $(ISO_ROOT)/boot/axalith-kernel.elf
	cp grub/grub.cfg $(ISO_ROOT)/boot/grub/grub.cfg
	$(GRUB_MKRESCUE) -o $@ $(ISO_ROOT)

iso: check $(ISO)
	@echo "Created $(ISO)"

run: iso
	$(QEMU) -machine q35 -m 512M -cdrom $(ISO) -boot d

run-serial: iso
	$(QEMU) -machine q35 -m 512M -cdrom $(ISO) -boot d -display none -serial stdio

clean:
	rm -rf $(BUILD)
