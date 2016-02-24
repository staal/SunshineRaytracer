#include "generaltab.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

namespace sunshine {


// *****************************************************************************
GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
{
    //Path
    auto outLabel = new QLabel(tr("Output Path:"));
    auto outEdit = new QLineEdit();
    auto outBrowse = new QPushButton(tr("..."));
    outBrowse->setMaximumWidth(25);
    outLabel->setBuddy(outEdit);

    auto *outLayout = new QHBoxLayout();
    outLayout->addWidget(outEdit);
    outLayout->addWidget(outBrowse);

    auto widthSpin = new QSpinBox();
    widthSpin->setMaximum(100000);
    auto widthLabel = new QLabel(tr("Image Width:"));
    widthLabel->setBuddy(widthSpin);

    auto heightSpin = new QSpinBox();
    heightSpin->setMaximum(100000);
    auto heightLabel = new QLabel(tr("Image Height:"));
    heightLabel->setBuddy(heightSpin);

    //Grid layout
    auto *gridLayout = new QGridLayout();
    gridLayout->addWidget(outLabel, 0, 0, 1, 1);
    gridLayout->addLayout(outLayout,0,1);

    gridLayout->addWidget(widthLabel, 1, 0, 1, 1);
    gridLayout->addWidget(widthSpin, 1, 1, 1, 1,Qt::AlignRight);

    gridLayout->addWidget(heightLabel, 2, 0, 1, 1);
    gridLayout->addWidget(heightSpin, 2, 1, 1, 1, Qt::AlignRight);

    gridLayout->setSpacing(5);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addItem(gridLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}


} // namespace sunshine