#include <MLinearLayoutPolicy>
#include <QGraphicsLinearLayout>
#include <MButton>
#include <MLayout>
#include <MToolBar>
#include <MAction>
#include <MTextEdit>
#include <MSceneWindow>
#include <QDebug>
#include <MApplication>
#include <MOnDisplayChangeEvent>
#include <MApplicationWindow>
#include <MTheme>
#include <QGraphicsGridLayout>
#include <MGridLayoutPolicy>
#include <MImageWidget>
#include <MPannableViewport>
#include <MSeparator>
#include <QGraphicsItem>
#include <MMessageBox>
#include <math.h>

#include "mainpage.h"
#include "process.h"

class ViewHeader : public MWidgetController
{
public:
    ViewHeader(QGraphicsItem *parent = 0) :
        MWidgetController(parent),
        linearLayout(0),
        titleWidget(0)
    {
        setStyleName("CommonHeaderPanel");
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        linearLayout = new QGraphicsLinearLayout(Qt::Horizontal, this);
        titleWidget = new MLabel(this);
        titleWidget->setTextElide(true);
        titleWidget->setStyleName("CommonHeaderInverted");
        linearLayout->addItem(titleWidget);
    }

    void setTitle(const QString &title)
    {
        titleWidget->setText(title);
    }

private:
    QGraphicsLinearLayout *linearLayout;
    MLabel *titleWidget;

};

MainPage::MainPage(QGraphicsItem *parent)
    : MApplicationPage(parent)
{

}

void MainPage::createContent()
{
    MTheme *theme = MTheme::instance();
    theme->loadCSS("/opt/videozoom/style/videozoom.css");
    applicationWindow()->setStyleName("CommonApplicationWindowInverted");
    setStyleName("CommonApplicationPageInverted");
    MLayout *layout = new MLayout(this);

    /////////////////////////////////////////////////// HEADER VIEW

    /* Fix: lock page content */
    setPannable(false);
    MPannableViewport *viewport = this->pannableViewport();
    viewport->setAutoRange(false);
    viewport->setRange(QRectF(0,0,0,0));

    ViewHeader *header = new ViewHeader;
    header->setTitle("VideoZoom");

    MLinearLayoutPolicy *portraitPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPortraitPolicy(portraitPolicy);
    portraitPolicy->setContentsMargins(0, 0, 0, 0);
    portraitPolicy->setSpacing(0);
    portraitPolicy->setNotifyWidgetsOfLayoutPositionEnabled(true);
    // Create main app viewport
    MPannableViewport *viewportWidget = new MPannableViewport;
    // Create layout for the main app viewport
    MLayout *viewportLayout = new MLayout();
    // Create widget for integrating the layout with the viewport
    QGraphicsWidget *form = new QGraphicsWidget();
    form->setLayout(viewportLayout);
    viewportWidget->setWidget(form);
    // Create layout policy for the main app viewport
    MLinearLayoutPolicy *viewportLayoutPolicy = new MLinearLayoutPolicy(viewportLayout, Qt::Vertical);
    // Add header to the layout
    portraitPolicy->addItem(header);
    // Add viewportWidget to layout (main layout)
    portraitPolicy->addItem(viewportWidget);

    /////////////////////////////////////////////////// CONTENT

    MLabel *textDesc = new MLabel(qtTrId("Nokia N9's default video recording application doesn't allow to <b>ZOOM IN/OUT</b> during"
                                     " video recording. This modification will enable such functionality. Just press <b>Install modification</b> button."));
    textDesc->setStyleName("CommonBodyTextInverted");
    textDesc->setAlignment(Qt::AlignCenter);
    textDesc->setWordWrap(true);
    textDesc->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    installButton = new MButton("Install modification");
    installButton->setStyleName("CommonSingleButtonInverted");
    aboutButton = new MButton(this);
    aboutButton->setIconID ("icon-s-description-inverse");
    aboutButton->setViewType (MButton::iconType);
    aboutButton->setStyleName("CommonRightIcon");

    QGraphicsLinearLayout *verticalDescText = new QGraphicsLinearLayout(Qt::Horizontal);
    verticalDescText->addStretch();
    verticalDescText->addItem(textDesc);
    verticalDescText->addStretch();

    QGraphicsLinearLayout *verticalInstallButton = new QGraphicsLinearLayout(Qt::Horizontal);
    verticalInstallButton->addStretch();
    verticalInstallButton->addItem(installButton);
    verticalInstallButton->addStretch();

    QGraphicsLinearLayout *verticalAboutButton = new QGraphicsLinearLayout(Qt::Horizontal);
    verticalAboutButton->addStretch();
    verticalAboutButton->addItem(aboutButton);
    verticalAboutButton->addStretch();

    QGraphicsLinearLayout *vertical = new QGraphicsLinearLayout(Qt::Vertical);
    vertical->addStretch();
    vertical->addItem(verticalDescText);
    vertical->addStretch();
    vertical->addItem(verticalInstallButton);
    vertical->addStretch();
    vertical->addItem(verticalAboutButton);
    vertical->addStretch();

    viewportLayoutPolicy->addItem(vertical);

    /////////////////////////////////////////////////// SIGNALS
    connect(aboutButton, SIGNAL(clicked()), this, SLOT(showAboutDialog()));
    connect(installButton, SIGNAL(clicked()), this, SLOT(showQueryDialog()));

    /////////////////////////////////////////////////// OTHER
    // Create info banner.
    infoBanner = new MBanner();
    // Create Proces object
    process = new Process();

    // Check if mod is installed
    installation = process->fileExists("/etc/camera.conf");

    // Set installButton text according to INSTALLATION value
    setInstallButtonText();
}

void MainPage::setInstallButtonText()
{
    if (installation) {
        // File exists, be ready to uninstall
        installButton->setText(qtTrId("Uninstall modification"));
    }
    else {
        // File does not exist, be ready to install
        installButton->setText(qtTrId("Install modification"));
    }
}

void MainPage::queryDialogAccepted()
{
    if (installation) {
        // File exists, be ready to uninstall
        process->removeFile("/etc/camera.conf");
        process->rebootPhone();
    }
    else {
        // File does not exist, be ready to install
        process->copyFile("/opt/videozoom/data/camera.conf", "/etc/camera.conf");
        process->rebootPhone();
    }
}

void MainPage::queryDialogRejected()
{
    //throwMessage("Rejected");
}

void MainPage::showQueryDialog()
{
    MMessageBox *messageBox = new MMessageBox("", M::YesButton|M::NoButton);

    messageBox->setTitle(qtTrId("Are you sure?"));
    if (installation)
        messageBox->setText(qtTrId("Are you sure that you want to <b>uninstall</b> system modification? Your device will be <b><font color=\"#6604BD\">rebooted</font></b>."));
    else
        messageBox->setText(qtTrId("Are you sure that you want to <b>install</b> system modification? Your device will be <b><font color=\"#6604BD\">rebooted</font></b>."));

    QPixmap icon("/opt/videozoom/data/dialog-question.png");
    messageBox->setIconPixmap(icon);

    connect(messageBox, SIGNAL(accepted()), this, SLOT(queryDialogAccepted()));
    connect(messageBox, SIGNAL(rejected()), this, SLOT(queryDialogRejected()));

    messageBox->appear(MSceneWindow::DestroyWhenDone);
}

void MainPage::showAboutDialog()
{
    MDialog *dialog = new MDialog("", M::CloseButton);

    const QChar CopyrightSymbol(0x00a9);

    QString text(qtTrId("VideoZoom modification for MeeGo 1.2 Harmattan.\n"));
    QString copyright_string(QString(CopyrightSymbol) + QString::fromUtf8(" 2012 Tomasz Pieniążek"));

    MLabel *textSystemModal= new MLabel(text + copyright_string);
    textSystemModal->setStyleName("CommonBodyTextInverted");
    textSystemModal->setAlignment(Qt::AlignCenter);
    textSystemModal->setWordWrap(true);
    textSystemModal->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    MLabel *title= new MLabel(qtTrId("VideoZoom 1.0"));
    title->setStyleName("title_label");
    title->setAlignment(Qt::AlignCenter);
    title->setWordWrap(true);
    title->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    QGraphicsLinearLayout *layoutDesc = new QGraphicsLinearLayout(Qt::Horizontal);
    layoutDesc->addStretch();
    layoutDesc->addItem(textSystemModal);
    layoutDesc->addStretch();

    QGraphicsLinearLayout *layoutTitle = new QGraphicsLinearLayout(Qt::Horizontal);
    layoutTitle->addStretch();
    layoutTitle->addItem(title);
    layoutTitle->addStretch();

    MImageWidget *image = new MImageWidget(new QPixmap("/usr/share/icons/hicolor/80x80/apps/videozoom.png"));

    QGraphicsLinearLayout *layout1 = new QGraphicsLinearLayout(Qt::Vertical);
    layout1->addItem(image);
    layout1->addItem(layoutTitle);
    layout1->addItem(layoutDesc);
    layout1->addStretch();

    dialog->centralWidget()->setLayout(layout1);
    dialog->setObjectName("about_dialog");

    dialog->appear(MSceneWindow::DestroyWhenDone);
}

void MainPage::throwMessage(const QString &text)
{
    infoBanner->setStyleName(MBannerType::InformationBanner);
    infoBanner->setTitle(text);
    infoBanner->appear(scene(), MSceneWindow::KeepWhenDone);
}
