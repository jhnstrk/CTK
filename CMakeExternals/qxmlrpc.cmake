#
# qxmlrpc
#

set(qxmlrpc_DEPENDS)
ctkMacroShouldAddExternalproject(qxmlrpc_LIBRARY add_project)
if(${add_project})

  # Sanity checks
  if(DEFINED qxmlrpc_DIR AND NOT EXISTS ${qxmlrpc_DIR})
    message(FATAL_ERROR "qxmlrpc_DIR variable is defined but corresponds to non-existing directory")
  endif()
  
  set(qxmlrpc_enabling_variable qxmlrpc_LIBRARY)
  
  set(proj qxmlrpc)
  set(proj_DEPENDENCIES)
  
  set(qxmlrpc_DEPENDS ${proj})

  if(NOT DEFINED qxmlrpc_DIR)
    #message(STATUS "Adding project:${proj}")
    
    ExternalProject_Add(${proj}
      SOURCE_DIR ${CMAKE_BINARY_DIR}/${proj}
      BINARY_DIR ${proj}-build
      PREFIX ${proj}${ep_suffix}
      GIT_REPOSITORY "${git_protocol}://github.com/commontk/qxmlrpc.git"
      GIT_TAG "origin/patched"
      CMAKE_GENERATOR ${gen}
      INSTALL_COMMAND ""
      CMAKE_ARGS
        ${ep_common_args}
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
      DEPENDS
        ${proj_DEPENDENCIES}
      )
    set(qxmlrpc_DIR "${CMAKE_BINARY_DIR}/${proj}-build")
    
    # Since qxmlrpc is statically build, there is not need to add its corresponding 
    # library output directory to CTK_EXTERNAL_LIBRARY_DIRS
  
  else()
    ctkMacroEmptyExternalproject(${proj} "${proj_DEPENDENCIES}")
  endif()
  
  list(APPEND CTK_SUPERBUILD_EP_VARS qxmlrpc_DIR:PATH)

  set(${qxmlrpc_enabling_variable}_LIBRARY_DIRS qxmlrpc_LIBRARY_DIRS)
  set(${qxmlrpc_enabling_variable}_INCLUDE_DIRS qxmlrpc_INCLUDE_DIRS)
  set(${qxmlrpc_enabling_variable}_FIND_PACKAGE_CMD qxmlrpc)
    
endif()

