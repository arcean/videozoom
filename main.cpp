#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>
#include <MButton>
#include <MToolBar>
#include <MAction>
#include <MWidgetAction>
#include <MTextEdit>
#include <QObject>
#include <MExport>
#include <MComponentCache>

#include "mainpage.h"

M_EXPORT int main(int argc, char *argv[]){
    MApplication* application = MComponentCache::mApplication(argc, argv);
    application->setOrganizationName("arcean");
    application->setOrganizationDomain("arcean.com");
    application->setApplicationName("videozoom");

    MApplicationWindow* window = MComponentCache::mApplicationWindow();
    MainPage page;

    page.appear(window);

    window->showFullScreen();

    return application->exec();
 }
