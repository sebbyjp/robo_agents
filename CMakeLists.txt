cmake_minimum_required(VERSION 3.5)

project(robo_agents VERSION 0.1 LANGUAGES CXX)
option(BUILD_TESTS "Wether or not to build tests." OFF)
set(DOWNLOAD_EXTRACT_TIMESTAMP true)
include(CMakePackageConfigHelpers)
add_library(robo_agents INTERFACE)
target_include_directories(robo_agents INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    target_compile_features(robo_agents INTERFACE cxx_std_17)
endif()

if(${CMAKE_VERSION} VERSION_LESS "3.14.0")
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/robo_agentsConfigVersion.cmake"
        VERSION 0.1
        COMPATIBILITY AnyNewerVersion
    )
else()
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/robo_agentsConfigVersion.cmake"
        VERSION 0.1
        COMPATIBILITY AnyNewerVersion
        ARCH_INDEPENDENT
    )
endif()
if(${CMAKE_VERSION} VERSION_GREATER "3.26.0")
    cmake_policy(SET CMP0135 NEW)
endif()

install(TARGETS robo_agents
    EXPORT robo_agentsTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/robo_agentsConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/robo_agentsConfig.cmake"
    INSTALL_DESTINATION lib/cmake/robo_agents
)

install(EXPORT robo_agentsTargets DESTINATION lib/cmake/robo_agents)
install(FILES "${PROJECT_BINARY_DIR}/robo_agentsConfigVersion.cmake"
    "${PROJECT_BINARY_DIR}/robo_agentsConfig.cmake"
    DESTINATION lib/cmake/robo_agents)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

if(BUILD_TESTS)
    message(NOTICE "Building Tests...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    include(GoogleTest)
    add_executable(replay_buffer_test tests/replay_buffer_test.cpp)
    target_link_libraries(replay_buffer_test GTest::gtest_main robo_agents)

    add_executable(actor_test tests/actor_test.cpp)
    target_link_libraries(actor_test GTest::gtest_main robo_agents)

    add_executable(observer_test tests/observer_test.cpp)
    target_link_libraries(observer_test GTest::gtest_main robo_agents)
    include(GoogleTest)
    gtest_discover_tests(replay_buffer_test)
    gtest_discover_tests(observer_test)
    gtest_discover_tests(actor_test)
    # find_package(GTest REQUIRED)

    # add_executable(replay_buffer_test tests/replay_buffer_test.cpp)
    # target_link_libraries(replay_buffer_test GTest::gtest_main robo_agents)

    # add_executable(actor_test tests/actor_test.cpp)
    # target_link_libraries(actor_test GTest::gtest_main robo_agents)

    # add_executable(observer_test tests/observer_test.cpp)
    # target_link_libraries(observer_test GTest::gtest_main robo_agents)

    # gtest_add_tests(TARGET replay_buffer_test)
    # gtest_add_tests(TARGET actor_test)
    # gtest_add_tests(TARGET observer_test)

    # message(NOTICE "Building Tests...")
    # enable_testing()
    # find_package(GTest REQUIRED)
    # # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # add_executable(replay_buffer_test tests/replay_buffer_test.cpp)
    # target_link_libraries(replay_buffer_test GTest::gtest_main robo_agents)

    # add_executable(actor_test tests/actor_test.cpp)
    # target_link_libraries(actor_test GTest::gtest_main robo_agents)

    # add_executable(observer_test tests/observer_test.cpp)
    # target_link_libraries(observer_test GTest::gtest_main robo_agents)

    # include(GoogleTest)
    # gtest_discover_tests(observer_test actor_test replay_buffer_test)
endif()
