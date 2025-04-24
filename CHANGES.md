# Major changes for CnC: Rebel

## 1.34.2 - TECHNICIAN

This release aimed to be intermediate stable base for new features and enhancements. Codebase migrated to recent
Platform SDK and now game requires at least Windows 10.

* Project migrated to MSVC 2022 and Windows Platform SDK 10 with cmake as main buildsystem.
* Project migrated to support C++20 standard.
* Project now uses dxsdk-d3dx package from vcpkg, all required DirectX dependencies are bundled into release tarball.
* Remove and replace some deprecated D3DX aux libraries (dxerr and d3dxmath).
* LevelEdit now uses same registry location `HKEY_CURRENT_USER\Software\CnC_Rebel\Rebel` as game.
* Properly identify build info in main screen and logs (include version, codename and build hash to messages).
* Fixes some compilation warnings.
* Fixes some runtime errors and compatibility issues.

## 1.034.1 - MIRAGE TANK

This is the last build that supports Windows XP. Next releases will require a more recent platform.

* Built with MSVC 2010.
* Migrated to DirectX 9.0 SDK June 2010. Game now requires DirectX End-User Runtimes (June 2010).
* Fix runtime error on starting Campaign.
* Migrate all registry keys from `HKEY_LOCAL_MACHINE\Software\Westwood\Renegade` to `HKEY_CURRENT_USER\Software\CnC_Rebel\Rebel`.
  Game and WWConfig will migrate old entries to new locations automatically.
* Minor fixes and enhancements to code.

## 1.034.0 - MINIGUNNER

* Built with MSVC 6.0.
* Linked with DirectX 9.0 in compat mode.
* Fixed version generation in main screen.
* Runnable Level Editor.
* GameSpy code (mainly query and reporting stuff) are disabled with ENABLE_GAMESPY macro.
* Imported GNU Regex from Gnulib circa 2002.
