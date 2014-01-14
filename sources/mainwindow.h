/*
    biblref
    Creation of bibliographic references.

    File: mainwindow.h

    Copyright (C) 2012-2014 Artem Petrov <pa2311@gmail.com>

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
#include <QCloseEvent>

#include "refbookdialog.h"
#include "refarticledialog.h"
#include "refsitedialog.h"
#include "refdissertationdialog.h"
#include "refdeposmanuscriptdialog.h"
#include "refthesisdialog.h"
#include "refpatentdialog.h"
#include "refinventsertificatedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
     void closeEvent(QCloseEvent *event);

private slots:
    void on_action_file_open_triggered();
    void on_action_file_save_triggered();
    void on_action_file_print_triggered();
    void on_action_file_quit_triggered();

    void on_action_view_folding_triggered();

    void on_action_ref_book_triggered();
    void on_action_ref_article_triggered();
    void on_action_ref_site_triggered();
    void on_action_ref_dissertation_triggered();
    void on_action_ref_deposmanuscript_triggered();
    void on_action_ref_thesis_triggered();
    void on_action_ref_patent_triggered();
    void on_action_ref_inventsertificate_triggered();

    void on_action_help_about_triggered();

private:
    Ui::MainWindow *ui;

    QSharedPointer<RefBookDialog> refbookdialog;
    QSharedPointer<RefArticleDialog> refarticledialog;
    QSharedPointer<RefSiteDialog> refsitedialog;
    QSharedPointer<RefDissertationDialog> refdissertationdialog;
    QSharedPointer<RefDeposManuscriptDialog> refdeposmanuscriptdialog;
    QSharedPointer<RefThesisDialog> refthesisdialog;
    QSharedPointer<RefPatentDialog> refpatentdialog;
    QSharedPointer<RefInventSertificateDialog> refinventsertificatedialog;

    void saveIfNecessary();

};

#endif // MAINWINDOW_H
