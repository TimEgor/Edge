set (ALL_SOURCE_FILE_EXTENSIONS
	"*.h"
	"*.hpp"
	"*.c"
	"*.cpp"
	"*.cmake"
	"*.inl"
	"*.natvis"
)

### edge_get_directory_sources_recurse
function(edge_get_directory_sources_recurse SOURCE_DIR_PATH SOURCE_FILES)
	foreach(FILE_EXTENSION ${ALL_SOURCE_FILE_EXTENSIONS})
		file(GLOB_RECURSE TMP_SRCS "${SOURCE_DIR_PATH}/${FILE_EXTENSION}")
		list(APPEND RESULT_FILES ${TMP_SRCS})
	endforeach(FILE_EXTENSION)

	list(APPEND RESULT_FILES ${${SOURCE_FILES}})
	set(${SOURCE_FILES} ${RESULT_FILES} PARENT_SCOPE)
endfunction()

### edge_get_directory_sources
function(edge_get_directory_sources SOURCE_DIR_PATH SOURCE_FILES)
	foreach(FILE_EXTENSION ${ALL_SOURCE_FILE_EXTENSIONS})
		file(GLOB TMP_SRCS "${SOURCE_DIR_PATH}/${FILE_EXTENSION}")
		list(APPEND RESULT_FILES ${TMP_SRCS})
	endforeach(FILE_EXTENSION)

	list(APPEND RESULT_FILES ${${SOURCE_FILES}})
	set(${SOURCE_FILES} ${RESULT_FILES} PARENT_SCOPE)
endfunction()

### edge_get_subdir_names
function(edge_get_subdirs_names DIR_PATH SUBDIRS_NAMES)
	file(GLOB DIR_FILES RELATIVE ${DIR_PATH} "${DIR_PATH}/*")
	foreach(FILE_NAME ${DIR_FILES})
		if(IS_DIRECTORY "${DIR_PATH}/${FILE_NAME}")
			list(APPEND RESULT_NAMES ${FILE_NAME})
		endif()
	endforeach()

	set(${SUBDIRS_NAMES} ${RESULT_NAMES} PARENT_SCOPE)
endfunction()

### edge_get_all_sources_subdirs
function(edge_get_all_sources_subdirs SOURCE_DIR_PATH SUBDIRS_NAMES SOURCE_FILES)
	set(SUBDIR_GROUP_SRCS)
	
	edge_get_directory_sources(${SOURCE_DIR_PATH} SUBDIR_GROUP_SRCS)

	foreach(SUBDIR_NAME ${SUBDIRS_NAMES})
		set(SUBDIR_SRCS)
		edge_get_all_group_sources_recurse("${SOURCE_DIR_PATH}/${SUBDIR_NAME}" ${SUBDIR_NAME} SUBDIR_SRCS)

		list(APPEND SUBDIR_GROUP_SRCS ${SUBDIR_SRCS})
	endforeach()

	list(APPEND SUBDIR_GROUP_SRCS ${${SOURCE_FILES}})

	set(${SOURCE_FILES} ${SUBDIR_GROUP_SRCS} PARENT_SCOPE)
endfunction()

### edge_get_all_group_sources_recurse
function(edge_get_all_group_sources_recurse SOURCE_DIR_PATH GROUP_NAME SOURCE_FILES)
	set(GROUP_CMAKE_FILE_PATH "${SOURCE_DIR_PATH}/${GROUP_NAME}.cmake")

	if(EXISTS ${GROUP_CMAKE_FILE_PATH})
		include(${GROUP_CMAKE_FILE_PATH})
	else()
		edge_get_subdirs_names(${SOURCE_DIR_PATH} SUBDIRS_NAMES)
		edge_get_all_sources_subdirs(${SOURCE_DIR_PATH} "${SUBDIRS_NAMES}" GROUP_SRCS)
	endif()
	
	list(APPEND GROUP_SRCS ${${SOURCE_FILES}})
	set(${SOURCE_FILES} ${GROUP_SRCS} PARENT_SCOPE)
endfunction()

### edge_get_all_sources_recurse
function(edge_get_all_sources_recurse SOURCE_DIR_PATH SOURCE_FILES)
	edge_get_subdirs_names(${SOURCE_DIR_PATH} SUBDIRS_NAMES)
	edge_get_all_sources_subdirs(${SOURCE_DIR_PATH} "${SUBDIRS_NAMES}" GROUP_SRCS)
	
	list(APPEND GROUP_SRCS ${${SOURCE_FILES}})
	set(${SOURCE_FILES} ${GROUP_SRCS} PARENT_SCOPE)
endfunction()

### edge_generate_source_groups_by_sources_prefix
function(edge_generate_source_groups_by_sources_prefix SOURCE_DIR_PATH PREFIX_DIR SOURCE_FILES)
	string(LENGTH ${SOURCE_DIR_PATH} SOURCE_DIR_PATH_LENGTH)
	foreach(SOURCE_FILE_NAME ${${SOURCE_FILES}})
		if(${SOURCE_FILE_NAME} MATCHES ${SOURCE_DIR_PATH})
			string(SUBSTRING ${SOURCE_FILE_NAME} ${SOURCE_DIR_PATH_LENGTH} -1 RELATIVE_SOURCE_FILE_PATH)
			string(FIND ${RELATIVE_SOURCE_FILE_PATH} / FILE_NAME_SEPARATOR_POSITION REVERSE)
			string(SUBSTRING ${RELATIVE_SOURCE_FILE_PATH} 0 ${FILE_NAME_SEPARATOR_POSITION} SOURCE_GROUP_NAME)

			if (PREFIX_DIR STREQUAL "")
				source_group(TREE ${SOURCE_DIR_PATH} FILES ${SOURCE_FILE_NAME})
			else()
				source_group(TREE ${SOURCE_DIR_PATH} PREFIX ${PREFIX_DIR} FILES ${SOURCE_FILE_NAME})
			endif()
		endif()
	endforeach(SOURCE_FILE_NAME)
endfunction()

### edge_generate_source_groups_by_sources
function(edge_generate_source_groups_by_sources SOURCE_DIR_PATH SOURCE_FILES)
	edge_generate_source_groups_by_sources_prefix("${SOURCE_DIR_PATH}" "" ${SOURCE_FILES})
endfunction()