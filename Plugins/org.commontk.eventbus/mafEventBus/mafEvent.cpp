/*
 *  ctkEvent.cpp
 *  ctkEventBus
 *
 *  Created by Paolo Quadrani on 27/03/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafEvent.h"

using namespace ctkEventBus;

ctkEvent::ctkEvent() {
    m_EventHash = new ctkEventHash();
}

/// Overload object constructor.
ctkEvent::ctkEvent(QString topic, ctkEventType event_type, mafSignatureType signature_type, QObject *objectPointer, QString signature) {
    m_EventHash = new ctkEventHash();
    entries()->insert(TOPIC, topic);
    entries()->insert(TYPE, static_cast<int>(event_type));
    entries()->insert(SIGTYPE, static_cast<int>(signature_type));
    QVariant var;
    var.setValue(objectPointer);
    entries()->insert(OBJECT, var);
    entries()->insert(SIGNATURE, signature);
}

ctkEvent::~ctkEvent() {
    m_EventHash->clear();
    delete m_EventHash;
}

ctkEventHash *ctkEvent::entries() {
    return m_EventHash;
}

ctkEventHash *ctkEvent::entries() const {
    return m_EventHash;
}

QVariant &ctkEvent::operator[](QString key) const{
    return (*m_EventHash)[key];
}

ctkEventType ctkEvent::eventType() const {
    return static_cast<ctkEventType>(entries()->value(TYPE).toInt());
}

QString ctkEvent::eventTopic() const {
    return entries()->value(TOPIC).toString();
}

bool ctkEvent::isEventLocal() const {
    int et = entries()->value(TYPE).toInt();
    return et == ctkEventTypeLocal;
}

void ctkEvent::setEventType(ctkEventType et) {
    entries()->insert(TYPE, static_cast<int>(et));
}

void ctkEvent::setEventTopic(QString topic) {
    entries()->insert(TOPIC, topic);
}

/*QString ctkEvent::eventIdName() const {
    mafId id = eventId();
    return mafIdProvider::instance()->idName(id);
}*/
