#
# qxmlrpc
#

SET(qxmlrpc_DEPENDS)
ctkMacroShouldAddExternalProject(qxmlrpc_LIBRARY add_project)
IF(${add_project})

  # Sanity checks
  IF(DEFINED qxmlrpc_DIR AND NOT EXISTS ${qxmlrpc_DIR})
    MESSAGE(FATAL_ERROR "qxmlrpc_DIR variable is defined but corresponds to non-existing directory")
  ENDIF()
  
  SET(qxmlrpc_enabling_variable qxmlrpc_LIBRARY)
  
  SET(proj qxmlrpc)
  SET(proj_DEPENDENCIES)
  
  SET(qxmlrpc_DEPENDS ${proj})

  IF(NOT DEFINED qxmlrpc_DIR)
    #MESSAGE(STATUS "Adding project:${proj}")
    
    ExternalProject_Add(${proj}
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
    SET(qxmlrpc_DIR ${ep_build_dir}/${proj})
    
    # Since qxmlrpc is statically build, there is not need to add its corresponding 
    # library output directory to CTK_EXTERNAL_LIBRARY_DIRS
  
  ELSE()
    ctkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()
  
  SET(${qxmlrpc_enabling_variable}_INCLUDE_DIRS qxmlrpc_INCLUDE_DIRS)
  SET(${qxmlrpc_enabling_variable}_FIND_PACKAGE_CMD qxmlrpc)
    
ENDIF()

