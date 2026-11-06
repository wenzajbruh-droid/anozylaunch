#include "store.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QUrl>
#include <QPushButton>

#ifdef Q_OS_ANDROID
    #include <QDesktopServices>
#endif

#define HORIZON_STORE_URL "http://store.launchhorizon.com/"

Store::Store(QSettings* p, QWidget* parent)
    : QWidget(parent)
{
    this->setStyleSheet("color: "+ p->value("Primary/LightText").toString() + ";");

    init();
}

#ifdef Q_OS_ANDROID

/** Android: QtWebKit doesn't exist here, so the store opens in the system browser. */
void Store::init()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addStretch();

    urlLabel = new QLabel(tr("The Horizon store opens in your browser."));
    urlLabel->setAlignment(Qt::AlignHCenter);
    urlLabel->setWordWrap(true);
    layout->addWidget(urlLabel);

    QPushButton* openBtn = new QPushButton(tr("Open store"));
    openBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addWidget(openBtn, 0, Qt::AlignHCenter);

    layout->addStretch();

    connect(openBtn, &QPushButton::clicked, []
    {
        QDesktopServices::openUrl(QUrl(HORIZON_STORE_URL));
    });
}

void Store::changeUrlLabel()
{
    // Nothing to update: there is no embedded page on Android.
}

#else

void Store::init()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    QWidget* controlsWidget = new QWidget();
    layout->addWidget(controlsWidget);

    QHBoxLayout* controlsLayout = new QHBoxLayout(controlsWidget);
    //controlsLayout->setMargin(5);

    QPixmap back(":/res/icon/Material/NavArrowLeft.svg");
    QIcon backIcon(back);
    QPixmap forward(":/res/icon/Material/NavArrowRight.svg");
    QIcon forwardIcon(forward);

    QPushButton* backBtn = new QPushButton("");
    backBtn->setIcon(backIcon);
    backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    controlsLayout->addWidget(backBtn);

    QPushButton* forwardBtn = new QPushButton("");
    forwardBtn->setIcon(forwardIcon);
    forwardBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    controlsLayout->addWidget(forwardBtn);

    urlLabel = new QLabel();
    urlLabel->setAlignment(Qt::AlignHCenter);
    urlLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    controlsLayout->addWidget(urlLabel);

    webView = new QWebView();
    webView->setContentsMargins(0,0,0,0);
    webView->load(QUrl(HORIZON_STORE_URL));
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(webView);

    connect(webView, &QWebView::loadStarted, this, &Store::changeUrlLabel);
    connect(webView, &QWebView::loadProgress, this, &Store::changeUrlLabel);
    connect(webView, &QWebView::loadFinished, this, &Store::changeUrlLabel);

    connect(backBtn, &QPushButton::clicked, webView, &QWebView::back);
    connect(forwardBtn, &QPushButton::clicked, webView, &QWebView::forward);
}

void Store::changeUrlLabel()
{
    urlLabel->setText(webView->url().toString());
}

#endif
