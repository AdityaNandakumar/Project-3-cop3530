#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtreewidget.h>
#include <set>
#include "hash.h"
#include "trie.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_random_data_button_clicked();

    void on_clear_button_clicked();

    void on_insert_button_clicked();

    void on_delete_button_clicked();

    void on_search_button_clicked();

private:
    Ui::MainWindow *ui;
    Hash_Table _table;
    Trie _tree;
    void draw_hash();
    void draw_trie();
    void draw_children(QTreeWidgetItem* parent, char name, Trie::node* root);
};
#endif // MAINWINDOW_H
