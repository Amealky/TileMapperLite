#ifndef MAP_H
#define MAP_H

#include <QImage>
#include <QPixmap>
#include <QString>

using namespace std;

class Map
{
public:
    Map();

    void initSize(int maxX, int maxY, int tileSize);
    void changeSize(int newMaxX, int newMaxY);

    vector<vector<QString>> tileLayout1;
    vector<vector<QString>> tileLayout2;
    vector<vector<QString>> tileLayout3;


    QPixmap tilesetTexture;
    QPixmap tileActive;

    int mapSizeX = 0;
    int mapSizeY = 0;
    int mapSizeInPixelX = 0;
    int mapSizeInPixelY = 0;

    int tilesize = 32;

};

#endif // MAP_H
