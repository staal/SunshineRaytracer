#ifndef SUNSHINE_RENDER_SETTINGS_DIALOG_H_
#define SUNSHINE_RENDER_SETTINGS_DIALOG_H_

#include <QWidget>
#include <QDialog>

namespace sunshine {


class RenderSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    RenderSettingsDialog(QWidget *parent = nullptr);

signals:
    void render();
};


} // namespace sunshine
#endif // !SUNSHINE_RENDER_SETTINGS_DIALOG_H_