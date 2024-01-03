# Project's name
project(camera_streamer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Find OpenCV
find_package(OpenCV REQUIRED)

set(TARGET CameraStream)
add_library(${TARGET} MODULE 
        src/main.cpp
        src/CameraManager.cpp
        src/VirtualCamera.cpp
        src/VideoStream.cpp
        src/FrameProcessor.cpp
        src/FramesPublisher.cpp
        src/CircQProcessedFrames.cpp
        src/Config
        src/ImageLoader.cpp
        )

target_include_directories(${TARGET} PRIVATE
        include
        ${OpenCV_INCLUDE_DIRS}
        external
)

install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_PREFIX}/redpesk/${PROJECT_NAME}/lib)
#install(TARGETS ${TARGET} DESTINATION /var/local/lib/afm/applications/${PROJECT_NAME}/lib)

# Link OpenCV to the project
target_link_libraries(${TARGET} ${OpenCV_LIBS})


