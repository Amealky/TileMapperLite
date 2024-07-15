#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QFileDialog>
#include <string>
#include "dialogs/MapSizeDialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newMap();
    void loadMap();
    void saveMap();
    void resizeMap();
    void exportMapAsImage();
    void askForSave();
    void loadTileset();


private:
    Ui::MainWindow *ui;
    int tilesize;

private slots:

    void positionLabelUpdate(int x, int y);

    void onTileSelectedInTileset(QPixmap tileImage, QString tileValue);

    void on_btn_new_map_clicked();

    void on_btn_load_map_clicked();

    void on_btn_save_map_clicked();

    void on_btn_resize_map_clicked();

    void on_btn_export_map_clicked();

    void on_btn_import_tileset_clicked();

    void on_checkbox_grid_toggled(bool checked);

    void on_rb_layout_all_toggled(bool checked);

    void on_rb_layout_back_toggled(bool checked);

    void on_rb_layout_mid_toggled(bool checked);

    void on_rb_layout_front_toggled(bool checked);


};

#endif // MAINWINDOW_H
