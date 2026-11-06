#include "gamelauncher.h"

#include <QMessageBox>

#ifdef Q_OS_ANDROID
    #include <QtAndroid>
    #include <QAndroidJniObject>
    #include <QAndroidJniEnvironment>
#endif

#ifdef Q_OS_ANDROID

/** Start an installed Android app by its package name.
 * \param packageName Package name of the app, e.g. "com.example.game".
 * \return true if the launch Intent was found and started, false otherwise.
*/
bool GameLauncher::launchAndroidPackage(const QString& packageName)
{
    QAndroidJniEnvironment env;

    QAndroidJniObject activity = QtAndroid::androidActivity();
    if (!activity.isValid())
    {
        return false;
    }

    QAndroidJniObject packageManager = activity.callObjectMethod(
        "getPackageManager", "()Landroid/content/pm/PackageManager;");
    if (!packageManager.isValid())
    {
        return false;
    }

    QAndroidJniObject jPackageName = QAndroidJniObject::fromString(packageName.trimmed());
    QAndroidJniObject intent = packageManager.callObjectMethod(
        "getLaunchIntentForPackage",
        "(Ljava/lang/String;)Landroid/content/Intent;",
        jPackageName.object<jstring>());

    if (env->ExceptionCheck())
    {
        env->ExceptionClear();
        return false;
    }
    if (!intent.isValid())
    {
        // Not installed, or the app has no launchable activity.
        return false;
    }

    // FLAG_ACTIVITY_NEW_TASK
    intent.callObjectMethod("addFlags", "(I)Landroid/content/Intent;", 0x10000000);
    activity.callMethod<void>("startActivity", "(Landroid/content/Intent;)V", intent.object<jobject>());

    if (env->ExceptionCheck())
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return false;
    }

    return true;
}

#endif // Q_OS_ANDROID

/** Launch a game.
 * Desktop: start a new QProcess using the passed exe and working directory.
 * Android: start the installed app whose package name is passed in \a file.
 * \param file Location of the exe to run (Android: package name of the app).
 * \param workingDirectory The directory that QProcess should spawn in (ignored on Android).
*/
void GameLauncher::runProcess(QString file, QString workingDirectory)
{
#ifdef Q_OS_ANDROID
    Q_UNUSED(workingDirectory);

    if (!launchAndroidPackage(file))
    {
        QMessageBox(QMessageBox::Critical, tr("Error"),
                    tr("Could not start the game. Please double check that the app is installed and that you entered the correct package name.")).exec();
    }
#else
    // TODO: Implement some threading
    QProcess* runningProcess = new QProcess(this);
    connect(runningProcess, (void (QProcess::*) (int, QProcess::ExitStatus)) &QProcess::finished, this, &GameLauncher::finished);
    connect(runningProcess, (void (QProcess::*) (QProcess::ProcessError)) &QProcess::error, this, &GameLauncher::onLaunchError);
    runningProcess->setWorkingDirectory(workingDirectory);
    runningProcess->setStandardErrorFile("error.txt");
    runningProcess->setStandardOutputFile("log.txt");
    runningProcess->start(file, QStringList());
    runningProcess->waitForStarted();
#endif
}

/** Launch a game with arguments.
 * Desktop: start a new QProcess using the passed exe and working directory.
 * Android: command-line arguments don't exist for apps, so \a args is ignored.
 * \param file Location of the exe to run (Android: package name of the app).
 * \param workingDirectory The directory that QProcess should spawn in (ignored on Android).
 * \param args String of arguments to launch the executable with.
*/
void GameLauncher::runProcessWithArgs(QString file, QString workingDirectory, QString args)
{
#ifdef Q_OS_ANDROID
    Q_UNUSED(args);
    runProcess(file, workingDirectory);
#else
    // TODO: Implement some threading
    QProcess* runningProcess = new QProcess(this);
    connect(runningProcess, (void (QProcess::*) (int, QProcess::ExitStatus)) &QProcess::finished, this, &GameLauncher::finished);
    connect(runningProcess, (void (QProcess::*) (QProcess::ProcessError)) &QProcess::error, this, &GameLauncher::onLaunchError);
    runningProcess->setWorkingDirectory(workingDirectory);
    runningProcess->setStandardErrorFile("error.txt");
    runningProcess->setStandardOutputFile("log.txt");
    runningProcess->start(file, QStringList(args.split(" ")));
    runningProcess->waitForStarted();
#endif
}

/** Attempt to handle process ending unexpectedly or fork.
 * \param exitCode Exit code to check.
 * \param exitStatus Status to check.
*/
void GameLauncher::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode != 0)
    {
        QMessageBox(QMessageBox::Warning, tr("Warning"), tr("The game finished, but it claims to have encountered an error")).exec();
    }
}

/** Handle errors before the process has launched.
 * \param error The error to translate.
*/
void GameLauncher::onLaunchError(QProcess::ProcessError error)
{
    switch (error)
    {
        case QProcess::FailedToStart:
            QMessageBox(QMessageBox::Critical, tr("Error"), tr("Could not start the game. Please double check that you are using the correct file to launch it.")).exec();
            break;
        case QProcess::Crashed:
            QMessageBox(QMessageBox::Warning, tr("Crash!"), tr("The launched game has crashed")).exec();
            break;
        default:
            // Other cases are errors unrelated to startup, so let's not handle them
            break;
    }
}
