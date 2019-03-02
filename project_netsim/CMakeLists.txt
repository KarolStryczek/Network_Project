# 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
cmake_minimum_required(VERSION 3.12)
project(project_netsim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(include)

# Debug configuration
set(SOURCE_FILES
		src/Nodes/ReceiverPreferences.cpp
		src/Storage/Package.cpp
		src/Nodes/PackageSender.cpp
		src/Storage/PackageQueue.cpp
		src/Nodes/Worker.cpp
		src/Nodes/Storehouse.cpp
		src/Nodes/Ramp.cpp
		src/Simulate.cpp
		#src/Factory_Package/Factory.cpp
        #src/IO.cpp
        src/Factory_Package/NodeCollection.cpp
		#src/Report_Generation/SpecificTurnsReportNotifier.cpp
		#src/Report_Generation/IntervalReportNotifier.cpp
		#src/Report_Generation/Reporting.cpp
        )

add_executable(project_netsim_debug ${SOURCE_FILES} main.cpp)

# Test configuration
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")

set(SOURCES_FILES_TESTS
        test/testRamp.cpp
        test/testWorker.cpp
        test/testPackageSender.cpp
		test/testPackageQueue.cpp
		test/testPackage.cpp
		test/testStorehouse.cpp
		#test/testFactory.cpp
		#test/testIO.cpp
		test/testNodeCollection.cpp
		#test/testSpecificTurnsReportNotifier.cpp
		#test/testIntervalReportNotifier.cpp
		#test/testGenerateStructureReportToFile.cpp
		#test/testGenerateSimulationTurnReportToFile.cpp
		#test/testSimulate.cpp
		test/testReceiverPreferences.cpp
		)


add_subdirectory(googletest-master)

add_executable(project_netsim_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_test.cpp)

target_include_directories(project_netsim_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

target_link_libraries(project_netsim_test gmock)

# 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)