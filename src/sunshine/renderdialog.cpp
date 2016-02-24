#include "renderdialog.h"

#include <QVBoxLayout>
#include <QProgressBar>
#include <QImage>
#include <QLabel>
#include <QPixmap>

namespace sunshine {


// *****************************************************************************
RenderDialog::RenderDialog(QWidget *parent)
    : QDialog(parent)
{
    auto image = new QImage(200, 200, QImage::Format_ARGB32);
    auto imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(*image));
    auto progressBar = new QProgressBar();
    progressBar->setValue(40);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(progressBar);

    setLayout(mainLayout);
}


} // namespace sunshine