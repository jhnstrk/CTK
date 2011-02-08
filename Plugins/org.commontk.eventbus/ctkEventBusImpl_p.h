/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#ifndef CTKEVENTBUSIMPL_H
#define CTKEVENTBUSIMPL_H

#include <service/event/ctkEventAdmin.h>

#include "mafEventBus/mafEventBusManager.h"

#include <QList>
#include <QHash>
#include <QSet>

//class forward
class ctkEventHandlerWrapper;


class ctkEventBusImpl : public QObject,
                     public ctkEventAdmin
{
  Q_OBJECT
  Q_INTERFACES(ctkEventAdmin)

public:

  //static ctkEventBusImpl* instance();
          ctkEventBusImpl();

  void postEvent(const ctkEvent& event);
  void sendEvent(const ctkEvent& event);

  void publishSignal(const QObject* publisher, const char* signal, const QString& topic, Qt::ConnectionType type = Qt::QueuedConnection);

  void publishSignal(const QObject* publisher, const char* signal, Qt::ConnectionType type = Qt::QueuedConnection);

  QString subscribeSlot(const QObject* subscriber, const char* member, const QString& topic,const ctkDictionary& properties);

  virtual void unsubscribeSlot(const QString& topic);

  virtual bool updateProperties(const QString& topic, const ctkDictionary& properties);
  
  /// Create the server for remote communication according to the given protocol and listen port.
  virtual bool createServer(const QString &communication_protocol, unsigned int listen_port);

    /// Allow to start server listening.
  virtual void startListen();

    /// Create the client for remote communication according to the given protocol, server host and port.
  virtual bool createClient(const QString &communication_protocol, const QString &server_host, unsigned int port);

protected:

  typedef QList<ctkEventHandlerWrapper*> HandlerList;

  HandlerList globalWildcard;

  QHash<QString, HandlerList> topicName;

  void dispatchEvent(const ctkEvent& event, bool isAsync);

  void bucket(ctkEventHandlerWrapper* wrapper);

  QSet<ctkEventHandlerWrapper*> handlers(const QString& topic);

private:


  ctkEventBus::ctkEventBusManager *m_EventBusManager;
};

#endif // CTKEVENTBUSIMPL_H
