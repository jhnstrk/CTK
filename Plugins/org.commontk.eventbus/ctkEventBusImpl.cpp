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
using namespace mafEventBus;

/*ctkEventBusImpl* ctkEventBusImpl::instance()
{
  static ctkEventBusImpl inst;
  return &inst;
}*/

ctkEventBusImpl::ctkEventBusImpl()
{
    m_MafEventBusManager = mafEventBusManager::instance();
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
    m_MafEventBusManager->addEventProperty(*mesbEvent);
}

QString ctkEventBusImpl::subscribeSlot(const QObject* subscriber, const char* member, const QString& topic, const ctkDictionary& properties)
{
    mafEvent *mesbEvent = new mafEvent(topic, mafEventTypeLocal, mafSignatureTypeCallback, const_cast<QObject *>(subscriber), member);
    m_MafEventBusManager->addEventProperty(*mesbEvent);

	// to be changed!!!!!!
	return QString();
  // TODO check for duplicates

  /*ctkEventHandlerWrapper* wrapper = new ctkEventHandlerWrapper(subscriber, member, properties);
  if (wrapper->init())
  {
    bucket(wrapper);
  }

  // TODO return id
  return QString();*/
}

void ctkEventBusImpl::updateProperties(const QString& subscriptionId, const ctkDictionary& properties)
{
  Q_UNUSED(subscriptionId)
  Q_UNUSED(properties)
}

void ctkEventBusImpl::dispatchEvent(const ctkEvent& event, bool isAsync)
{
  Q_UNUSED(isAsync)



  /*QString topic = event.topic();

  QSet<ctkEventHandlerWrapper*> eventHandlers = this->handlers(topic);
  if (eventHandlers.empty()) return;

  QSetIterator<ctkEventHandlerWrapper*> iter(eventHandlers);
  while (iter.hasNext())
  {
    iter.next()->handleEvent(event);
  }*/

  QString topic = event.getTopic(); //may contains widlcards

  mafEvent *mebEvent = new mafEvent();
  mebEvent->setEventTopic(topic);
  mebEvent->setEventType(mafEventTypeLocal);
  //mebEvent->setEventFilter(NULL);
  //need to think about the arguments inside the event


  typedef QList<QGenericArgument> ctkEventArgumentList;

  ctkEventArgumentList list;
  mafList<mafVariant> le(event.getProperty("localEvent").toList());
  mafList<mafVariant> ld(event.getProperty("localData").toList());

  list.append(Q_ARG(mafList<mafVariant>,le));
  list.append(Q_ARG(mafList<mafVariant>,ld));

  m_MafEventBusManager->notifyEvent(topic, mafEventTypeRemote, &list);
  m_MafEventBusManager->notifyEvent(*mebEvent);

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
        return m_MafEventBusManager->createServer(communication_protocol,listen_port);
}

void ctkEventBusImpl::startListen() {
	m_MafEventBusManager->startListen();
}

bool ctkEventBusImpl::createClient(const QString &communication_protocol, const QString &server_host, unsigned int port) {
        return m_MafEventBusManager->createClient(communication_protocol,server_host,port);
}
