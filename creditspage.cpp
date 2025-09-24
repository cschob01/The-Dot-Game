#include "creditspage.h"
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdexcept>



CreditsPage::CreditsPage(QWidget *parent)
    : QWidget(parent)
    , to_TittlePage(new QPushButton("Back", this))
{

    QVBoxLayout *layout_sa = new QVBoxLayout(this);
    QVBoxLayout *layout = new QVBoxLayout();

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("QScrollArea {"
        "border: 2px solid white;"
        "border-radius: 5px;"
        "padding: 0px;"
        "}");

    layout_sa->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setLayout(layout);

    QLabel *label;

    //Crediting myself
    label = new QLabel("The Dot Game", this);
    label->setFont(QFont("Arial", 20, QFont::Bold));
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Created by: Carlos Schober", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 40, QFont::Bold));
    layout->addWidget(label);

    //Crediting music
    label = new QLabel("Tunes Used:", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Stage 1: \"Me Gustas Tú\" and \"Megalovania\"", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Stage 2: \"Fairly Odd Parents Theme\" and \"Friend Like You\"", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Stage 3: \"Rock Lobster\" and \"Sixteen Tons\"", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Stage 4: \"Istanbul\" and \"Wanna Be Like You\"", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Stage 5: \"Hit the Road, Jack\" and \"Kool Beans\"", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Stage 6: \"Song for Denise\" and \"Wellerman\"", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 40, QFont::Bold));
    layout->addWidget(label);

    //Crediting Inspiration
    label = new QLabel("A Special Thanks to:", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Pablo Schober - Primary playtester", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("PROXIMATE - For game inspiration", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 40, QFont::Bold));
    layout->addWidget(label);
    
    layout_sa->addWidget(to_TittlePage);
    connect(to_TittlePage, &QPushButton::clicked, this, [this]() {
        emit changePage(0);
    });

}

CreditsPage::~CreditsPage()
{
}
