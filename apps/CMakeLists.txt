#add_executable(gnl-bin gnl.c)
#target_link_libraries(gnl-bin PRIVATE gnl)
#set_target_properties(gnl-bin PROPERTIES OUTPUT_NAME gnl)

# standalone test libraries
if(BUILD_TESTING)
	add_executable(torture-gnl.bin torture-gnl.c)
	target_link_libraries(torture-gnl.bin PRIVATE gnl)
endif()
