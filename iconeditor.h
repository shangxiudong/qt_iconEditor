#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QColor>

class IconEditor : public QWidget
{
    Q_OBJECT

public:
    IconEditor(QWidget *parent = nullptr);
    ~IconEditor() = default;
    void setImage(const QString path);
    QImage image() const {return m_image;}
    void setZoomFactor(int factor);
    int getZoom() const { return zoom;}
    void setPenColor(const QColor &newColor);
    QColor penColor() const {return m_color;}

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private:
    QRect pixelRect(int i, int j);
    void setImagePixel(QPoint area, bool opaque);
    QImage m_image;
    int zoom;
    QColor m_color;
};

#endif // WIDGET_H
