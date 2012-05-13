#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <MApplicationPage>
#include <MDialog>
#include <QColor>
#include <MAction>
#include <MWidgetAction>
#include <MLabel>
#include <MBanner>
#include "process.h"

/* To enable debug msgs: */
/* -output-level debug */

class MainPage : public MApplicationPage {
    Q_OBJECT
public:
    MainPage(QGraphicsItem *parent = 0);

protected:
    virtual void createContent();

public slots:

private slots:
    void showAboutDialog();
    void showQueryDialog();

    void queryDialogAccepted();
    void queryDialogRejected();

private:
    void throwMessage(const QString &text);
    void setInstallButtonText();

    MBanner *infoBanner;
    MButton *installButton;
    MButton *aboutButton;

    Process *process;
    // If TRUE - be ready to install mod, otherwise uninstall
    bool installation;

};

#endif // MAINPAGE_H
