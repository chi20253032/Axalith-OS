# AXALITH OS Architecture

## Product contract

AXALITH OS targets everyday desktop users on x86-64 and ARM64. The user experience, platform services, package format, system API, and desktop shell are independently designed. The first product kernel backend is Linux LTS. A native kernel is a separate long-term research project and must not block a usable Linux-backed product.

## Layer model

1. Experience: desktop shell, compositor/window manager, file manager, settings, notifications, accessibility, first-party applications.
2. Platform: service manager, package manager, application lifecycle, audio, networking, security policy, graphics API, update and recovery.
3. Compatibility: Linux ABI, Windows user-mode API compatibility, application containers, virtual machines and device assignment.
4. AXALITH Core: stable internal interfaces for memory, processes, devices, filesystems, IPC, timers, power, and graphics.
5. Kernel backend: Linux LTS initially; experimental native kernel later.
6. Hardware: CPU, memory, storage, display, GPU, input, network and firmware.

Upper layers depend on AXALITH interfaces, not Linux-specific implementation details. Linux-specific adapters live under the Linux backend.

## Architecture targets

- x86-64 is the first implementation and validation target.
- ARM64 is a first-class target with its own boot flow, toolchain, device tree / ACPI handling, firmware requirements, and hardware validation.
- Shared code belongs in architecture-neutral libraries.
- Architecture-specific code belongs in arch/x86_64 or arch/aarch64.
- Do not promise that an x86-64 binary or driver runs on ARM64 without emulation or a supported native build.

## GPU policy

- Start with the vendor-supported Linux driver stack for supported NVIDIA GPUs.
- Use Vulkan as the preferred cross-vendor graphics API; retain OpenGL where needed.
- Use CUDA only where the NVIDIA stack and license permit it.
- Multi-GPU management initially means enumeration, per-device telemetry, explicit device selection, and application-level workload placement. It does not imply transparent VRAM pooling or automatic scaling for arbitrary games.
- Windows NVIDIA kernel drivers are not loaded directly into the Linux kernel.
- Windows-only devices or drivers may be supported through a Windows VM and PCIe passthrough where hardware, IOMMU, firmware, and licensing permit. A passed-through device is generally owned by the guest while assigned.

## Windows compatibility policy

Separate three compatibility goals:

1. User-mode applications: Wine / Proton / other lawful compatibility implementations, tested per application.
2. Graphics and games: DirectX translation to Vulkan where supported; compatibility varies by application, anti-cheat, DRM, and driver.
3. Kernel-mode drivers: not part of the Linux ABI. Treat as a VM / device assignment problem unless a separately engineered, legally reviewed compatibility subsystem is proven.

Never advertise complete Windows compatibility until a published compatibility matrix demonstrates it. Windows itself, Windows source code, proprietary Microsoft binaries, product keys, and Microsoft trademarks are not bundled without authorization.

## Kernel backend interface

AXALITH Core defines versioned interfaces for physical and virtual memory, scheduling, interrupt and timer delivery, device discovery, block and character I/O, VFS, IPC, power events, and graphics presentation. The Linux backend maps these interfaces to Linux facilities. A future native backend must implement the same conformance suite before replacing Linux for any product profile.

## Security baseline

- Secure Boot support is a release requirement, not assumed in the bootstrap.
- Signed system updates and rollback-capable deployments.
- Least-privilege service model and per-application permissions.
- Memory-safe languages for new privileged components where practical.
- Threat modeling, fuzzing, dependency scanning, and security response process before public stable release.

## Licensing

Every imported component must have its license, version, source URL, patch set, and redistribution obligations recorded in a software bill of materials. Linux kernel and driver licensing must be reviewed independently. Obtain legal review before distributing proprietary driver binaries or Windows compatibility components.
