/*
 *  ctkEventDefinitions.h
 *  ctkEventBus
 *
 *  Created by Paolo Quadrani on 27/03/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef CTKEVENTDEFINITIONS_H
#define CTKEVENTDEFINITIONS_H

// Qt includes
#include <QByteArray>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QThread>
#include <QThreadPool>
#include <QObject>
#include <QDebug>

#include "ctkEventBus_global.h"

//defines

#define TOPIC "EventTopic"
#define TYPE "EventType"
#define SIGTYPE "SignatureType"
#define OBJECT "ObjectPointer"
#define SIGNATURE "Signature"

class ctkEvent;

#define mafRegisterLocalSignal(topic, sender, signature) \
    {\
        ctkEvent *properties = new ctkEvent(topic, ctkEventBus::ctkEventTypeLocal, ctkEventBus::mafSignatureTypeSignal, static_cast<QObject*>(sender), signature); \
        bool ok = ctkEventBus::ctkEventBusManager::instance()->addEventProperty(*properties);\
        if(!ok) {\
            qWarning("%s", tr("Some problem occourred during the signal registration with ID '%1'.").arg(topic).toAscii().data());\
            if(properties) {delete properties; properties = NULL;} \
            }\
    }

#define mafRegisterRemoteSignal(topic, sender, signature) \
    {\
        ctkEvent *properties = new ctkEvent(topic, ctkEventBus::ctkEventTypeRemote, ctkEventBus::mafSignatureTypeSignal, static_cast<QObject*>(sender), signature); \
        bool ok =  ctkEventBus::ctkEventBusManager::instance()->addEventProperty(*properties);\
        if(!ok) {\
            qWarning("%s", tr("Some problem occourred during the signal registration with ID '%1'.").arg(topic).toAscii().data());\
            if(properties) {delete properties; properties = NULL;} \
        }\
    }

#define mafRegisterLocalCallback(topic, observer, signature) \
    {\
        ctkEvent *properties = new ctkEvent(topic, ctkEventBus::ctkEventTypeLocal, ctkEventBus::mafSignatureTypeCallback, static_cast<QObject*>(observer), signature); \
        bool ok =  ctkEventBus::ctkEventBusManager::instance()->addEventProperty(*properties);\
        if(!ok) {\
            qWarning("%s", tr("Some problem occourred during the callback registration with ID '%1'.").arg(topic).toAscii().data());\
            if(properties) {delete properties; properties = NULL;} \
        }\
    }

#define mafRegisterRemoteCallback(topic, sender, signature) \
    {\
        ctkEvent *properties = new ctkEvent(topic, ctkEventBus::ctkEventTypeRemote, ctkEventBus::mafSignatureTypeCallback, static_cast<QObject*>(sender), signature); \
        bool ok =  ctkEventBus::ctkEventBusManager::instance()->addEventProperty(*properties);\
        if(!ok) {\
            qWarning("%s", tr("Some problem occourred during the callback registration with ID '%1'.").arg(topic).toAscii().data());\
            if(properties) {delete properties; properties = NULL;} \
        }\
    }


namespace ctkEventBus {
//forward classes
class ctkNetworkConnector;

/// Hash table that associate the communication protocol with the corresponding network connector class (Eg. XMLRPC, ctkEventBus::ctkNetworkConnectorQXMLRPC)
typedef QHash<QString, ctkNetworkConnector *> ctkNetworkConnectorHash;

/// typedef that represents dictionary entries ( key  , value )
typedef QHash<QString, QVariant> ctkEventHash;

///< Enum that identify the ctkEventType's type: Local or Remote.
typedef enum {
    ctkEventTypeLocal,
    ctkEventTypeRemote
} ctkEventType;

///< Enum that identify the mafSignatureType's type: Signal or Callback.
typedef enum {
    mafSignatureTypeSignal = 0,
    mafSignatureTypeCallback = 1
} mafSignatureType;

/// List of the arguments to be sent through the event bus.
typedef QList<QGenericArgument> ctkEventArgumentsList;
typedef ctkEventArgumentsList * ctkEventArgumentsListPointer;
#define ctkEventArgument(type, data) QArgument<type >(#type, data)
#define mafGenericReturnArgument QGenericReturnArgument
#define ctkEventReturnArgument(type, data) QReturnArgument<type >(#type, data)


/// Types definitions for events' hash (to be more readable).
typedef QHash<QString, ctkEvent *> ctkEventsHashType;

/// type definition for observers' properties list to be stored into the event's hash.
typedef QList<ctkEvent *> ctkEventItemListType;

/// map which represent list of function to be registered in the server, with parameters
typedef QMap<QString, QList<QVariant::Type> >  mafRegisterMethodsMap;

} // namespace ctkEventBus


Q_DECLARE_METATYPE(ctkEventBus::ctkEventArgumentsListPointer);
Q_DECLARE_METATYPE(ctkEventBus::mafRegisterMethodsMap);

#endif // CTKEVENTDEFINITIONS_H
