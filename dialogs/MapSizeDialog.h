#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H

#include <QDialog>

namespace Ui {
    class MapSizeDialog;
}

class MapSizeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MapSizeDialog(QWidget *parent = nullptr);
    ~MapSizeDialog();

    int getSizeX();
    int getSizeY();
    void setDefaultValue(int defaultSizeX, int defaultSizeY);

private:
    Ui::MapSizeDialog *ui;
};

#endif // NEWMAPDIALOG_H
