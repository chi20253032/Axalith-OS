# Development Environment

## Product development direction

AXALITH OS is developed as a Linux LTS-based operating system with an independently designed desktop and platform. The repository's current Makefile builds the historical 0.1 bare-metal experiment; it does not build the product image. Product-image build instructions will be added with milestone 0.2 after the Linux baseline and image-building system are selected.

## Historical 0.1 prototype

The first bootable prototype targets x86-64 and uses Ubuntu 24.04 as its documented reference build host.

Install:

    sudo apt update
    sudo apt install -y build-essential binutils grub-pc-bin grub-common xorriso qemu-system-x86

Commands:

    make clean       # remove generated files
    make kernel      # compile the historical freestanding x86-64 prototype
    make check       # verify the Multiboot2 header
    make iso         # create the historical prototype ISO
    make run         # launch the prototype ISO in QEMU
    make run-serial  # launch with serial diagnostics

Generated artifacts are placed under build/. These commands do not build or boot the Linux-backed AXALITH product.

## Product build requirements (planned for 0.2)

- Pin the Linux LTS release and configuration.
- Make image creation reproducible and CI-driven.
- Record source versions, patches, licenses, and redistribution obligations.
- Test boot and core hardware on QEMU and a documented physical-device matrix.
- Keep system updates signed and support rollback.

## Development rules

- Treat Linux as the sole kernel; do not add a parallel native-kernel roadmap.
- Prefer upstream Linux functionality and small, reviewable AXALITH patches.
- Keep AXALITH desktop and platform design independent from generic Linux desktop environments.
- Do not claim a feature works until it has a repeatable test.
- Keep boot and diagnostic paths usable when graphics initialization fails.

## ARM64

ARM64 is a first-class product target, but the current 0.1 prototype is x86-64 only. The Linux-backed product needs a separate ARM64 image build and hardware validation. Shared AXALITH platform code should remain architecture-neutral where practical.
