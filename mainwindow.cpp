/*
    biblref
    Creation of bibliographic references.

    File: mainwindow.cpp

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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "constants.h"

#include <QSharedPointer>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    setWindowTitle("biblref " + VERSION);

    refbookdialog = QSharedPointer<RefBookDialog>
            (new RefBookDialog(ui->plainTextEdit_references));
    refarticledialog = QSharedPointer<RefArticleDialog>
            (new RefArticleDialog(ui->plainTextEdit_references));
    refdissertationdialog = QSharedPointer<RefDissertationDialog>
            (new RefDissertationDialog(ui->plainTextEdit_references));
    refdeposmanuscriptdialog = QSharedPointer<RefDeposManuscriptDialog>
            (new RefDeposManuscriptDialog(ui->plainTextEdit_references));
    refpatentdialog = QSharedPointer<RefPatentDialog>
            (new RefPatentDialog(ui->plainTextEdit_references));
    refinventsertificatedialog = QSharedPointer<RefInventSertificateDialog>
            (new RefInventSertificateDialog(ui->plainTextEdit_references));
}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::on_action_file_open_activated() {

    QString dir(QDir::currentPath());

    QString filename(QFileDialog::getOpenFileName(
                         this,
                         tr("Открыть файл..."),
                         dir,
                         QString::fromAscii(
                             "Text files (*.txt);;All files (*.*)"
                             ),
                         0,
                         0));

    if ( !filename.isEmpty() ) {

        QFile filedata(filename);

        if ( filedata.open(QIODevice::ReadOnly) ) {

            ui->plainTextEdit_references->
                    setPlainText(filedata.readAll());

            filedata.close();
        }
        else {

            QMessageBox::critical(
                        0,
                        "biblref",
                        "Не могу открыть файл \"" + filename + "\"!",
                        0, 0, 0);
            return;
        }
    }
}

void MainWindow::on_action_file_save_activated() {

    QString dir(QDir::currentPath());

    QString filename(QFileDialog::getSaveFileName(
                         this,
                         "Сохранить в файл...",
                         dir,
                         QString::fromAscii(
                             "Text files (*.txt);;All files (*.*)"
                             ),
                         0,
                         0));

    if ( !filename.isEmpty() ) {

        QFile file(filename);

        if ( !file.open(QIODevice::WriteOnly) ) {

            QMessageBox::critical(
                        0,
                        "biblref",
                        "Не могу открыть файл \"" + filename + "\"!",
                        0, 0, 0);
            return;
        }

        QTextStream fout(&file);
        fout << ui->plainTextEdit_references->toPlainText();

        file.close();
    }
}

void MainWindow::on_action_file_print_activated() {

    QPrinter printer;

    printer.setOrientation(QPrinter::Portrait);
    printer.setPageMargins(20, 20, 10, 10, QPrinter::Millimeter);

    QPrintDialog printDialog(&printer, this);

    if ( printDialog.exec() == QDialog::Accepted ) {

        ui->plainTextEdit_references->print(&printer);
    }
}

void MainWindow::on_action_file_quit_activated() {

    close();
}

void MainWindow::on_action_ref_book_activated() {

    refbookdialog->exec();
}

void MainWindow::on_action_ref_article_activated() {

    refarticledialog->exec();
}

void MainWindow::on_action_ref_dissertation_activated() {

    refdissertationdialog->exec();
}

void MainWindow::on_action_ref_deposmanuscript_activated() {

    refdeposmanuscriptdialog->exec();
}

void MainWindow::on_action_ref_patent_activated() {

    refpatentdialog->exec();
}

void MainWindow::on_action_ref_inventsertificate_activated() {

    refinventsertificatedialog->exec();
}

void MainWindow::on_action_help_about_activated() {

    QString str = "<b>biblref " + VERSION + "</b>\n"
            "<br><br>Создание библиографических ссылок."
            "<br><br>Copyright (C) 2012 Artem Petrov "
            "<a href= \"mailto:pa2311@gmail.com\" >pa2311@gmail.com</a>"
            "<br><br>Сайт программы: "
            "<a href= \"https://github.com/pa23/biblref\">"
            "https://github.com/pa23/biblref</a>"
            "<br>Блог автора: "
            "<a href= \"http://pa2311.blogspot.com\">"
            "http://pa2311.blogspot.com</a>"
            "<br><br>This program is free software: you can redistribute it "
            "and/or modify "
            "it under the terms of the GNU General Public License as published "
            "by "
            "the Free Software Foundation, either version 3 of the License, or "
            "(at your option) any later version. "
            "<br>This program is distributed in the hope that it will be "
            "useful, "
            "but WITHOUT ANY WARRANTY; without even the implied warranty of "
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the "
            "GNU General Public License for more details. "
            "<br>You should have received a copy of the GNU General Public "
            "License "
            "along with this program. If not, see <a href= "
            "\"http://www.gnu.org/licenses/\" >"
            "http://www.gnu.org/licenses/</a>.<br>";

    QMessageBox::about(this, "О программе biblref", str);
}
