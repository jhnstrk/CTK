#
# qxmlrpc
#

SET(qxmlrpc_DEPENDS)
ctkMacroShouldAddExternalProject(qxmlrpc_LIBRARY add_project)
IF(${add_project})
  
  SET(proj qxmlrpc)
  MESSAGE(STATUS "Adding project:${proj}")
  SET(qxmlrpc_DEPENDS ${proj})

  SET(_qxmlrpc_url "${CTK_SOURCE_DIR}/Utilities/qxmlrpc/qxmlrpc.tar.gz")
  IF(WIN32)
    SET(_make_cmd nmake)
    IF(MINGW)
      SET(_make_cmd mingw32-make)
    ENDIF()
  ELSE()
    SET(_make_cmd make)
  ENDIF()

  
  # Patch program
  FIND_PROGRAM(CTK_PATCH_EXECUTABLE patch
    "C:/Program Files/GnuWin32/bin"
    "C:/Program Files (x86)/GnuWin32/bin")
  MARK_AS_ADVANCED(CTK_PATCH_EXECUTABLE)
  IF(NOT CTK_PATCH_EXECUTABLE)
    MESSAGE(FATAL_ERROR "error: Patch is required to build ${PROJECT_NAME}. Set CTK_PATCH_EXECUTABLE")
  ENDIF()

  # Configure patch script
  SET(qxmlrpc_src_dir ${ep_source_dir}/${proj}/xmlrpc)
  SET(qxmlrpc_patch_dir ${CTK_SOURCE_DIR}/Utilities/qxmlrpc)
  SET(qxmlrpc_configured_patch_dir ${CTK_BINARY_DIR}/Utilities/qxmlrpc)
  SET(qxmlrpc_patchscript
    ${qxmlrpc_configured_patch_dir}/qxmlrpc-patch.cmake)
  CONFIGURE_FILE(
    ${CTK_SOURCE_DIR}/Utilities/qxmlrpc/qxmlrpc-patch.cmake.in
    ${qxmlrpc_patchscript} @ONLY)
  
  SET(_qxmlrpc_build_script "${CTK_BINARY_DIR}/Utilities/qxmlrpc/BuildScript.cmake")
  CONFIGURE_FILE("${CTK_SOURCE_DIR}/Utilities/qxmlrpc/BuildScript.cmake.in" ${_qxmlrpc_build_script} @ONLY)

  SET(_qxmlrpc_install_script "${CTK_BINARY_DIR}/Utilities/qxmlrpc/InstallScript.cmake")
  CONFIGURE_FILE("${CTK_SOURCE_DIR}/Utilities/qxmlrpc/InstallScript.cmake.in" ${_qxmlrpc_install_script} @ONLY)

  ExternalProject_Add(${proj}
    URL ${_qxmlrpc_url}
    PATCH_COMMAND ${CMAKE_COMMAND} -P ${qxmlrpc_patchscript}
    CONFIGURE_COMMAND cd .
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${CMAKE_COMMAND} -P ${_qxmlrpc_build_script}
    INSTALL_COMMAND ${CMAKE_COMMAND} -D INTERMEDIATE_DIRECTORY:STRING=$(IntDir) -P ${_qxmlrpc_install_script}
  )
  
  SET(qxmlrpc_DIR "${CTK_BINARY_DIR}/Utilities/qxmlrpc/")

  # Since the full path of PythonQt library is used, there is not need to add 
  # its corresponding library output directory to CTK_EXTERNAL_LIBRARY_DIRS
    
ENDIF()
