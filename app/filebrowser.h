#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QDirModel>
#include <QTreeView>
#include <QHBoxLayout>

class FileBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit FileBrowser(QWidget *parent = 0);

signals:

public slots:

protected:
    QTreeView *m_tree;
    QDirModel *model;

private:
    void createUi();
    void connectUi();
};

#endif // FILEBROWSER_H
