/*
 *  ctkEvent.h
 *  ctkEventBus
 *
 *  Created by Daniele Giunchi on 10/05/10.
 *  Copyright 2009-2010 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef CTKEVENTHEADER_H
#define CTKEVENTHEADER_H

#include "mafEventDefinitions.h"

namespace ctkEventBus {

 /**
Class name: ctkEvent
This class defines the MAF3 Event which inherit from mafDictionary, and contains
constructor for rapid dictionary creation.
@sa mafDictionary
*/
class CTKEVENTBUSSHARED_EXPORT ctkEvent : public QObject {

public:
    /// Object constructor.
    ctkEvent();

    /// Object destructor.
    ~ctkEvent();

    /// Overload object constructor.
    ctkEvent(QString topic, ctkEventType event_type, mafSignatureType signature_type, QObject *objectPointer, QString signature);

    /// Allow to assign the event type: ctkEventTypeLocal or ctkEventTypeRemote.
    void setEventType(ctkEventType et);

    /// Return the type of the event: ctkEventTypeLocal or ctkEventTypeRemote.
    ctkEventType eventType() const;

    /// Check if the event is local or not.
    bool isEventLocal() const;

    /// Allow to set or modify the event ID
    void setEventTopic(QString topic);

    /// Return the Id associated with the event.
    QString eventTopic() const;

    /// Return the name associated to the numeric Id.
    //QString eventIdName() const;

    /// Redefined operator to have access to the entries owned.
    ctkEventHash *entries();

    /// Redefined operator to have access to the entries owned.
    ctkEventHash *entries() const;

    /// Overload operator for rapid access to mafDictionaryEntries
    QVariant &operator[](QString key) const;

private:
    ctkEventHash *m_EventHash;
};

typedef ctkEvent * ctkEventPointer;

} // namespace ctkEventBus

Q_DECLARE_METATYPE(ctkEventBus::ctkEventPointer);

#endif // CTKEVENTHEADER_H
