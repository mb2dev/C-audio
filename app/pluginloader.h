#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

// On n'oublie pas les inclusions.

#include <QList>
#include <QPluginLoader>
#include <QObject>
#include <QString>
#include <QDir>
#include <QObject>

// @see https://openclassrooms.com/courses/qt-creation-de-plugins

namespace PluginLoader {

    // C'est une méthode qui demande un argument template pour éviter de créer un chargeur par type de plugin.
    template<typename T> T* pluginByName(const QString& fileName) {
        QPluginLoader loader(fileName); // On charge le plugin.
        QObject *plugin = loader.instance(); // On prend l'instance.
        return qobject_cast<T*>(plugin); // Et on retourne le plugin casté.
    }

    // Toujours une méthode avec un argument template pour éviter qu'il y en ait 50.
    template<typename T> QList<T*> pluginByDir(const QString& dir) {
        QList<T*> ls; // On crée la liste où seront mis tous les plugins valides.
        QDir plugDir = QDir(dir);
        foreach(QString file, plugDir.entryList(QDir::Files)) { // On prend la liste des fichiers.
            if(T* plugin = PluginLoader::pluginByName<T>(plugDir.absoluteFilePath(file))) // On vérifie si le plugin existe.
                ls.push_back(plugin); // On l'ajoute à la liste si oui.
        }

        return ls;
    }

}

#endif // PLUGINLOADER_H
