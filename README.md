# Rebel - Command & Conquer Renegade source code enhancement project

The project aimed at improving the source code of CnC: Renegade for running on modern platforms and adding new features.

## Major features

* DirectX 9 support.

See [CHANGES.md](CHANGES.md) for full changelog.

## Development and Dependencies

* Microsoft Visual C++ 2022
* Microsoft Platform SDK 10.0
* CMake 3.20
* Microsoft.DXSDK.D3DX 9.29.952.8 (vcpkg package)
* RAD Miles Sound System 6 SDK (`Code/third_party/miles6`)
* RAD Bink SDK (`Code/third_party/bink`)
* NvDXTLib SDK (`Code/third_party/nvDXTLib`)

## Runtime Dependencies

To use the compiled binaries, you must own the game, fully patched to v1.037. Best choice is purchase CnC: Renegade
on [Steam](https://store.steampowered.com/app/2229890/Command__Conquer_Renegade/).

Minimal requirements for system:

* Windows 10
* A processor that supports the SSE2 instruction set
* A DirectX 9 compliant video card

## Licensing

This repository and its contents are licensed under the GPL v3 license, with additional terms applied.
Please see [LICENSE.md](LICENSE.md) for details.
