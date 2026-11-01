# AXALITH OS Roadmap

## 0.1 — Bootable developer preview

- [x] x86-64 Multiboot2 entry and long-mode transition
- [x] serial diagnostics
- [x] framebuffer splash when GRUB supplies a supported 32-bit RGB framebuffer
- [x] reproducible Makefile ISO target
- [ ] QEMU CI boot smoke test
- [ ] documented hardware test matrix

## 0.2 — Kernel foundations

- [ ] parse and validate complete boot information
- [ ] physical memory map and page-frame allocator
- [ ] virtual memory manager
- [ ] GDT / IDT, exception handlers and interrupt controllers
- [ ] PIT / APIC timer support
- [ ] kernel heap allocator
- [ ] panic screen and structured logging
- [ ] keyboard and serial input

## 0.3 — Linux-backed system prototype

- [ ] select and pin an appropriate Linux LTS baseline
- [ ] create reproducible x86-64 image build
- [ ] boot on QEMU and selected physical hardware
- [ ] establish AXALITH Core interfaces and Linux adapters
- [ ] service supervision, logging and update strategy
- [ ] networking and storage support

## 0.4 — Desktop and platform

- [ ] independent compositor / shell design
- [ ] display, input, audio and accessibility services
- [ ] file manager and settings
- [ ] package manager and signed repositories
- [ ] installer, recovery and rollback

## 0.5 — GPU and application compatibility

- [ ] supported NVIDIA driver integration on x86-64
- [ ] Vulkan conformance and GPU telemetry
- [ ] explicit multi-GPU selection and monitoring
- [ ] Windows user-mode compatibility layer integration
- [ ] application compatibility test harness
- [ ] Windows VM and PCIe passthrough prototype

## 0.6 — ARM64

- [ ] ARM64 cross-compilation toolchain
- [ ] QEMU AArch64 boot target
- [ ] firmware and device-tree / ACPI discovery
- [ ] memory, interrupt and timer bring-up
- [ ] supported ARM64 reference hardware

## 0.7+ — Product hardening

- [ ] secure boot and signed updates
- [ ] accessibility and localization
- [ ] installer and recovery testing
- [ ] performance, power and reliability testing
- [ ] security audit and software bill of materials
- [ ] public hardware and application compatibility matrix

## Long-term research — native AXALITH kernel

This track starts only after the Linux-backed product has stable interfaces and conformance tests. The native kernel must pass the same platform tests before any supported product profile can use it. Linux remains an available backend; native-kernel progress does not silently remove hardware support.
