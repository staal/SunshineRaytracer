#include "renderdialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>

namespace sunshine {

RenderDialog::RenderDialog(QWidget *parent)
    : QDialog(parent)
{
    resize(400, 300);

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
    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(tabWidget);
    mainLayout->addStretch();
    mainLayout->addItem(buttonLayout);

    setLayout(mainLayout);
}


} // namespace sunshine