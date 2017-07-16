#include "filebrowser.h"
#include <QDebug>
#include <QStandardPaths>
#include <QMenu>
#include <QAction>

FileBrowser::FileBrowser(QWidget *parent)
    : QWidget(parent)
    , model(new QFileSystemModel)
    , m_tree(new QTreeView)
    , m_menu(new QMenu(this))
    , loadA(new QAction("Load into Player A", this))
    , loadB(new QAction("Load into Player B", this))
{

    m_menu->addAction(loadA);
    m_menu->addAction(loadB);

    //model->setFilter( QDir::NoDotAndDotDot | QDir::Files );

    QStringList filters;
    filters << "*.wav";

    model->setNameFilters(filters);
    model->setNameFilterDisables(false);

    QStringList list = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    QString dir(list.at(0));
    qDebug(dir.toLatin1());
    model->setRootPath(dir);
    m_tree->setModel(model);
    m_tree->setRootIndex(model->index(dir));
    m_tree->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tree, SIGNAL(customContextMenuRequested(QPoint)),
    SLOT(customMenuRequested(QPoint)));
//    m_tree->setSelectionModel();
    createUi();
    connectUi();

}

void FileBrowser::loadIntoA(){
    qDebug("LoadIntoA");
    QModelIndex index = m_tree->indexAt(lastPos);
    QString filePath(model->filePath(index));
//    if(filePath.compare(m_songA) != 0){
//        emit songToLoad(filePath);
//    }
    emit songToLoad(0, filePath);
}

void FileBrowser::loadIntoB(){
    QModelIndex index = m_tree->indexAt(lastPos);
    QString filePath(model->filePath(index));
    emit songToLoad(1, filePath);
}

void FileBrowser::customMenuRequested(QPoint pos){
    lastPos = pos;
    QModelIndex index = m_tree->indexAt(pos);

    QString filePath = model->filePath(index);
    QFileInfo check_file(filePath);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        m_menu->popup(m_tree->viewport()->mapToGlobal(pos));
    }
}

void FileBrowser::createUi()
{
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *v_layout = new QVBoxLayout;


    v_layout->addWidget(m_tree);

    layout->addLayout(v_layout);

    this->setLayout(layout);
}

void FileBrowser::connectUi()
{
    qDebug("selectionModel %p", m_tree->selectionModel());
    QObject::connect(m_tree->selectionModel()
                     , SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&))
                     , this
                     , SLOT(handleClick(const QModelIndex&)));
    connect(loadA, SIGNAL(triggered()), this, SLOT(loadIntoA()));
    connect(loadB, SIGNAL(triggered()), this, SLOT(loadIntoB()));
}

void FileBrowser::handleClick(const QModelIndex &index){
    qDebug("index is valid %d", index.isValid());
    QVariant item = model->data(index, Qt::DisplayRole);
    qDebug(item.toString().toLatin1()); //relative path
    qDebug(model->filePath(index).toLatin1()); //absolute path

    QString filePath = model->filePath(index);
    QFileInfo check_file(filePath);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        //TODO
    }
}
