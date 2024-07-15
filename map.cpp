#include "map.h"

Map::Map()
{
    //mpview = new MapView(this);
     beginx = 0;
     beginy = 0;

     startX = 0;
     startY = tilesize;

     finMapX = 0;
     finMapY = 0;

}

void Map::initSize(int maxX, int maxY, int tileSize) {
    mapSizeX = maxX;
    mapSizeY = maxY;
    this->tilesize = tileSize;

    mapSizeInPixelX = mapSizeX * tilesize;
    mapSizeInPixelY = mapSizeY * tilesize;

    tileLayout1.clear();
    tileLayout2.clear();
    tileLayout3.clear();

    for(int i = 0; i <= mapSizeX; i++)
    {
        tileLayout1.push_back(vector<QString>(mapSizeY));
        tileLayout2.push_back(vector<QString>(mapSizeY));
        tileLayout3.push_back(vector<QString>(mapSizeY));
        for(int j = 0; j < mapSizeY; j++)
        {
            tileLayout1[i][j] = tileLayout2[i][j] = tileLayout3[i][j] = "0";

        }
    }
}


