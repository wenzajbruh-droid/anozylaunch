# Horizon Launcher

**Unofficial modified version.** Horizon Launcher is a personal Android launcher for
[Minecraft: Java Edition](https://www.minecraft.net/), built from source code of
[Zalith Launcher 2](https://github.com/ZalithLauncher/ZalithLauncher2) and its community fork
[Zalith Launcher 2+](https://github.com/Star1xr/ZalithLauncher2Plus). It is not affiliated with or endorsed by
either project.

## Attribution and license

- Licensed under **GPL-3.0** (see [LICENSE](LICENSE)), inherited from the upstream projects.
- Per the additional terms in the upstream README (GPLv3 §7): this program is renamed, it does not use the
  names "ZalithLauncher" or "ZL", and it shows an "Unofficial Version" notice on first launch.
  The original copyright notices are kept.
- Launch engine: [PojavLauncher](https://github.com/PojavLauncherTeam/PojavLauncher).

## Build

Requirements: Android Studio (recent), JDK 11+, Android SDK with API 35 (target) and API 26 (min).

Debug build (signed with the local Android debug key):

```bash
./gradlew :ZalithLauncher:assembleDebug
```

Release build (requires your own keystore; nothing is bundled in this repo):

```bash
export HORIZON_KEYSTORE=/path/to/your.jks
export HORIZON_KEYSTORE_PASS=...
export HORIZON_KEY_ALIAS=...
export HORIZON_KEY_PASS=...
./gradlew :ZalithLauncher:assembleRelease
```

Create a keystore once with `keytool -genkeypair -v -keystore your.jks -alias horizon -keyalg RSA -keysize 2048 -validity 10000`.
Without `HORIZON_KEYSTORE`, the release build is produced unsigned.

## Renaming

- App name: `launcher_app_name` in `ZalithLauncher/gradle.properties`.
- Application ID: `horizonApplicationId` in `ZalithLauncher/build.gradle.kts`.
- The Java/Kotlin namespace (`com.movtery.zalithlauncher`) is internal and was left unchanged.
