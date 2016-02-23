#include "renderdialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTabWidget>

#include "generaltab.h"
#include "rendertab.h"

namespace sunshine {


// *****************************************************************************
RenderDialog::RenderDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint | Qt::WindowTitleHint)
{
    resize(400, 300);

    //TabWidget
    auto tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralTab(), tr("General"));
    tabWidget->addTab(new RenderTab(), tr("Renderer"));

    //ButtonBox
    auto closeButton = new QPushButton(tr("Close"));
    auto cancelButton = new QPushButton(tr("Cancel")); 
    auto applyButton = new QPushButton(tr("Apply"));
    auto renderButton = new QPushButton(tr("Render"));
    renderButton->setDefault(true);

    //Render button
    auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(renderButton);
    buttonLayout->addSpacing(10);
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(applyButton);

    //Main layout
    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addItem(buttonLayout);

    setLayout(mainLayout);
}


} // namespace sunshine