# Horizon Launcher for Android

An Android port of the open source [Horizon Launcher client](https://github.com/HorizonLauncher/Client) (MIT, C++/Qt), keeping the original C++ codebase and Qt Widgets UI.

> **Status: early port, not yet built or tested on a device.** The code changes are in place, but nothing has been compiled yet. The first step is running the GitHub Actions workflow (see below) and fixing whatever the compiler finds.

## What changed from the desktop client

| Area | Desktop | Android |
| --- | --- | --- |
| Build | CMake + Qt 5 | `HorizonLauncher-android.pro` (qmake, Qt 5.15 + `androidextras`) and `android/AndroidManifest.xml` |
| Window | Frameless/borderless window with custom title bar | `AndroidWindow` / `AndroidPanel`, always full screen, finger-drag scrolling via `QScroller` |
| Launching a game | Starts an executable with `QProcess` | Starts an installed app through an Android `Intent`; the "Executable" field holds the **package name** (for example `com.example.game`) |
| Add game wizard | Directory + executable pickers | Package name only |
| Store tab | Embedded QtWebKit browser | QtWebKit doesn't exist on Android, so the tab opens the store in the system browser |
| Steam import | Reads the local Steam install | Disabled (no Steam client on Android) |
| Data folder | Generic data location | App-private data folder |

## Known limitations

- The layout was designed for a 1152x648 desktop window and has not been adapted for phone screens yet.
- Only the Add game wizard and the launcher were adapted for Android; other screens still assume desktop behaviour (for example some file pickers in Settings).
- `CMakeLists.txt` is the unchanged desktop build. Android builds only use the `.pro` file.

## Building the APK

Easiest: push to GitHub and run the **Android APK** workflow (`.github/workflows/android.yml`). It installs Qt 5.15.2 + NDK r21e and uploads a debug APK as an artifact.

Locally you need Qt 5.15.x for Android, NDK r21e, the Android SDK and JDK 11. The exact commands are at the top of `HorizonLauncher-android.pro`.

---

# Original project

## Horizon Launcher Client Repository

[![Slack Status](http://slack.launchhorizon.com/badge.svg)](http://slack.launchhorizon.com)
[![Chat on Freenode](https://img.shields.io/badge/chat-on%20freenode-blue.svg?style=flat)](https://kiwiirc.com/client/chat.freenode.net/#horizonlauncher)

Build statuses are down at the moment, but they will return shortly.

This repository is based on the Horizon Launcher client repository.

The borderless window system for Windows is pulled from deimos1877's [BorderlessWindow](http://github.com/deimos1877/BorderlessWindow). Horizon Launcher also contains code from its predescessor [Project Ascension](https://github.com/Proj-Ascension).

If you have any questions, feel free to join us on [Slack](http://slack.launchhorizon.com) or [IRC](https://kiwiirc.com/client/chat.freenode.net/#horizonlauncher).

# License
This project is licensed under the MIT License.

Full license can be viewed [here](LICENSE).

# Contributing
If you would like to contribute, please read over [the contributing guidelines](CONTRIBUTING.md)
