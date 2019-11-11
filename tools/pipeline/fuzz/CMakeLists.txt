cmake_minimum_required(VERSION 3.2)

set(TARGET_NAME catapult.tools.pipeline.fuzz)

catapult_shared_library_target(${TARGET_NAME})
target_link_libraries(catapult.tools.pipeline.fuzz catapult.tools.pipeline.impl)
