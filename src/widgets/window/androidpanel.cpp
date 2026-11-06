#include "androidpanel.h"
#include "androidwindow.h"

#include <QScroller>
#include <QScrollArea>

AndroidPanel::AndroidPanel(AndroidWindow* window)
    : MainPanel((QWidget*) window),
      androidWindow(window)
{
    // The scroll bars are hidden in MainPanel, so enable finger-drag scrolling.
    QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);

    this->adjustSize();
}

void AndroidPanel::pushButtonMinimize()
{
    androidWindow->minimize();
}

void AndroidPanel::pushButtonMaximize()
{
    androidWindow->maximize();
}

void AndroidPanel::pushButtonClose()
{
    androidWindow->closeWindow();
}
