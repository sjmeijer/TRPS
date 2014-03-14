#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(TRPSGe)

# include ROOT stuff
include(FindROOT.cmake)
# set build type
set(CMAKE_BUILD_TYPE Debug)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can Set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${ROOT_INCLUDE_DIR})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(XGeBox XGeBox.cc ${sources} ${headers})
#tarGet_link_libraries(XGeBox ${Geant4_LIBRARIES} )
tarGet_link_libraries(XGeBox ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
#link_directories(${ROOT_LIBRARY_DIR})
#tarGet_link_libraries(${ROOT_LIBRARY_DIR})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(TRPSGe_SCRIPTS
    run.in vis.mac
  )

set(TRPSGe_DATA
    CrystalMaps/
  )

foreach(_script ${TRPSGe_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

file(COPY ${PROJECT_SOURCE_DIR}/${TRPSGe_DATA} DESTINATION ${PROJECT_BINARY_DIR}/${TRPSGe_DATA})

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_tarGet(TRPSGe DEPENDS XGeBox)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS XGeBox DESTINATION bin)


