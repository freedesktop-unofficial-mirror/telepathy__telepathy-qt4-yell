/*
 * This file is part of TelepathyQt4Yell
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

namespace Tpy
{

/* ====== CallStream ====== */
struct TELEPATHY_QT4_YELL_NO_EXPORT CallStream::Private
{
    Private(CallStream *parent, const CallContentPtr &content);

    static void introspectMainProperties(Private *self);

    void processRemoteMembersChanged();

    struct RemoteMembersChangedInfo;

    // Public object
    CallStream *parent;

    QWeakPointer<CallContent> content;

    // Mandatory proxies
    Client::CallStreamInterface *streamInterface;
    Tp::Client::DBus::PropertiesInterface *properties;

    Tp::ReadinessHelper *readinessHelper;

    // Introspection
    uint localSendingState;
    ContactSendingStateMap remoteMembers;
    QHash<uint, Tp::ContactPtr> remoteMembersContacts;
    bool buildingRemoteMembers;
    QQueue<RemoteMembersChangedInfo *> remoteMembersChangedQueue;
    RemoteMembersChangedInfo *currentRemoteMembersChangedInfo;
};

struct TELEPATHY_QT4_YELL_NO_EXPORT CallStream::Private::RemoteMembersChangedInfo
{
    RemoteMembersChangedInfo(const ContactSendingStateMap &updates, const Tp::UIntList &removed)
        : updates(updates),
          removed(removed)
    {
    }

    ContactSendingStateMap updates;
    UIntList removed;
};

/* ====== PendingCallContent ====== */
struct TELEPATHY_QT4_YELL_NO_EXPORT PendingCallContent::Private
{
    Private(PendingCallContent *parent, const CallChannelPtr &channel)
        : parent(parent),
          channel(channel)
    {
    }

    PendingCallContent *parent;
    CallChannelPtr channel;
    CallContentPtr content;
};

/* ====== CallContent ====== */
struct TELEPATHY_QT4_YELL_NO_EXPORT CallContent::Private
{
    Private(CallContent *parent, const CallChannelPtr &channel);

    static void introspectMainProperties(Private *self);
    void checkIntrospectionCompleted();

    CallStreamPtr addStream(const QDBusObjectPath &streamPath);
    CallStreamPtr lookupStream(const QDBusObjectPath &streamPath);

    // Public object
    CallContent *parent;

    QWeakPointer<CallChannel> channel;

    // Mandatory proxies
    Client::CallContentInterface *contentInterface;
    Tp::Client::DBus::PropertiesInterface *properties;

    Tp::ReadinessHelper *readinessHelper;

    // Introspection
    QString name;
    uint type;
    CallStreams streams;
    CallStreams incompleteStreams;
};

/* ====== CallChannel ====== */
struct TELEPATHY_QT4_YELL_NO_EXPORT CallChannel::Private
{
    Private(CallChannel *parent);
    ~Private();

    static void introspectContents(Private *self);
    static void introspectLocalHoldState(Private *self);

    CallContentPtr addContent(const QDBusObjectPath &contentPath);
    CallContentPtr lookupContent(const QDBusObjectPath &contentPath) const;

    // Public object
    CallChannel *parent;

    // Mandatory proxies
    Client::ChannelTypeCallInterface *callInterface;
    Tp::Client::DBus::PropertiesInterface *properties;

    Tp::ReadinessHelper *readinessHelper;

    // Introspection
    bool hardwareStreaming;
    CallContents contents;
    CallContents incompleteContents;

    uint localHoldState;
    uint localHoldStateReason;
};

} // Tp
