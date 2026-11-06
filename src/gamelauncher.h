#ifndef GAMELAUNCHER_H
#define GAMELAUNCHER_H

#include <QProcess>
#include <QObject>

/** GameLauncher class
 * Class to handle launching games
 *
 * On desktop a game is an executable started through QProcess.
 * On Android a "game" is an installed app: the stored executable path is
 * treated as the app's package name and started through an Intent.
 */
class GameLauncher : public QObject
{
    Q_OBJECT

public:
    void runProcess(QString file, QString workingDirectory);
    void runProcessWithArgs(QString file, QString workingDirectory, QString args);

private:
#ifdef Q_OS_ANDROID
    bool launchAndroidPackage(const QString& packageName);
#endif

private slots:
    void onLaunchError(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif //GAMELAUNCHER_H
