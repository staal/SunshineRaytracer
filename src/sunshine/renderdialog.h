#ifndef SUNSHINE_RENDER_DIALOG_H_
#define SUNSHINE_RENDER_DIALOG_H_

#include <QDialog>

namespace sunshine {


class RenderDialog : public QDialog
{
    Q_OBJECT

public:
    RenderDialog(QWidget *parent = nullptr);
};


} // namespace sunshine
#endif // !SUNSHINE_RENDER_DIALOG_H_