#ifdef Q_OS_ANDROID
    // On Android the "generic" data location is shared storage, which apps can't write to freely.
    // Use the app-private data directory instead.
    #define CONFIG_FOLDER QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "HorizonLauncher"
#else
    #define CONFIG_FOLDER QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QDir::separator() + "HorizonLauncher"
#endif
