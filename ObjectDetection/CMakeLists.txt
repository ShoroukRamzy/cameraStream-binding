set(TARGET ObjectDetection)
add_library(${TARGET} MODULE ObjectDetection.cpp )
#The new dir
install(TARGETS ${TARGET} DESTINATION ${CMAKE_INSTALL_PREFIX}/redpesk/${PROJECT_NAME}/lib)
#install(TARGETS ${TARGET} DESTINATION /var/local/lib/afm/applications/${PROJECT_NAME}/lib)
