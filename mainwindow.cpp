#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <typeinfo>
using namespace std;

set<string> random_dataset(int no_of_randoms);
string random_string(int word_length);
bool valid_input(string input);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw_hash();
    draw_trie();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_random_data_button_clicked() {
    _table.clear();
    _tree.clear();
    set<string> data_set = random_dataset(ui->random_input->text().toInt());
    for (auto it : data_set) {
        _table.insert(it);
        _tree.insert(it);
    }
    draw_hash();
    draw_trie();
}


void MainWindow::on_clear_button_clicked() {
    _table.clear();
    _tree.clear();
    draw_hash();
    draw_trie();
}


void MainWindow::on_insert_button_clicked() {
    if (valid_input(ui->lineEdit->text().toStdString())) {
        _table.insert(ui->lineEdit->text().toStdString());
        _tree.insert(ui->lineEdit->text().toStdString());
    }
    else {
        ui->textEdit_2->setPlainText("Invalid Input");
        ui->trie_out->setPlainText("Invalid Input");
    }
    draw_hash();
    draw_trie();
}


void MainWindow::on_delete_button_clicked() {
    if (valid_input(ui->lineEdit->text().toStdString())) {
        _table.remove(ui->lineEdit->text().toStdString());
        _tree.remove(ui->lineEdit->text().toStdString());
    }
    else {
        ui->textEdit_2->setPlainText("Invalid Input");
        ui->trie_out->setPlainText("Invalid Input");
    }
    draw_trie();
    draw_hash();
}


void MainWindow::on_search_button_clicked() {
    if (valid_input(ui->lineEdit->text().toStdString())) {
        if (_table.search(ui->lineEdit->text().toStdString())) {
            ui->textEdit_2->setPlainText("Found in Hash Table");
        }
        else if (!_table.search(ui->lineEdit->text().toStdString())){
            ui->textEdit_2->setPlainText("Not found in Hash Table");
        }
        if (_tree.find(ui->lineEdit->text().toStdString())) {
            ui->trie_out->setPlainText("Found in Trie");
        }
        else if (!_tree.find(ui->lineEdit->text().toStdString())){
            ui->trie_out->setPlainText("Not found in Trie");
        }
    }
    else {
        ui->trie_out->setPlainText("Invalid Input");
        ui->textEdit_2->setPlainText("Invalid Input");
    }

}

void MainWindow::draw_hash() {
    vector<vector<string>>& data_table = _table.get_table();
    ui->tableWidget->setRowCount(data_table.size());
    for (int i = 0; i < data_table.size(); i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString(QString::number(i))));
        string data_row = "";
        for (int j = 0; j < data_table[i].size(); j++) {
            data_row += (data_table[i][j] + " ");
        }
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString(QString::fromStdString(data_row))));
    }
}

void MainWindow::draw_trie() {
    if (_tree.get_values() == 0) {
        ui->treeWidget->clear();
        QTreeWidgetItem* itm = new QTreeWidgetItem(ui->treeWidget);
        itm->setText(0, "root");
        itm->setText(1, "0");
        ui->treeWidget->addTopLevelItem(itm);
        return;
    }
    ui->treeWidget->clear();
    QTreeWidgetItem* itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0, "root");
    itm->setText(1, "0");
    ui->treeWidget->addTopLevelItem(itm);
    Trie::node* root = _tree.get_root();
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != nullptr) {
            draw_children(itm, (i + 'a'), root->children[i]);
        }
    }
}

void MainWindow::draw_children(QTreeWidgetItem* parent, char name, Trie::node* root) {
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(0, QString(QChar(name)));
    if (root->is_leaf) {
        itm->setText(1, "1");
    }
    else {
        itm->setText(1, "0");
    }

    parent->addChild(itm);
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != nullptr) {
            draw_children(itm, (i + 'a'), root->children[i]);
        }
    }
}

set<string> random_dataset(int no_of_randoms) {
    set<string> random_set;
    for (int i = 0; i < no_of_randoms; i++) {
        random_set.insert(random_string((rand() % 3) + 4));
    }
    return random_set;
}

string random_string(int word_length) {
    string random_str;
    for (int i = 0; i < word_length; i++) {
        char random_letter = rand() % ('z' - 'a' + 1) + 'a';
        random_str += (random_letter);
    }
    return random_str;
}

bool valid_input(string input) {
    for (char i : input) {
        if (isupper(i) || i == *" " || isdigit(i)) {
            return false;
        }
    }
    return true;
}
