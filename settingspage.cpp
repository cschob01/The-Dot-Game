#include "settingspage.h"
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <stdexcept>



SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addSpacerItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

    QHBoxLayout *layout10 = new QHBoxLayout();
    QLabel *blank10 = new QLabel("");
    layout10->addWidget(blank10);
    QPushButton *reset = new QPushButton("Reset to Default Settings");
    layout10->addWidget(reset);
    QLabel *blank11 = new QLabel("");
    layout10->addWidget(blank11);
    connect(reset, &QPushButton::clicked, this, [this]() {
        settings = Settings();
        updateLabels();
    });
    layout->addLayout(layout10);

    layout->addSpacerItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //POVH and POV
    QHBoxLayout *layout1 = new QHBoxLayout();
    QLabel *pov_h_l = new QLabel("Horizontal POV:");
    QPushButton *pov_h_d = new QPushButton("-");
    pov_h_c = new QLabel(QString::number(settings.pov_h));
    QPushButton *pov_h_i = new QPushButton("+");
    layout1->addWidget(pov_h_l);
    pov_h_l->setAlignment(Qt::AlignCenter);
    layout1->addWidget(pov_h_d);
    pov_h_d->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout1->addWidget(pov_h_c);
    pov_h_c->setAlignment(Qt::AlignCenter);
    layout1->addWidget(pov_h_i);
    pov_h_i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout1->setStretchFactor(pov_h_l, 2);

    QLabel *pov_v_l = new QLabel("Vertical POV:");
    QPushButton *pov_v_d = new QPushButton("-");
    pov_v_c = new QLabel(QString::number(settings.pov_v));
    QPushButton *pov_v_i = new QPushButton("+");
    layout1->addWidget(pov_v_l);
    pov_v_l->setAlignment(Qt::AlignCenter);
    layout1->addWidget(pov_v_d);
    pov_v_d->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout1->addWidget(pov_v_c);
    pov_v_c->setAlignment(Qt::AlignCenter);
    layout1->addWidget(pov_v_i);
    pov_v_i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout1->setStretchFactor(pov_v_l, 2);

    QLabel *blank1 = new QLabel("");
    layout1->addWidget(blank1);
    layout1->setStretchFactor(blank1, 1);

    layout->addLayout(layout1);
    connect(pov_h_d, &QPushButton::clicked, this, [this]() {
        if(settings.pov_h > 10){
            settings.pov_h--;
            updateLabels();
        }
    });
    connect(pov_h_i, &QPushButton::clicked, this, [this]() {
        if(settings.pov_h < 120){
            settings.pov_h++;
            updateLabels();
        }
    });
    connect(pov_v_d, &QPushButton::clicked, this, [this]() {
        if(settings.pov_v > 10){
            settings.pov_v--;
            updateLabels();
        }
    });
    connect(pov_v_i, &QPushButton::clicked, this, [this]() {
        if(settings.pov_v < 120){
            settings.pov_v++;
            updateLabels();
        }
    });

    layout->addSpacerItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //Columns and rows
    QHBoxLayout *layout2 = new QHBoxLayout();
    QLabel *col_l = new QLabel("Dot Columns:");
    QPushButton *col_d = new QPushButton("-");
    col_c = new QLabel(QString::number(settings.columns));
    QPushButton *col_i = new QPushButton("+");
    layout2->addWidget(col_l);
    col_l->setAlignment(Qt::AlignCenter);
    layout2->addWidget(col_d);
    col_d->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout2->addWidget(col_c);
    col_c->setAlignment(Qt::AlignCenter);
    layout2->addWidget(col_i);
    col_i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout2->setStretchFactor(col_l, 2);

    QLabel *row_l = new QLabel("Dot Rows:");
    QPushButton *row_d = new QPushButton("-");
    row_c = new QLabel(QString::number(settings.rows));
    QPushButton *row_i = new QPushButton("+");
    layout2->addWidget(row_l);
    row_l->setAlignment(Qt::AlignCenter);
    layout2->addWidget(row_d);
    row_d->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout2->addWidget(row_c);
    row_c->setAlignment(Qt::AlignCenter);
    layout2->addWidget(row_i);
    row_i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout2->setStretchFactor(row_l, 2);

    QLabel *blank2 = new QLabel("");
    layout2->addWidget(blank2);
    layout2->setStretchFactor(blank2, 1);

    layout->addLayout(layout2);
    connect(col_d, &QPushButton::clicked, this, [this]() {
        if(settings.columns > 50){
            settings.columns = settings.columns - 10;
            updateLabels();
        }
    });
    connect(col_i, &QPushButton::clicked, this, [this]() {
        settings.columns = settings.columns + 10;
        updateLabels();
    });
    connect(row_d, &QPushButton::clicked, this, [this]() {
        if(settings.rows > 50){
            settings.rows = settings.rows - 10;
            updateLabels();
        }
    });
    connect(row_i, &QPushButton::clicked, this, [this]() {
        settings.rows = settings.rows + 10;
        updateLabels();
    });

    layout->addSpacerItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //SensitivityH and SensitivityV
    QHBoxLayout *layout3 = new QHBoxLayout();
    QLabel *sensitivityH_l = new QLabel("Horizontal Sensitivity:");
    QPushButton *sensitivityH_d = new QPushButton("-");
    sensitivityH_c = new QLabel(QString::number(settings.sensitivityH));
    QPushButton *sensitivityH_i = new QPushButton("+");
    layout3->addWidget(sensitivityH_l);
    sensitivityH_l->setAlignment(Qt::AlignCenter);
    layout3->addWidget(sensitivityH_d);
    sensitivityH_d->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout3->addWidget(sensitivityH_c);
    sensitivityH_c->setAlignment(Qt::AlignCenter);
    layout3->addWidget(sensitivityH_i);
    sensitivityH_i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout3->setStretchFactor(sensitivityH_l, 2);

    QLabel *sensitivityV_l = new QLabel("Vertical Sensitivity:");
    QPushButton *sensitivityV_d = new QPushButton("-");
    sensitivityV_c = new QLabel(QString::number(settings.sensitivityV));
    QPushButton *sensitivityV_i = new QPushButton("+");
    layout3->addWidget(sensitivityV_l);
    sensitivityV_l->setAlignment(Qt::AlignCenter);
    layout3->addWidget(sensitivityV_d);
    sensitivityV_d->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout3->addWidget(sensitivityV_c);
    sensitivityV_c->setAlignment(Qt::AlignCenter);
    layout3->addWidget(sensitivityV_i);
    sensitivityV_i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout3->setStretchFactor(sensitivityV_l, 2);

    QLabel *blank3 = new QLabel("");
    layout3->addWidget(blank3);
    layout3->setStretchFactor(blank3, 1);

    layout->addLayout(layout3);
    connect(sensitivityH_d, &QPushButton::clicked, this, [this]() {
        if(settings.sensitivityH > 1){
            settings.sensitivityH--;
            updateLabels();
        }
    });
    connect(sensitivityH_i, &QPushButton::clicked, this, [this]() {
        settings.sensitivityH++;
        updateLabels();
    });
    connect(sensitivityV_d, &QPushButton::clicked, this, [this]() {
        if(settings.sensitivityV > 1){
            settings.sensitivityV--;
            updateLabels();
        }
    });
    connect(sensitivityV_i, &QPushButton::clicked, this, [this]() {
        settings.sensitivityV++;
        updateLabels();
    });

    layout->addSpacerItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

    //Render and roofs
    QHBoxLayout *layout4 = new QHBoxLayout();
    QLabel *render_l = new QLabel("Render Distance:");
    QPushButton *render_d = new QPushButton("-");
    render_c = new QLabel(QString::number(settings.render));
    QPushButton *render_i = new QPushButton("+");
    layout4->addWidget(render_l);
    render_l->setAlignment(Qt::AlignCenter);
    layout4->addWidget(render_d);
    render_d->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout4->addWidget(render_c);
    render_c->setAlignment(Qt::AlignCenter);
    layout4->addWidget(render_i);
    render_i->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout4->setStretchFactor(render_l, 2);

    QLabel *roofs_l = new QLabel("Roof:");
    roofs_c = new QPushButton("Enabled");
    layout4->addWidget(roofs_l);
    roofs_l->setAlignment(Qt::AlignCenter);
    layout4->addWidget(roofs_c);
    roofs_c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout4->setStretchFactor(roofs_l, 2);

    QLabel *blank4 = new QLabel("");
    layout4->addWidget(blank4);
    layout4->setStretchFactor(blank4, 1);

    layout->addLayout(layout4);
    connect(render_d, &QPushButton::clicked, this, [this]() {
        if(settings.render > 10){
            settings.render -= 5;
            updateLabels();
        }
    });
    connect(render_i, &QPushButton::clicked, this, [this]() {
        settings.render += 5;
        updateLabels();
    });
    connect(roofs_c, &QPushButton::clicked, this, [this]() {
        if(settings.roofs){
            settings.roofs = false;
            updateLabels();
        }
        else{
            settings.roofs = true;
            updateLabels();
        }
    });

    layout->addSpacerItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

    to_TittlePage = new QPushButton("Back", this);
    layout->addWidget(to_TittlePage);
    connect(to_TittlePage, &QPushButton::clicked, this, [this]() {
        emit changePage(0);
    });

    layout->addSpacerItem(new QSpacerItem(40, 15, QSizePolicy::Expanding, QSizePolicy::Expanding));

}

void SettingsPage::updateLabels(){
    pov_h_c->setText(QString::number(settings.pov_h));
    pov_v_c->setText(QString::number(settings.pov_v));
    col_c->setText(QString::number(settings.columns));
    row_c->setText(QString::number(settings.rows));
    render_c->setText(QString::number(settings.render));
    sensitivityH_c->setText(QString::number(settings.sensitivityH));
    sensitivityV_c->setText(QString::number(settings.sensitivityV));
    if(settings.roofs){
        roofs_c->setText("Enabled");
    }
    else{
        roofs_c->setText("Disabled");
    }
}

SettingsPage::~SettingsPage()
{
}

Settings SettingsPage::getSettings(){
    return settings;
}

void SettingsPage::setup(Settings settings){
    this->settings = settings;
    updateLabels();
}
