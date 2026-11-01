# AXALITH OS Architecture

## Product contract

AXALITH OS targets everyday desktop users on x86-64 and ARM64. **The Linux kernel is the sole kernel strategy for AXALITH OS.** There is no parallel native-kernel product or long-term kernel-replacement track. AXALITH differentiates itself through its independently designed desktop, platform services, system applications, package and update experience, visual identity, and product integration.

The existing 0.1 Multiboot2 image is a historical bare-metal bring-up experiment created before the Linux-only decision. It is not the production backend and should be maintained only as a reference / archival prototype unless a narrowly scoped maintenance fix is needed.

## Layer model

1. Experience: AXALITH desktop shell, compositor/window management, file manager, settings, notifications, accessibility, first-party applications.
2. AXALITH platform: service supervision, package management, application lifecycle, audio, networking, security policy, graphics integration, updates and recovery.
3. Compatibility: Linux application ABI, Windows user-mode API compatibility, application containers, virtual machines and device assignment.
4. AXALITH integration layer: stable interfaces and services that connect the AXALITH experience to the underlying operating system.
5. Kernel: upstream Linux LTS, with a small, reviewable AXALITH patch set where required.
6. Hardware: CPU, memory, storage, display, GPU, input, network and firmware, supported through the Linux kernel and its driver ecosystem.

AXALITH components should use documented platform interfaces rather than depend on incidental implementation details. Where Linux-specific integration is necessary, isolate it in backend adapters and keep the boundary documented. This is an abstraction and maintainability goal, not a promise that AXALITH can later swap out Linux for another kernel.

## Architecture targets

- x86-64 is the first implementation and validation target.
- ARM64 is a first-class target with its own boot flow, toolchain, device tree / ACPI handling, firmware requirements, and hardware validation.
- Shared code belongs in architecture-neutral libraries.
- Architecture-specific integration belongs in clearly separated x86-64 and AArch64 modules.
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

## Linux kernel maintenance policy

- Track a supported upstream Linux LTS baseline and document the exact version used by each release.
- Prefer upstream functionality and out-of-tree integration over invasive kernel forks.
- Keep AXALITH kernel patches small, reviewable, reproducible, and documented.
- Preserve required license notices and provide corresponding source where applicable.
- Establish a regular security-update and stable-backport process.
- Validate kernel updates against boot, storage, networking, graphics, suspend/resume, and supported hardware test suites.

## Security baseline

- Secure Boot support is a release requirement, not assumed in the 0.1 prototype.
- Signed system updates and rollback-capable deployments.
- Least-privilege service model and per-application permissions.
- Memory-safe languages for new privileged components where practical.
- Threat modeling, fuzzing, dependency scanning, and security response process before public stable release.

## Licensing

Every imported component must have its license, version, source URL, patch set, and redistribution obligations recorded in a software bill of materials. Linux kernel and driver licensing must be reviewed independently. Obtain legal review before distributing proprietary driver binaries or Windows compatibility components.
