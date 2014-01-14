/*
    biblref
    Creation of bibliographic references.

    File: refsitedialog.cpp

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

#include "refsitedialog.h"
#include "ui_refsitedialog.h"

#include <QPlainTextEdit>
#include <QTextCursor>
#include <QString>
#include <QStringList>
#include <QMessageBox>

RefSiteDialog::RefSiteDialog(QPlainTextEdit *pte, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefSiteDialog) {

    ui->setupUi(this);
    plainTextEdit = pte;
}

RefSiteDialog::~RefSiteDialog() {
    delete ui;
}

void RefSiteDialog::on_pushButton_add_clicked() {

    if ( ui->lineEdit_pubtitle->text().isEmpty() ||
         ui->lineEdit_sitetitle->text().isEmpty() ||
         ui->lineEdit_url->text().isEmpty() ) {

        QMessageBox::warning(
                    this, "biblref",
                    "Для формирования ссылки типа \"Сайт\" необходимы следующие данные: "
                    "название публикации, название сайта, URL.\n\n"
                    "Так как вы выполнили не все требования, ссылка будет неполноценной."
                    );
    }

    QStringList accessdate = ui->dateEdit->text().split(".");

    if ( accessdate[2].toInt() < ui->spinBox_year->value() ) {

        QMessageBox::critical(this, "biblref",
                              "Ссылка не сформирована.\n"
                              "Вы не могли получить доступ к информации "
                              "раньше, чем она была опубликована. "
                              "Проверьте год и дату доступа.");
        return;
    }

    //

    QString bibref("");

    if ( !ui->lineEdit_authors->text().isEmpty() ) {

        QStringList authors = ui->lineEdit_authors->text().split(";", QString::SkipEmptyParts);

        if ( !authors.isEmpty() ) {

            for ( ptrdiff_t i=0; i<authors.count(); i++ ) {
                authors[i] = authors[i].trimmed();
            }

            if ( authors.count() < 4 ) {

                QStringList firstAuthName = authors[0].split(" ");
                bibref += firstAuthName[firstAuthName.count()-1] + ", ";

                for ( ptrdiff_t i=0; i<firstAuthName.count()-1; i++ ) {
                    bibref += firstAuthName[i] + " ";
                }
            }
        }

        bibref += ui->lineEdit_pubtitle->text() + " / ";

        if ( !authors.isEmpty() ) {

            for ( ptrdiff_t i=0; i<authors.count(); i++ ) {
                bibref += authors[i] + ", ";
            }
        }

        bibref.chop(2);
    }
    else {
        bibref += ui->lineEdit_pubtitle->text();
    }

    bibref += " // "
            + ui->lineEdit_sitetitle->text()
            + ". "
            + QString::number(ui->spinBox_year->value())
            + ". ";

    if ( !ui->lineEdit_sysspec->text().isEmpty() ) {
        bibref += "Систем. требования: "
                + ui->lineEdit_sysspec->text()
                + ". ";
    }

    bibref += "URL: "
            + ui->lineEdit_url->text()
            + " (дата обращения: "
            + ui->dateEdit->text()
            + ").";

    //

    plainTextEdit->moveCursor(QTextCursor::End);
    plainTextEdit->appendPlainText(bibref);
}
