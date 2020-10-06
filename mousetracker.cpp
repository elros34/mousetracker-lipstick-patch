#include "mousetracker.h"
#include <QMouseEvent>

MouseTracker::MouseTracker(QObject *parent) :
    QObject(parent),
    m_target(nullptr),
    m_mouseX(-1),
    m_mouseY(-1),
    m_mouseActive(false),
    m_pressed(false)
{
}

void MouseTracker::setTarget(QObject *target)
{
    if (m_target == target)
        return;
    if (m_target)
        m_target->removeEventFilter(this);
    m_target = target;
    if (target)
        m_target->installEventFilter(this);
}

bool MouseTracker::eventFilter(QObject *watched, QEvent *e)
{
    if (e->type() != QEvent::SockAct && e->type() != QEvent::Timer &&
        e->type() != QEvent::UpdateRequest && e->type() != QEvent::MetaCall)
        qDebug() << watched << "type: " << e->type();

    if (watched != m_target)
        return false;

    switch (e->type()) {
    case QMouseEvent::MouseMove: {
        if (!m_mouseActive)
            setMouseActive(true);

        QMouseEvent *event = static_cast<QMouseEvent*>(e);
        setMouseX(event->x());
        setMouseY(event->y());
        break;
    }
    // FIXME: something sends MouseButtonPress without release on unlock
    case QMouseEvent::MouseButtonPress: {
        QMouseEvent *event = static_cast<QMouseEvent*>(e);
        if (event->button() == Qt::MiddleButton)
            emit middleButtonPressed();
        setPressed(true);
        break;
    }
    case QMouseEvent::MouseButtonRelease: {
        setPressed(false);
        break;
    }
    case QMouseEvent::TouchBegin: {
        if (m_mouseActive)
            setMouseActive(false);
        break;
    }
    case QMouseEvent::Wheel: {
        emit wheelRolled();
        break;
    }
    default:
        return false;
    }
    return false;
}

int MouseTracker::mouseX() const
{
    return m_mouseX;
}

void MouseTracker::setMouseX(int mouseX)
{
    m_mouseX = mouseX;
    emit mouseXChanged();
}

int MouseTracker::mouseY() const
{
    return m_mouseY;
}

void MouseTracker::setMouseY(int mouseY)
{
    m_mouseY = mouseY;
    emit mouseYChanged();
}

bool MouseTracker::mouseActive() const
{
    return m_mouseActive;
}

void MouseTracker::setMouseActive(bool mouseActive)
{
    if (m_mouseActive == mouseActive)
        return;
    m_mouseActive = mouseActive;
    emit mouseActiveChanged();
}

QObject *MouseTracker::target() const
{
    return m_target;
}

bool MouseTracker::pressed() const
{
    return m_pressed;
}

void MouseTracker::setPressed(bool pressed)
{
    m_pressed = pressed;
    emit pressedChanged();
}
