# AXALITH OS Roadmap

## Kernel strategy — decided

**AXALITH OS uses the Linux kernel exclusively.** The product will track an appropriate upstream Linux LTS baseline. No native AXALITH kernel development track is planned. Engineering effort is focused on the AXALITH platform, desktop, system applications, hardware integration, and product quality.

## 0.1 — Historical bare-metal experiment

- [x] x86-64 Multiboot2 entry and long-mode transition
- [x] serial diagnostics
- [x] framebuffer splash when GRUB supplies a supported 32-bit RGB framebuffer
- [x] reproducible Makefile ISO target
- [x] QEMU CI boot smoke test
- [ ] documented hardware test matrix

Status: this is a pre-decision engineering prototype, not the Linux-backed product. Keep it as a reference; do not expand it into a competing kernel.

## 0.2 — Linux LTS product foundation

- [ ] select and pin an appropriate Linux LTS baseline
- [ ] define supported x86-64 hardware baseline and kernel configuration
- [ ] create reproducible Linux-based image build
- [ ] boot the image in QEMU and selected physical hardware
- [ ] define AXALITH system partitioning, boot, init, and service supervision
- [ ] establish logging, crash reporting, update, and recovery foundations
- [ ] validate storage, networking, audio, input, and display basics
- [ ] create software bill of materials and license inventory

## 0.3 — AXALITH platform

- [ ] define stable AXALITH platform services and APIs
- [ ] application lifecycle and permission model
- [ ] package manager and signed repositories
- [ ] system update, rollback, and recovery mechanism
- [ ] networking, audio, Bluetooth, power, and device management
- [ ] localization and accessibility foundations

## 0.4 — Independent desktop experience

- [ ] define AXALITH visual design system and interaction principles
- [ ] implement independent compositor / shell
- [ ] implement login, desktop, taskbar / dock, launcher, notifications, and window management
- [ ] build AXALITH file manager and settings
- [ ] build first-party system applications
- [ ] installer and recovery user experience
- [ ] ensure the finished experience does not resemble a generic Linux desktop

## 0.5 — GPU and application compatibility

- [ ] supported NVIDIA driver integration on x86-64
- [ ] Vulkan conformance and GPU telemetry
- [ ] explicit multi-GPU selection and monitoring
- [ ] Windows user-mode compatibility layer integration
- [ ] application compatibility test harness
- [ ] Windows VM and PCIe passthrough prototype for selected devices

## 0.6 — ARM64

- [ ] select supported ARM64 reference hardware
- [ ] Linux LTS ARM64 image and boot flow
- [ ] firmware and device-tree / ACPI validation
- [ ] validate storage, graphics, networking, suspend/resume, and power
- [ ] publish an ARM64 hardware compatibility list

## 0.7+ — Product hardening and release

- [ ] Secure Boot and signed updates
- [ ] accessibility and localization
- [ ] installer and recovery testing
- [ ] performance, power, and reliability testing
- [ ] security audit and software bill of materials
- [ ] public hardware and application compatibility matrix
- [ ] release engineering, support policy, and security response process
