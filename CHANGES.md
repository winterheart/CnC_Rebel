# Major changes for CnC: Rebel

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
