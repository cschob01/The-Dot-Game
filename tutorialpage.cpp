#include "tutorialpage.h"
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdexcept>



TutorialPage::TutorialPage(QWidget *parent)
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

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 10, QFont::Bold));
    layout->addWidget(label);

    //How to Play
    label = new QLabel("How to Play", this);
    label->setFont(QFont("Arial", 20, QFont::Bold));
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 20, QFont::Bold));
    layout->addWidget(label);

    //Movement
    label = new QLabel("Movement:", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("w: Move forward", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("a: Move left", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("d: Move right", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("s: Move backward", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 20, QFont::Bold));
    layout->addWidget(label);

    //Looking
    label = new QLabel("Looking Around:", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Up-arrow: Look up", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Left-arrow: Look left", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Right-arrow: Look right", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("Down-arrow: Look down", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 20, QFont::Bold));
    layout->addWidget(label);

    //Map
    label = new QLabel("m: Look at your map (you cannot move while doing this)", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);
    label = new QLabel("esc: Leave the current level", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);

    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 20, QFont::Bold));
    layout->addWidget(label);

    //Suggestion
    label = new QLabel("Feel free to mess with settings to improve your experience!", this);
    layout->addWidget(label);
    label->setAlignment(Qt::AlignCenter);


    //Space
    label = new QLabel("", this);
    label->setFont(QFont("Arial", 10, QFont::Bold));
    layout->addWidget(label);
    
    layout_sa->addWidget(to_TittlePage);
    connect(to_TittlePage, &QPushButton::clicked, this, [this]() {
        emit changePage(0);
    });

}

TutorialPage::~TutorialPage()
{
}
