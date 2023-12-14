set(TARGET CameraStream)
add_library(${TARGET} MODULE CameraReader.cpp )
install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_PREFIX}/redpesk/${PROJECT_NAME}/lib)
#install(TARGETS ${TARGET} DESTINATION /var/local/lib/afm/applications/${PROJECT_NAME}/lib)


