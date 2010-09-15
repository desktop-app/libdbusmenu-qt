/* This file is part of the KDE libraries
   Copyright 2010 Canonical
   Author: Aurelien Gateau <aurelien.gateau@canonical.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License (LGPL) as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later
   version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef DBUSMENUEXPORTERDBUS_P_H
#define DBUSMENUEXPORTERDBUS_P_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusVariant>

// Local
#include <dbusmenuitem_p.h>

class DBusMenuExporter;

/**
 * Internal class implementing the DBus side of DBusMenuExporter
 * This avoid exposing the implementation of the DBusMenu spec to the outside
 * world.
 */
class DBusMenuExporterDBus : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ayatana.dbusmenu")
public:
    DBusMenuExporterDBus(DBusMenuExporter *m_exporter);

    Q_PROPERTY(bool IsRightToLeft READ IsRightToLeft)

    bool IsRightToLeft() const;

public Q_SLOTS:
    DBusMenuItemList GetChildren(int parentId, const QStringList &propertyNames);
    Q_NOREPLY void Event(int id, const QString &eventId, const QDBusVariant &data, uint timestamp);
    QDBusVariant GetProperty(int id, const QString &property);
    QVariantMap GetProperties(int id, const QStringList &names);
    uint GetLayout(int parentId, QString &layout);
    DBusMenuItemList GetGroupProperties(const QList<int> &ids, const QStringList &propertyNames);
    bool AboutToShow(int id);

Q_SIGNALS:
    void ItemUpdated(int);
    void ItemPropertyUpdated(int, QString, QVariant);
    void LayoutUpdated(uint revision, int parentId);
    void ItemActivationRequested(int id, uint timeStamp);

private:
    DBusMenuExporter *m_exporter;

    friend class DBusMenuExporter;
    friend class DBusMenuExporterPrivate;
};

#endif /* DBUSMENUEXPORTERDBUS_P_H */
