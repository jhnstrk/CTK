MACRO(mafMacroGetTargetLibraries varname)

  SET(filepath ${CMAKE_CURRENT_SOURCE_DIR}/target_libraries.cmake)

  # Check if "target_libraries.cmake" file exists
#  IF(NOT EXISTS ${filepath} )
#    MESSAGE(FATAL_ERROR "${filepath} doesn't exists !")
#  ENDIF()

  # Make sure the variable is cleared
  SET(target_libraries )

  # Check if "target_libraries.cmake" file exists
  # if the file does not exists, no external dependences are assigned.
  IF(EXISTS ${filepath})
    # Let's make sure target_libraries contains only strings
    FILE(STRINGS "${filepath}" stringtocheck) # read content of 'filepath' into 'stringtocheck'
    #STRING(REGEX MATCHALL "[^\\#]\\$\\{.*\\}" incorrect_elements ${stringtocheck})
    FOREACH(incorrect_element ${incorrect_elements})
      STRING(REGEX REPLACE "\\$|\\{|\\}" "" correct_element ${incorrect_element})
      MESSAGE(FATAL_ERROR "In ${filepath}, ${incorrect_element} should be replaced by ${correct_element}")
    ENDFOREACH()

    INCLUDE(${filepath})

    # Loop over all target library
    # Loop over all target files, let's resolve the variable to access its content
    FOREACH(target_library ${target_libraries})
      LIST(APPEND ${varname} "${target_library}")
    ENDFOREACH()
  ENDIF()

ENDMACRO()

MACRO(mafMacroInitProject test)

  # Extract current directory name to use as project name
  file(GLOB CUR_FILE "CMakeLists.txt")
  get_filename_component(CUR_ABSOLUTE_DIR ${CUR_FILE} PATH)
  get_filename_component(DIR_NAME ${CUR_ABSOLUTE_DIR} NAME)
  PROJECT(${DIR_NAME})

  FILE(GLOB include_file_list "${PROJECT_SOURCE_DIR}/*.h")
  FILE(GLOB implementation_file_list "${PROJECT_SOURCE_DIR}/*.cpp")
  FILE(GLOB templete_file_list1 "${PROJECT_SOURCE_DIR}/*.txx")
  FILE(GLOB templete_file_list2 "${PROJECT_SOURCE_DIR}/*.tpp")
  FILE(GLOB resource_file_list "${PROJECT_SOURCE_DIR}/*.qrc")
  FILE(GLOB ui_file_list "${PROJECT_SOURCE_DIR}/*.ui")

  # Set your list of sources here.
  SET(PROJECT_SRCS
        ${implementation_file_list}
        ${include_file_list}
        ${templete_file_list1}
        ${templete_file_list2}
        ${ui_file_list}
        ${resource_file_list}
  )

  ## Add the project binary dir as include dir for the .moc files.
  INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

  set(MY_MOC_CXX )
  if(${test})
    ## Moc the tests:
    foreach(FILE_NAME_ABS ${implementation_file_list})
      ## extract the base file name.
      get_filename_component(FILE_NAME ${FILE_NAME_ABS} NAME_WE)
      ## Exclude the main.cpp file (it doesn't ned to be 'mocced')
      if(NOT ${FILE_NAME} STREQUAL "main")
        ## Assign the moc custom filename
        set(MOC_FILE "${FILE_NAME}.moc")
        QT4_GENERATE_MOC(${FILE_NAME_ABS} ${MOC_FILE})
        LIST(APPEND MY_MOC_CXX "${PROJECT_BINARY_DIR}/${MOC_FILE}")
      endif(NOT ${FILE_NAME} STREQUAL "main")
    endforeach()
  else(${test})
    ## Moc the library's .h files
    QT4_WRAP_CPP(MY_MOC_CXX ${include_file_list})
    QT4_WRAP_UI(MY_UI_CXX ${ui_file_list})
    #QT4_ADD_RESOURCES(MY_RESOURCE_CXX ${resource_file_list})
  endif(${test})

  SET(PROJECT_SRCS
    ${PROJECT_SRCS}
    ${MY_MOC_CXX}
    ${MY_UI_CXX}
    ${resource_file_list}
    )

  # List libraries that are needed by this project.
  mafMacroGetTargetLibraries(dependency_libraries)
  SET(PROJECT_LIBS ${dependency_libraries})

ENDMACRO()

PROJECT(org_commontk_eventbustest)

## #################################################################
## Init Project
## #################################################################

mafMacroInitProject(1)

## #################################################################
## Build rules
## #################################################################

# Create the executable.

SET(test_executable ${PROJECT_NAME})

ADD_EXECUTABLE(${test_executable} ${PROJECT_SRCS})
ADD_TEST(${PROJECT_NAME} ${CPP_TEST_PATH}/${test_executable})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PROJECT_LIBS})
LINK_LIBRARIES(${PROJECT_LIBS})
ADD_DEPENDENCIES(${PROJECT_NAME} ${PROJECT_NAME} ${eventbus_test})

