#ifndef SHAZAMSECTION_H
#define SHAZAMSECTION_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QListView>


class ShazamSection : public QWidget
{
    Q_OBJECT
public:
    ShazamSection(QWidget *parent = 0);

public slots:
    void ouvrirDialogue();

protected:
    QListView *m_liste;
    QPushButton *m_boutonDialogue;
    QProgressBar *m_progressBar;

private:
    void createUi();
    void connectUi();
};

#endif // SHAZAMSECTION_H
