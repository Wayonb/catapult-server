cmake_minimum_required(VERSION 3.2)

set(TARGET_NAME catapult.tools.pipeline.impl)

catapult_library_target(${TARGET_NAME})
target_link_libraries(${TARGET_NAME} catapult.tools catapult.local.server)

# tool has local node dependency, so it must be able to access src
include_directories(${PROJECT_SOURCE_DIR}/src)
