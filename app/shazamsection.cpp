#include "shazamsection.h"

ShazamSection::ShazamSection(QWidget *parent)
    : QWidget(parent)
    , m_boutonDialogue(new QPushButton("Choisir un fichier", this))
    , m_progressBar(new QProgressBar(this))
    , m_liste(new QListView(this))
{
    createUi();
    connectUi();
}

void ShazamSection::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
}

void ShazamSection::createUi()
{
    m_boutonDialogue->move(40, 50);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_boutonDialogue);
    layout->addWidget(m_progressBar);
    layout->addWidget(m_liste);

    this->setLayout(layout);
}

void ShazamSection::connectUi()
{
    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(ouvrirDialogue()));
}
