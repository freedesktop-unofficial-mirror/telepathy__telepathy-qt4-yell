/*
 * This file is part of TelepathyQt4
 *
 * Copyright (C) 2010 Collabora Ltd. <http://www.collabora.co.uk/>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _TelepathyQt4_models_conversation_item_h_HEADER_GUARD_
#define _TelepathyQt4_models_conversation_item_h_HEADER_GUARD_

#ifndef IN_TELEPATHY_QT4_HEADER
#error IN_TELEPATHY_QT4_HEADER
#endif

#include <QDateTime>
#include <QString>
#include <TelepathyQt4/Types>

namespace Tp
{

class TELEPATHY_QT4_EXPORT ConversationItem : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ConversationItem)

public:
    enum Type {
        INCOMING_MESSAGE,
        OUTGOING_MESSAGE,
        EVENT
    };

    ConversationItem(const ContactPtr &contact, const QDateTime &time,
            const QString &text, Type type, QObject *parent = 0);
    virtual ~ConversationItem();

    ContactPtr contact() const;
    QDateTime time() const;
    QString text() const;
    Type type() const;

private:
    struct Private;
    friend struct Private;
    Private *mPriv;
};

}

#endif // _TelepathyQt4_models_conversation_item_h_HEADER_GUARD_
