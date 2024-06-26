#include "FloatingWidget.h"
#include "FloatingSettings.h"
extern int screenWidth;
extern int screenHeight;

int new_x;
int new_y;

extern int padding;

extern "C" {
#include "settings.h"
}

#ifdef QT5
#define globalPosition globalPos
#endif

FloatingWidget::FloatingWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    setLayout(layout);
    QString style = QString(
    "QWidget {"
        "border-radius:13px;"
        "background-color: #cc939393;"
    "}");
    layout->setSpacing(padding);
    layout->setContentsMargins(padding, padding, padding, padding);
    setStyleSheet(style);
    cur_height = padding;
    new_x = get_int((char*)"cur-x");
    new_y = get_int((char*)"cur-y");
}


void FloatingWidget::setSettings(QWidget *widget) {
    floatingSettings = (FloatingSettings*)widget;
}

void FloatingWidget::setWidget(QWidget *widget) {
    cur_height += widget->size().height() + padding;
    if (cur_width < widget->size().width()) {
        cur_width = widget->size().width() + padding*2;
    }
    num_of_item++;
    setFixedSize(cur_width, cur_height);
    layout->addWidget(widget);
    moveAction();
}

void FloatingWidget::mousePressEvent(QMouseEvent *event) {
    offset_x = abs(event->globalPosition().x() - new_x);
    offset_y = abs(event->globalPosition().y() - new_y);
}

void FloatingWidget::mouseReleaseEvent(QMouseEvent *event) {
    (void)(event); // fix unused warning
    offset_x =-1;
    offset_y =-1;
    set_int((char*)"cur-x", new_x);
    set_int((char*)"cur-y", new_y);
}

void FloatingWidget::moveAction(){
        if (new_x < 0) {
            new_x = 0;
        }if (new_y < 0) {
            new_y = 0;
        }if (new_x > screenWidth - cur_width) {
            new_x = screenWidth - cur_width;
        }if (new_y > screenHeight - cur_height) {
            new_y = screenHeight - cur_height;
        }
        move(new_x, new_y);
        if(floatingSettings != NULL){
            int new_xx = new_x+padding+cur_width;
            if(new_xx  > screenWidth - floatingSettings->cur_width){
                new_xx = new_x - padding - floatingSettings->cur_width;
            }
            int new_yy = new_y + (cur_height / num_of_item) * settingsOffset;
            if (new_yy > screenHeight - floatingSettings->cur_height) {
                new_yy = screenHeight - floatingSettings->cur_height;
            }
            if(new_yy + floatingSettings->cur_height > new_y + cur_height) {
                new_yy = new_y + cur_height - floatingSettings->cur_height - padding;
            }
            floatingSettings->move(new_xx, new_yy + padding);
        }
}

void FloatingWidget::setFloatingOffset(int offset){
    settingsOffset = offset;
    moveAction();
}

void FloatingWidget::mouseMoveEvent(QMouseEvent *event) {
    if(offset_x < 0 || offset_y < 0){
        return;
    }
    if (event->buttons() & Qt::LeftButton) {
        new_x = event->globalPosition().x() - offset_x;
        new_y = event->globalPosition().y() - offset_y;
        moveAction();
        event->accept();
    }
}
