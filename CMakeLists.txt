cmake_minimum_required(VERSION 3.16)

project(cubGL
	VERSION 1.0.0
	LANGUAGES CXX
)

add_compile_options(-Wall -Wextra -Werror)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
	OpenGLWidgets
	Widgets
)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
	./src/cubGL.cpp
	./src/Scene.cpp
	./src/UploadButton.cpp
	./ressources.qrc
)

target_include_directories(${PROJECT_NAME} PRIVATE
	./include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	Qt6::OpenGLWidgets
	Qt6::Widgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	WIN32_EXECUTABLE ON
	MACOSX_BUNDLE ON
)
