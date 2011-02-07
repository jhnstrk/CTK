#
# See CMake/ctkFunctionGetTargetLibraries.cmake
# 
# This file should list the libraries required to build the current CTK plugin.
# 

SET(target_libraries
  CTKPluginFramework
  QT_LIBRARIES
  QTSOAP_LIBRARY
  qxmlrpc_LIBRARY
  )
