/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGraphicsView *graphicsView;
    QLabel *author;
    QPushButton *pushButton;
    QLabel *logo;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(900, 1000);
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(false);
        graphicsView->setGeometry(QRect(0, 60, 900, 900));
        graphicsView->setFocusPolicy(Qt::NoFocus);
        graphicsView->setToolTipDuration(0);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setLineWidth(0);
        author = new QLabel(Widget);
        author->setObjectName(QString::fromUtf8("author"));
        author->setGeometry(QRect(0, 960, 900, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI Light"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        author->setFont(font);
        author->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 100, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Segoe UI"));
        font1.setBold(true);
        font1.setWeight(75);
        pushButton->setFont(font1);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        logo = new QLabel(Widget);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(700, 0, 200, 60));
        QFont font2;
        font2.setFamily(QString::fromUtf8("GOST type A"));
        font2.setPointSize(30);
        font2.setBold(true);
        font2.setWeight(75);
        logo->setFont(font2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        author->setText(QApplication::translate("Widget", "Created by Mike Kosarev for MAI", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\320\235\320\220\320\247\320\220\320\242\320\254 \320\230\320\223\320\240\320\243", nullptr));
        logo->setText(QApplication::translate("Widget", "TanksBattle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
