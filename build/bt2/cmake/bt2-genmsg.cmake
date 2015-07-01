# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "bt2: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ibt2:/home/cipa/catkin_ws/src/bt2/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(bt2_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/cipa/catkin_ws/src/bt2/msg/Num.msg" NAME_WE)
add_custom_target(_bt2_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "bt2" "/home/cipa/catkin_ws/src/bt2/msg/Num.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(bt2
  "/home/cipa/catkin_ws/src/bt2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bt2
)

### Generating Services

### Generating Module File
_generate_module_cpp(bt2
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bt2
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(bt2_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(bt2_generate_messages bt2_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cipa/catkin_ws/src/bt2/msg/Num.msg" NAME_WE)
add_dependencies(bt2_generate_messages_cpp _bt2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bt2_gencpp)
add_dependencies(bt2_gencpp bt2_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bt2_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(bt2
  "/home/cipa/catkin_ws/src/bt2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bt2
)

### Generating Services

### Generating Module File
_generate_module_lisp(bt2
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bt2
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(bt2_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(bt2_generate_messages bt2_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cipa/catkin_ws/src/bt2/msg/Num.msg" NAME_WE)
add_dependencies(bt2_generate_messages_lisp _bt2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bt2_genlisp)
add_dependencies(bt2_genlisp bt2_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bt2_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(bt2
  "/home/cipa/catkin_ws/src/bt2/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bt2
)

### Generating Services

### Generating Module File
_generate_module_py(bt2
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bt2
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(bt2_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(bt2_generate_messages bt2_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cipa/catkin_ws/src/bt2/msg/Num.msg" NAME_WE)
add_dependencies(bt2_generate_messages_py _bt2_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(bt2_genpy)
add_dependencies(bt2_genpy bt2_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS bt2_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bt2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/bt2
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(bt2_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bt2)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/bt2
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(bt2_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bt2)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bt2\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/bt2
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(bt2_generate_messages_py std_msgs_generate_messages_py)
