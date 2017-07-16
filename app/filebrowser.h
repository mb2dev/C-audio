#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>

class FileBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit FileBrowser(QWidget *parent = 0);

signals:
    void songToLoad(const int &index, const QString filePath);

public slots:
    void handleClick(const QModelIndex &index);
    void customMenuRequested(QPoint pos);
    void loadIntoA();
    void loadIntoB();

protected:
    QTreeView *m_tree;
    QFileSystemModel *model;
    QMenu *m_menu;
    QAction *loadA, *loadB;
    QPoint lastPos;
//    QString *m_songA, *m_songB;

private:
    void createUi();
    void connectUi();
};

#endif // FILEBROWSER_H
