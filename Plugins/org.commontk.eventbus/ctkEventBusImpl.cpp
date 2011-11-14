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
#include "ctkBusEvent.h"
#include "ctkEventDefinitions.h"


#define ctkEventArgument(type,data) QArgument<type >(#type, data)

ctkEventBusImpl::ctkEventBusImpl()
{
    m_EventBusManager = ctkEventBus::ctkEventBusManager::instance();
}

void ctkEventBusImpl::postEvent(const ::ctkEvent& event)
{
  dispatchEvent(event, true);
}

void ctkEventBusImpl::sendEvent(const ::ctkEvent& event)
{
  dispatchEvent(event, false);
}

void ctkEventBusImpl::publishSignal(const QObject* publisher, const char* signal, const QString& topic,
                                    Qt::ConnectionType type)
{
    ctkBusEvent *mesbEvent = new ctkBusEvent(topic, ctkEventBus::ctkEventTypeLocal, ctkEventBus::ctkSignatureTypeSignal, const_cast<QObject *>(publisher), signal);
    m_EventBusManager->addEventProperty(*mesbEvent);
}

void ctkEventBusImpl::publishSignal(const QObject* publisher, const char* signal, Qt::ConnectionType type)
{
    qDebug() << "Not implemented in this class";
}

qlonglong ctkEventBusImpl::subscribeSlot(const QObject* subscriber, const char* member, const ctkDictionary& properties)
{
    ctkDictionary toSend(properties);
    QString topic = properties.value(TOPIC).toString();
    toSend.insert(TOPIC, topic);
    toSend.insert(TYPE, ctkEventBus::ctkEventTypeLocal);
    toSend.insert(SIGTYPE, ctkEventBus::ctkSignatureTypeCallback);
    QVariant var;
    var.setValue(const_cast<QObject *>(subscriber));
    toSend.insert(OBJECT, var);
    toSend.insert(SIGNATURE,member);
    ctkBusEvent *mesbEvent = new ctkBusEvent(topic, toSend);
    m_EventBusManager->addEventProperty(*mesbEvent);

    return topic.toLongLong();

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
  return false;
}

void ctkEventBusImpl::dispatchEvent(const ctkEvent& event, bool isAsync)
{
  Q_UNUSED(isAsync)
  ctkBusEvent *mebEvent = new ctkBusEvent("",ctkEventBus::ctkEventTypeRemote,ctkEventBus::ctkSignatureTypeSignal, this, "no");
  //cycle for all other elements
  QStringList keyList = event.getPropertyNames();
  QStringList::const_iterator constIterator;
  for (constIterator = keyList.constBegin(); constIterator != keyList.constEnd(); ++constIterator) {
      QVariant value = event.getProperty((*constIterator));
      //qDebug() << (*constIterator) << " " << value.toString();
      (*mebEvent)[(*constIterator)] = event.getProperty((*constIterator));
  }

  typedef QList<QGenericArgument> ctkEventArgumentList;

  ctkEventArgumentList list;
  list.append(Q_ARG(QVariantList,event.getProperty("localEvent").toList()));
  list.append(Q_ARG(QVariantList,event.getProperty("localData").toList()));

  m_EventBusManager->notifyEvent(*mebEvent, &list);
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
