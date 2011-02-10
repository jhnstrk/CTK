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
#ifndef CTKBUSEVENT_H
#define CTKBUSEVENT_H

#include "ctkPluginFrameworkExport.h"
#include <service/event/ctkEvent.h>

#include <QMap>
#include <QVariant>
#include <QStringList>

class ctkBusEventData;

/**
 * A CTK event.
 *
 * <code>ctkEvent</code> objects are delivered to <code>ctkEventHandler</code>
 * or Qt slots which subscribe to the topic of the event.
 */
class CTK_PLUGINFW_EXPORT ctkBusEvent : public ctkEvent
{
   QSharedDataPointer<ctkBusEventData> d;
   
public:

  /**
   * Default constructor for use with the Qt meta object system.
   */
  ctkBusEvent();

  ~ctkBusEvent();

  /**
   * Constructs an event.
   *
   * @param topic The topic of the event.
   * @param properties The event's properties (may be empty).
   * @throws std::invalid_argument If topic is not a valid topic name.
   */
  ctkBusEvent(const QString& topic, const ctkDictionary& properties = ctkDictionary());
  ctkBusEvent(const ctkBusEvent& event);
  ctkBusEvent(QString topic, int event_type, int signature_type, QObject *objectPointer, QString signature);

  /// Allow to assign the event type: ctkEventTypeLocal or ctkEventTypeRemote.
  void setEventType(int et);

  /// Return the type of the event: ctkEventTypeLocal or ctkEventTypeRemote.
  int eventType() const;

  /// Check if the event is local or not.
  bool isEventLocal() const;

  /// Allow to set or modify the event ID
  void setEventTopic(QString topic);

  /// Return the Id associated with the event.
  QString eventTopic() const;

  /// Overload operator for rapid access to mafDictionaryEntries
  QVariant &operator[](QString key);
};


#endif // CTKBUSEVENT_H
