#include "androidwindow.h"

#include <QVBoxLayout>

AndroidWindow::AndroidWindow()
{
    setObjectName("androidWindow");

    mainPanel = new AndroidPanel(this);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);
    layout->addWidget(mainPanel);

    mainPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    showFullScreen();
}

void AndroidWindow::minimize()
{
    showMinimized();
}

void AndroidWindow::maximize()
{
    // Always full screen on Android
    showFullScreen();
}

void AndroidWindow::closeWindow()
{
    this->close();
}
