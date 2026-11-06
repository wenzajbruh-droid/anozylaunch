# Qt for Android build of Horizon Launcher (Qt 5.15.x, qmake + androiddeployqt).
# The desktop build keeps using CMakeLists.txt.
#
# Build (see .github/workflows/android.yml for the full, automated version):
#   qmake HorizonLauncher-android.pro -spec android-clang CONFIG+=release ANDROID_ABIS=arm64-v8a
#   make -j$(nproc) && make INSTALL_ROOT=$PWD/android-build install
#   androiddeployqt --input android-HorizonLauncher-deployment-settings.json \
#                   --output android-build --android-platform android-30 --gradle

QT += core gui widgets network sql androidextras
CONFIG += c++11
TEMPLATE = app
TARGET = HorizonLauncher

INCLUDEPATH += src

SOURCES += \
    src/database.cpp \
    src/gamelauncher.cpp \
    src/main.cpp \
    src/steam/steamhelper.cpp \
    src/steam/steammetadatahelper.cpp \
    src/widgets/buddylist.cpp \
    src/widgets/buddylistexpandable.cpp \
    src/widgets/detailgamewidget.cpp \
    src/widgets/gamepropertyeditor.cpp \
    src/widgets/gridgamewidget.cpp \
    src/widgets/mainpanel.cpp \
    src/widgets/navbar/navbar.cpp \
    src/widgets/navbar/tablabel.cpp \
    src/widgets/navbar/tabwidget.cpp \
    src/widgets/newsfeedchooserwindow.cpp \
    src/widgets/newsitemwidget.cpp \
    src/widgets/stack/community.cpp \
    src/widgets/stack/homepage.cpp \
    src/widgets/stack/library.cpp \
    src/widgets/stack/news.cpp \
    src/widgets/stack/settings.cpp \
    src/widgets/stack/store.cpp \
    src/widgets/views/librarycarouselview.cpp \
    src/widgets/views/librarydetailview.cpp \
    src/widgets/views/librarygridview.cpp \
    src/widgets/window/androidpanel.cpp \
    src/widgets/window/androidwindow.cpp \
    src/widgets/wizards/addgamewizard.cpp \
    src/widgets/wizards/drmsetupwizard.cpp \
    src/widgets/wizards/setupwizard.cpp

HEADERS += \
    src/database.h \
    src/defines.h \
    src/gamelauncher.h \
    src/init.h \
    src/steam/steamhelper.h \
    src/steam/steammetadatahelper.h \
    src/widgets/buddylist.h \
    src/widgets/buddylistexpandable.h \
    src/widgets/detailgamewidget.h \
    src/widgets/gamepropertyeditor.h \
    src/widgets/gridgamewidget.h \
    src/widgets/mainpanel.h \
    src/widgets/navbar/navbar.h \
    src/widgets/navbar/tablabel.h \
    src/widgets/navbar/tabwidget.h \
    src/widgets/newsfeedchooserwindow.h \
    src/widgets/newsitemwidget.h \
    src/widgets/stack/community.h \
    src/widgets/stack/homepage.h \
    src/widgets/stack/library.h \
    src/widgets/stack/news.h \
    src/widgets/stack/settings.h \
    src/widgets/stack/store.h \
    src/widgets/views/librarycarouselview.h \
    src/widgets/views/librarydetailview.h \
    src/widgets/views/librarygridview.h \
    src/widgets/window/androidpanel.h \
    src/widgets/window/androidwindow.h \
    src/widgets/wizards/addgamewizard.h \
    src/widgets/wizards/drmsetupwizard.h \
    src/widgets/wizards/setupwizard.h

RESOURCES += \
    res/icon.qrc \
    res/font.qrc \
    res/styles.qrc \
    res/image.qrc

TRANSLATIONS += \
    Translations/horizon_da.ts \
    Translations/horizon_de.ts \
    Translations/horizon_es.ts \
    Translations/horizon_fr.ts \
    Translations/horizon_nb.ts \
    Translations/horizon_pl.ts \
    Translations/horizon_pt_BR.ts

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
