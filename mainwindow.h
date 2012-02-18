/*
    biblref
    Creation of bibliographic references.

    File: mainwindow.h

    Copyright (C) 2012 Artem Petrov <pa2311@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "refbookdialog.h"
#include "refarticledialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_action_file_open_activated();
    void on_action_file_save_activated();
    void on_action_file_print_activated();
    void on_action_file_quit_activated();

    void on_action_ref_book_activated();
    void on_action_ref_article_activated();

    void on_action_help_about_activated();

private:

    Ui::MainWindow *ui;

    QSharedPointer<RefBookDialog> refbookdialog;
    QSharedPointer<RefArticleDialog> refarticledialog;

};

#endif // MAINWINDOW_H
