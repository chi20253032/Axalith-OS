# AXALITH OS

**An independent hybrid operating system for x86-64 and ARM64.**

AXALITH OS targets everyday desktop users. It combines an independently designed user experience and platform layer with a replaceable kernel backend. The first backend is Linux; a native AXALITH kernel is a long-term research track, not a near-term compatibility promise.

## Project status

- Milestone: 0.1 Developer Preview — x86-64 boot foundation
- Architectures: x86-64 first; ARM64 platform bring-up follows
- Kernel strategy: hybrid / replaceable backend
- Graphics: framebuffer bootstrap first; Vulkan and vendor drivers later
- Windows compatibility: staged application compatibility; Windows kernel drivers are not loaded natively by the Linux backend

The current bootstrap is a small Multiboot2 x86-64 kernel intended to boot in QEMU through GRUB. It draws a minimal AXALITH splash screen and reports boot status over serial. It is not yet a general-purpose OS.

## Build on Ubuntu 24.04

Install dependencies:

    sudo apt update
    sudo apt install -y build-essential binutils grub-pc-bin grub-common xorriso qemu-system-x86

Build the kernel and bootable ISO:

    make clean
    make iso

Run in QEMU:

    make run

Serial diagnostics:

    make run-serial

Requirements: x86-64 Linux host, GNU GCC/binutils, GRUB utilities, xorriso, and QEMU. The first milestone uses GRUB Multiboot2 and is not an installer or UEFI-native boot manager.

## Repository map

    boot/                 Multiboot2 entry and x86-64 long-mode transition
    kernel/               Freestanding kernel code
    include/              Kernel headers and protocol definitions
    grub/                 GRUB boot menu
    docs/                 Architecture, roadmap, development policy
    .github/workflows/    Continuous integration

## Architecture policy

1. Keep hardware-specific code behind documented interfaces.
2. Keep architecture-specific boot and low-level code in separate directories.
3. Do not make the platform layer depend directly on Linux implementation details.
4. Preserve upstream notices and comply with every dependency's license.
5. Never claim Windows application or driver compatibility without passing documented tests.
6. Treat Windows kernel-driver compatibility as a separate, high-risk virtualization / device-assignment problem.

See docs/ARCHITECTURE.md, docs/ROADMAP.md, and docs/DEVELOPMENT.md.

## License

Original AXALITH OS source in this repository is licensed under the MIT License unless a file says otherwise. Third-party components retain their own licenses.
