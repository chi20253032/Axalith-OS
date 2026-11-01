# AXALITH OS

**An independently designed operating system powered by the Linux kernel.**

AXALITH OS targets everyday desktop users on x86-64 and ARM64. It uses the Linux kernel as its sole kernel strategy. AXALITH owns the user experience, desktop shell, system applications, platform services, visual identity, and product integration. The goal is to deliver a coherent, independent OS experience that does not look or behave like a conventional Linux distribution.

## Project status

- Product kernel: Linux LTS; no alternative or in-house kernel is planned
- Architectures: x86-64 first; ARM64 follows as a first-class target
- Desktop: independently designed AXALITH shell and system applications
- Graphics: Linux-supported graphics stack, with Vulkan as a preferred cross-vendor API
- Windows compatibility: staged user-mode application compatibility; Windows kernel drivers are not loaded natively by Linux

The existing 0.1 bootable image is a small bare-metal Multiboot2 experiment created before the Linux-only product decision. It validates an x86-64 boot path and QEMU smoke testing, but it is not the product kernel and will not be extended into a competing kernel. Preserve it as a historical engineering prototype. The next product milestone is a reproducible Linux LTS-based AXALITH image.

## Product principles

1. Linux is the sole kernel. Track an appropriate upstream LTS release and maintain a documented patch set.
2. AXALITH must have its own visual identity, desktop shell, login experience, settings, file manager, notifications, installer, and update experience.
3. Do not expose a generic Linux desktop as the finished product. Users should experience AXALITH, not a re-skinned upstream desktop.
4. Keep hardware-specific integration behind stable AXALITH platform interfaces where practical.
5. Preserve upstream notices and comply with every dependency's license.
6. Never claim Windows application or driver compatibility without passing documented tests.
7. Treat Windows kernel-driver compatibility as a separate, high-risk virtualization / device-assignment problem.

## Build the historical 0.1 prototype on Ubuntu 24.04

Install dependencies:

    sudo apt update
    sudo apt install -y build-essential binutils grub-pc-bin grub-common xorriso qemu-system-x86

Build the legacy prototype ISO:

    make clean
    make iso

Run in QEMU:

    make run

Serial diagnostics:

    make run-serial

This build does not produce the Linux-backed AXALITH product image. Requirements: x86-64 Linux host, GNU GCC/binutils, GRUB utilities, xorriso, and QEMU.

## Repository map

    boot/                 Legacy 0.1 Multiboot2 experiment
    kernel/               Legacy freestanding prototype code
    include/              Prototype headers and protocol definitions
    grub/                 Prototype GRUB boot menu
    docs/                 Architecture, roadmap, development policy
    .github/workflows/    Continuous integration

## License

Original AXALITH OS source in this repository is licensed under the MIT License unless a file says otherwise. Third-party components retain their own licenses.
