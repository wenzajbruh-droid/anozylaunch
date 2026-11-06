#ifndef ANDROIDWINDOW_H
#define ANDROIDWINDOW_H

#include "androidpanel.h"

/** Top-level window for Android.
 * Android apps are always full screen, so unlike UnixWindow there is no
 * custom title bar, dragging, or fixed window size.
 */
class AndroidWindow : public QWidget
{
    Q_OBJECT

public:
    AndroidWindow();

    void minimize();
    void maximize();
    void closeWindow();

private:
    AndroidPanel* mainPanel;
};

#endif
