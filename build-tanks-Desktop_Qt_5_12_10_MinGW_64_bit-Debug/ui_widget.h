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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGraphicsView *graphicsView;
    QLabel *author;
    QPushButton *pushButton;
    QLabel *logo;
    QPushButton *restart;
    QLabel *label;
    QSpinBox *spinBox;
    QLabel *label_2;
    QSpinBox *spinBox_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(900, 700);
        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(false);
        graphicsView->setGeometry(QRect(0, 60, 900, 600));
        graphicsView->setFocusPolicy(Qt::NoFocus);
        graphicsView->setToolTipDuration(0);
        graphicsView->setAutoFillBackground(false);
        graphicsView->setLineWidth(0);
        author = new QLabel(Widget);
        author->setObjectName(QString::fromUtf8("author"));
        author->setGeometry(QRect(0, 660, 900, 40));
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
        restart = new QPushButton(Widget);
        restart->setObjectName(QString::fromUtf8("restart"));
        restart->setGeometry(QRect(150, 10, 40, 40));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(240, 0, 170, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Segoe UI Black"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);
        spinBox = new QSpinBox(Widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(420, 5, 50, 20));
        spinBox->setMinimum(1);
        spinBox->setMaximum(3);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 30, 170, 30));
        label_2->setFont(font3);
        spinBox_2 = new QSpinBox(Widget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(420, 35, 50, 20));
        spinBox_2->setMinimum(5);
        spinBox_2->setMaximum(20);
        spinBox_2->setValue(5);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        author->setText(QApplication::translate("Widget", "Created by Mike Kosarev for MAI", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\320\235\320\220\320\247\320\220\320\242\320\254 \320\230\320\223\320\240\320\243", nullptr));
        logo->setText(QApplication::translate("Widget", "TanksBattle", nullptr));
        restart->setText(QString());
        label->setText(QApplication::translate("Widget", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\276\321\202\320\276\320\262", nullptr));
        label_2->setText(QApplication::translate("Widget", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\273\320\276\320\272\320\276\320\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
