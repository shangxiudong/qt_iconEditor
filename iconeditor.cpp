#include "iconeditor.h"
#include <QPainter>
#include <QPaintEvent>

IconEditor::IconEditor(QWidget *parent):
    zoom(1),
    m_color(qRgba(255,0,0,0))
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_image = QImage(16, 16, QImage::Format_RGB32);
    m_image.fill(QColor(255,255,255,0));
}

void IconEditor::setImage(const QString path)
{
    QImage tmpimage(path);
    m_image = tmpimage.convertToFormat(QImage::Format_RGB32);
    update();
    updateGeometry();
}

void IconEditor::setZoomFactor(int factor)
{
    if(factor <1)
        factor = 1;
    if(factor != zoom) {
        zoom = factor;
    }
    update();
}

void IconEditor::setPenColor(const QColor &newColor)
{
    if(m_color != newColor) {
        m_color = newColor;
    }
}

void IconEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //画网格线
    if(zoom >=3) {
        painter.setPen(palette().foreground().color());
        painter.setPen(QColor(Qt::black));
        for(int i = 0; i < m_image.width(); ++i) {
            painter.drawLine(i*zoom, 0, i*zoom, m_image.height()*zoom);
        }
        for(int j = 0; j < m_image.height(); ++j) {
            painter.drawLine(0, j*zoom, m_image.width()*zoom, j * zoom);
        }
    }
    //画图
    for(int i = 0; i < m_image.width(); ++i) {
        for(int j = 0; j < m_image.height(); ++j) {
            if(event->region().intersects(pixelRect(i, j))) {
                QColor color = m_image.pixelColor(i, j);
                painter.fillRect(pixelRect(i, j), color);
            }
        }
    }
}

void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->button() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->buttons() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

QRect IconEditor::pixelRect(int i, int j)
{
    if(zoom >=3) {
        return QRect(i * zoom +1, j *zoom +1, zoom -1, zoom -1);
    } else
        return QRect(i, j, zoom, zoom);
}

void IconEditor::setImagePixel(QPoint area, bool opaque)
{
    int i = area.x()/zoom;
    int j = area.y()/zoom;
    if (m_image.rect().contains(i, j)) {
        if(opaque)
            m_image.setPixel(i, j, m_color.rgba());
        else {
            m_image.setPixel(i, j, qRgba(0,0,0,0));
        }
        update(pixelRect(i, j));
    }
}
