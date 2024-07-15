#ifndef TILEGRAPHICSVIEW_H
#define TILEGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QScrollBar>
#include <QMouseEvent>
#include <QPen>


class TileGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TileGraphicsView(QWidget *parent = 0);
    void initSceneRect(int contentSizeX, int contentSizeY);
    virtual void drawContent() {};
    void drawGrid();
    void onGridChecked(bool checked);


protected:
    virtual void mouseMoveEvent(QMouseEvent *evt) override;

    bool gridEnabled;
    int tileSize;
    int sceneSizeX;
    int sceneSizeY;

    QGraphicsScene *scene;
    QPixmap tileActiveImage;
    QString tileActiveValue;

private:
    void scrollContentsBy(int dx, int dy) override;

};


#endif // TILEGRAPHICSVIEW_H
