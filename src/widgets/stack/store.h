#ifndef STORE_H
#define STORE_H

#include <QWidget>
#include <QLabel>
#include <QSettings>

// QtWebKit is not available on Android, so the embedded browser is desktop-only.
#ifndef Q_OS_ANDROID
    #include <QWebView>
#endif

class Store : public QWidget
{
    Q_OBJECT

public:
    Store(QSettings* p, QWidget* parent = 0);

private:
    void init();
    QLabel* urlLabel;
#ifndef Q_OS_ANDROID
    QWebView* webView;
#endif

private slots:
    void changeUrlLabel();
};

#endif
