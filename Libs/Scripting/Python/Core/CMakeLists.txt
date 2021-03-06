project(CTKScriptingPythonCore)

#
# 3rd party dependencies
#
if(CTK_LIB_Scripting/Python/Core_PYTHONQT_USE_VTK)
  include(${VTK_USE_FILE})
endif()

#
# See CTK/CMake/ctkMacroBuildLib.cmake for details
#

set(KIT_export_directive "CTK_SCRIPTING_PYTHON_CORE_EXPORT")


# Source files
set(KIT_SRCS
  ctkAbstractPythonManager.cpp
  ctkAbstractPythonManager.h
  )

# Headers that should run through moc
set(KIT_MOC_SRCS
  ctkAbstractPythonManager.h
  )

# UI files
set(KIT_UI_FORMS
)

# Resources
set(KIT_resources
)

#
# Configure file describing which Qt modules are wrapped
#
foreach(qtlib CORE GUI NETWORK OPENGL SQL SVG UITOOLS WEBKIT XML XMLPATTERNS)
  set(CTK_PYTHONQT_WRAP_QT${qtlib} ${CTK_LIB_Scripting/Python/Core_PYTHONQT_WRAP_QT${qtlib}})
  #message(CTK_LIB_Scripting/Python/Core_PYTHONQT_WRAP_QT${qtlib}:${CTK_LIB_Scripting/Python/Core_PYTHONQT_WRAP_QT${qtlib}})
endforeach()

configure_file(
  ctkScriptingPythonCoreConfigure.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/ctkScriptingPythonCoreConfigure.h
  )

# Target libraries - See CMake/ctkFunctionGetTargetLibraries.cmake
# The following macro will read the target libraries from the file 'target_libraries.cmake'
ctkFunctionGetTargetLibraries(KIT_target_libraries)

# Link against vtkPython if required
if(CTK_LIB_Scripting/Python/Core_PYTHONQT_USE_VTK)
  list(APPEND KIT_target_libraries vtkPythonCore)
endif()

ctkMacroBuildLib(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${KIT_export_directive}
  SRCS ${KIT_SRCS}
  MOC_SRCS ${KIT_MOC_SRCS}
  UI_FORMS ${KIT_UI_FORMS}
  TARGET_LIBRARIES ${KIT_target_libraries}
  RESOURCES ${KIT_resources}
  LIBRARY_TYPE ${CTK_LIBRARY_MODE}
  )

# Plugins
#if(BUILD_QTDESIGNER_PLUGINS)
#  add_subdirectory(Plugins)
#endif()

add_subdirectory(Python)

# Testing
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
