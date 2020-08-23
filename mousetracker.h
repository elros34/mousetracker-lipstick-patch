#ifndef MOUSETRACKER_H
#define MOUSETRACKER_H

#include <QObject>

class QScreen;
class MouseTracker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *target READ target WRITE setTarget)
    Q_PROPERTY(int mouseX READ mouseX NOTIFY mouseXChanged)
    Q_PROPERTY(int mouseY READ mouseY NOTIFY mouseYChanged)
    Q_PROPERTY(bool mouseActive READ mouseActive NOTIFY mouseActiveChanged)
    Q_PROPERTY(bool pressed READ pressed NOTIFY pressedChanged)
public:
    explicit MouseTracker(QObject *parent = nullptr);

    QObject *target() const;
    void setTarget(QObject *target);

    int mouseX() const;
    void setMouseX(int mouseX);

    int mouseY() const;
    void setMouseY(int mouseY);

    bool mouseActive() const;
    void setMouseActive(bool mouseActive);

    bool pressed() const;
    void setPressed(bool pressed);

    Qt::ScreenOrientation orientation() const;
    void setOrientation(const Qt::ScreenOrientation &orientation);

private:
    QObject *m_target;
    int m_mouseX;
    int m_mouseY;
    bool m_mouseActive;
    bool m_pressed;

private:
    bool eventFilter(QObject *watched, QEvent *e);

signals:
    void mouseXChanged();
    void mouseYChanged();
    void mouseActiveChanged();
    void pressedChanged();
    void middleButtonPressed();
    void wheelRolled();
};

#endif // MOUSETRACKER_H
