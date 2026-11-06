#ifndef ANDROIDPANEL_H
#define ANDROIDPANEL_H

#include "../mainpanel.h"

class AndroidWindow;

class AndroidPanel : public MainPanel
{
    Q_OBJECT

public:
    AndroidPanel(AndroidWindow* window);

public slots:
    void pushButtonMinimize();
    void pushButtonMaximize();
    void pushButtonClose();

private:
    AndroidWindow* androidWindow;
};

#endif
