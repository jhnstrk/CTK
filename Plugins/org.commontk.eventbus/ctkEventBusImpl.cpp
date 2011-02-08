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

#include "ctkEventBusImpl_p.h"

#include <QSetIterator>

#include "ctkEventHandlerWrapper_p.h"


#define ctkEventArgument(type,data) QArgument<type >(#type, data)

//using namespace mafCore;
using namespace ctkEventBus;

/*ctkEventBusImpl* ctkEventBusImpl::instance()
{
  static ctkEventBusImpl inst;
  return &inst;
}*/

ctkEventBusImpl::ctkEventBusImpl()
{
    m_EventBusManager = ctkEventBusManager::instance();
}

void ctkEventBusImpl::postEvent(const ctkEvent& event)
{
  dispatchEvent(event, true);
}

void ctkEventBusImpl::sendEvent(const ctkEvent& event)
{
  dispatchEvent(event, false);
}

void ctkEventBusImpl::publishSignal(const QObject* publisher, const char* signal, const QString& topic,
                                    Qt::ConnectionType type)
{
    mafEvent *mesbEvent = new mafEvent(topic, mafEventTypeLocal, mafSignatureTypeSignal, const_cast<QObject *>(publisher), signal);
    m_EventBusManager->addEventProperty(*mesbEvent);
}

void ctkEventBusImpl::publishSignal(const QObject* publisher, const char* signal, Qt::ConnectionType type)
{
    qDebug() << "Not implemented in this class";
}

QString ctkEventBusImpl::subscribeSlot(const QObject* subscriber, const char* member, const QString& topic, const ctkDictionary& properties)
{
    mafEvent *mesbEvent = new mafEvent(topic, mafEventTypeLocal, mafSignatureTypeCallback, const_cast<QObject *>(subscriber), member);
    m_EventBusManager->addEventProperty(*mesbEvent);

    return QString();

  /*ctkEventHandlerWrapper* wrapper = new ctkEventHandlerWrapper(subscriber, member, properties);
  if (wrapper->init())
  {
    bucket(wrapper);
  }

  // TODO return id
  return QString();*/
}

void ctkEventBusImpl::unsubscribeSlot(const QString& topic) {
      // @@@@to be implemented
}

bool ctkEventBusImpl::updateProperties(const QString& topic, const ctkDictionary& properties)
{
  Q_UNUSED(topic)
  Q_UNUSED(properties)
  // @@@@to be implemented
}

void ctkEventBusImpl::dispatchEvent(const ctkEvent& event, bool isAsync)
{
  Q_UNUSED(isAsync)

  QString topic = event.getTopic(); //may contains widlcards

  mafEvent *mebEvent = new mafEvent();
  mebEvent->setEventTopic(topic);
  mebEvent->setEventType(mafEventTypeLocal);
  //mebEvent->setEventFilter(NULL);
  //need to think about the arguments inside the event

  typedef QList<QGenericArgument> ctkEventArgumentList;

  ctkEventArgumentList list;
  list.append(Q_ARG(QVariantList,event.getProperty("localEvent").toList()));
  list.append(Q_ARG(QVariantList,event.getProperty("localData").toList()));

  m_EventBusManager->notifyEvent(topic, mafEventTypeRemote, &list);
  m_EventBusManager->notifyEvent(*mebEvent);
}

void ctkEventBusImpl::bucket(ctkEventHandlerWrapper* wrapper)
{
  // TODO bucket logic
  globalWildcard.push_back(wrapper);
}

QSet<ctkEventHandlerWrapper*> ctkEventBusImpl::handlers(const QString& topic)
{
  Q_UNUSED(topic)

  // TODO
  return globalWildcard.toSet();
}

bool ctkEventBusImpl::createServer(const QString &communication_protocol, unsigned int listen_port) {
        return m_EventBusManager->createServer(communication_protocol,listen_port);
}

void ctkEventBusImpl::startListen() {
        m_EventBusManager->startListen();
}

bool ctkEventBusImpl::createClient(const QString &communication_protocol, const QString &server_host, unsigned int port) {
        return m_EventBusManager->createClient(communication_protocol,server_host,port);
}
