#ifndef FLOATINGWIDGET_H
#define FLOATINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>

#include "FloatingSettings.h"

class QLabel;

class FloatingWidget : public QWidget {
public:
    int cur_height = 0;
    int cur_width = 0;
    FloatingWidget(QWidget *parent = nullptr);
    void setWidget(QWidget *widget);
    void setSettings(QWidget *widget);
    int settingsOffset = 0;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    int num_of_item = 0;
    void moveAction(int new_x, int new_y);
    FloatingSettings* floatingSettings;
    QPoint dragPosition;
    QLabel *label;
    QVBoxLayout *layout;
};

#endif // FLOATINGWIDGET_H
