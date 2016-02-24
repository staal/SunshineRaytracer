#ifndef SUNSHINE_RENDER_TAB_H_
#define SUNSHINE_RENDER_TAB_H_

#include <QWidget>

namespace sunshine {


class RenderTab : public QWidget {
    Q_OBJECT

public:
    RenderTab(QWidget *parent = nullptr);
};


} // namespace sunshine
#endif // !SUNSHINE_RENDER_TAB_H_