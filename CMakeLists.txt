cmake_minimum_required(VERSION 3.5)
project(EgoLocalizationSim2D VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

set(SRC_CPP
    src/main.cpp
    src/sim_display.cpp
    src/ego_vehicle.h
    src/ego_tracking_simulation.cpp
    src/utils.cpp
    src/sim_display.cpp
)

add_executable(${PROJECT_NAME}
        ${SRC_CPP}
        )

target_link_libraries(${PROJECT_NAME}
        SDL2
        SDL2_ttf
        Eigen3::Eigen
        )

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    

# look for Doxygen package
find_package(Doxygen)

if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs_doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target( docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
