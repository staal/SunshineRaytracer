macro(create_vs_folders)
    #Source https://github.com/kylewm/kylewm.com-frozen-flask/blob/master/content/2013-06-18-cmake-automatic-source-groups.md
    #Sort source files into visual studio folders
    foreach(FILE ${SOURCES}) 
      get_filename_component(PARENT_DIR "${FILE}" PATH)

      # skip src or include and changes /'s to \\'s
      string(REGEX REPLACE "(\\./)?(src|include)/?" "" GROUP "${PARENT_DIR}")
      string(REPLACE "/" "\\" GROUP "${GROUP}")

      # group into "Source Files" and "Header Files"
      if ("${FILE}" MATCHES ".*\\.cpp")
        set(GROUP "Source Files\\${GROUP}")
      elseif("${FILE}" MATCHES ".*\\.h")
        set(GROUP "Header Files\\${GROUP}")
      endif()

      source_group("${GROUP}" FILES "${FILE}")
    endforeach()
endmacro(create_vs_folders

set_property(GLOBAL PROPERTY USE_FOLDERS ON))