#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent)
    : QWidget(parent)
    , model(new QDirModel)
    , m_tree(new QTreeView(this))
{


}

void FileBrowser::createUi()
{
    QHBoxLayout *layout = new QHBoxLayout;

    m_tree->setModel(model);
    layout->addWidget(m_tree);

    this->setLayout(layout);
}

void FileBrowser::connectUi()
{

}
