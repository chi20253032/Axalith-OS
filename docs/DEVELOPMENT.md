# Development Environment

## Host requirements

The first bootable target is x86-64 Linux. Ubuntu 24.04 is the documented reference host.

Install:

    sudo apt update
    sudo apt install -y build-essential binutils grub-pc-bin grub-common xorriso qemu-system-x86

## Commands

    make clean       # remove generated files
    make kernel      # compile the freestanding x86-64 kernel
    make check       # verify the Multiboot2 header
    make iso         # create a bootable GRUB ISO
    make run         # launch the ISO in a QEMU window
    make run-serial  # launch with serial diagnostics

Generated artifacts are placed under build/.

## Debugging

- Use make run-serial to inspect kernel log messages.
- Add -S -s to QEMU for GDB remote debugging.
- Use gdb build/axalith-kernel.elf, then target remote :1234.
- Keep boot and kernel diagnostics available even when graphics initialization fails.

## Coding rules

- Keep the early boot path freestanding and dependency-light.
- Do not use the host C library from kernel code.
- Check all firmware / bootloader-provided structures before dereferencing them.
- Use fixed-width integer types for hardware and protocol fields.
- Document assumptions about physical address ranges and paging.
- Do not claim a feature works until it has a repeatable test.

## ARM64

ARM64 is an approved product architecture, but the current 0.1 boot stub is x86-64 only. ARM64 needs a separate boot path and CI job; do not compile x86 assembly for ARM64. Shared kernel and platform interfaces should remain architecture-neutral.
