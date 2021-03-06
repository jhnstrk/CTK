/*=========================================================================

  Library:   CTK

  Copyright (c)  

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// Qt includes
#include <QApplication>
#include <QTextStream>

// CTK includes
#include <ctkDICOMRetrieve.h>
#include <ctkDICOMDatabase.h>
#include "ctkLogger.h"

// DCMTK includes
#include "dcmtk/oflog/oflog.h"

// STD includes
#include <cstdlib>
#include <iostream>
#include <fstream>

void print_usage()
{
  std::cerr << "Usage:\n";
  std::cerr << "  ctkDICOMRetrieve StudyUID OutputDirectory callingAETitle calledAETitle host calledPort moveDestinationAETitle\n";
  return;
}


/**
  *
*/
int main(int argc, char** argv)
{
  ctkLogger::configure();
  ctkLogger logger ( "org.commontk.dicom.DICOMRetieveApp" );
  logger.setDebug();
  // Set the DCMTK log level to debug
  dcmtk::log4cplus::Logger rootLogger = dcmtk::log4cplus::Logger::getRoot();
  rootLogger.setLogLevel(dcmtk::log4cplus::DEBUG_LOG_LEVEL);

  if (argc < 9)
  {
    print_usage();
    return EXIT_FAILURE;
  }

  QCoreApplication app(argc, argv);
  QTextStream out(stdout);

  QString StudyUID ( argv[1] );
  QDir OutputDirectory ( argv[2] );
  QString CallingAETitle ( argv[3] ); 
  bool ok;
  QString CalledAETitle ( argv[4] ); 
  QString Host ( argv[5] ); 
  int CalledPort = QString ( argv[6] ).toInt ( &ok );
  if ( !ok )
    {
    std::cerr << "Could not convert " << argv[7] << " to an integer for the calledPoint" << std::endl;
    print_usage();
    return EXIT_FAILURE;
    }
  QString MoveDestinationAETitle ( argv[8] ); 

  ctkDICOMRetrieve retrieve;
  retrieve.setCallingAETitle ( CallingAETitle );
  retrieve.setCalledAETitle ( CalledAETitle );
  retrieve.setCalledPort ( CalledPort );
  retrieve.setHost ( Host );
  retrieve.setMoveDestinationAETitle ( MoveDestinationAETitle );

  logger.info ( "StudyUID: " + StudyUID + "\n" 
                + "OutputDirectory: " + OutputDirectory.absolutePath() + "\n"
                + "CallingAETitle: " + CallingAETitle + "\n"
                + "CalledAEtitle: " + CalledAETitle + "\n"
                + "Host: " + Host + "\n"
                + "CalledPort: " + QString::number ( CalledPort ) + "\n" );

  QSharedPointer<ctkDICOMDatabase> dicomDatabase =  QSharedPointer<ctkDICOMDatabase> (new ctkDICOMDatabase);
  dicomDatabase->openDatabase( OutputDirectory.absoluteFilePath(QString("ctkDICOM.sql")) );
  retrieve.setRetrieveDatabase( dicomDatabase );

  logger.info ( "Starting to retrieve" );
  try
    {
    retrieve.retrieveStudy ( StudyUID );
    }
  catch (std::exception e)
    {
    logger.error ( "Retrieve failed" );
    return EXIT_FAILURE;
    }
  logger.info ( "Retrieve success" );
  return EXIT_SUCCESS;
}
