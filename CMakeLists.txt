# CMakeList.txt: проект CMake для Symbolica;
cmake_minimum_required (VERSION 3.8)

# Политика для отладочной информации в MSVC (горячая перезагрузка)
if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

# Общие настройки
project(Symbolica VERSION 0.1.0 LANGUAGES C CXX)

# -----------------------------------------------------------------------------
# Определение платформы и путей к библиотеке
# -----------------------------------------------------------------------------
if(WIN32)
    set(BLT_PLATFORM_DIR "Windows64")
    set(BLT_LIB_EXT ".lib")
    set(BLT_DLL_EXT ".dll")
    set(BLT_COPY_COMMAND copy_if_different)
elseif(UNIX AND NOT APPLE)
    set(BLT_PLATFORM_DIR "Linux64")
    set(BLT_LIB_EXT ".so")           # обычно .so для динамической библиотеки, если статическая - .a
    set(BLT_DLL_EXT ".so")           # или .so.x.x
    set(BLT_COPY_COMMAND copy_if_different)  # в Linux тоже можно использовать copy_if_different
    # Для Linux можно также настроить rpath, чтобы не копировать .so
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Дополнительные флаги (опционально)
if(MSVC)
    add_compile_options(/W4 /WX-)
else()
    add_compile_options(-Wall -Wextra -Wzero-as-null-pointer-constant -Winit-self -Wswitch-default -Wfloat-equal -Wno-unused-parameter -fPIC)
endif()

# -----------------------------------------------------------------------------
# 2. Поиск библиотеки BearLibTerminal
# -----------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

# Указываем корневую папку библиотеки, чтобы модуль нашёл её
set(BearLibTerminal_ROOT "${PROJECT_SOURCE_DIR}/lib/BearLibTerminal/${BLT_PLATFORM_DIR}")

# Ищем библиотеку (требуется)
find_package(BearLibTerminal REQUIRED)
message(STATUS "BLT_LIBRARY (variable) = ${BLT_LIBRARY}")

# Проверяем, что переменные определены
if(NOT BLT_INCLUDE_DIRS)
    message(FATAL_ERROR "BLT_INCLUDE_DIRS not set by FindBearLibTerminal.cmake")
endif()
if(NOT BLT_LIBRARIES)
    message(FATAL_ERROR "BLT_LIBRARIES not set by FindBearLibTerminal.cmake")
endif()


# -----------------------------------------------------------------------------
# 3. Исходные файлы проекта
# -----------------------------------------------------------------------------
set(PROJECT_HEADERS_DIR "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_SOURCES_DIR "${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE HEADERS "${PROJECT_HEADERS_DIR}/*.h")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCES_DIR}/*.cpp")

# -----------------------------------------------------------------------------
# 4. Создание исполняемого файла
# -----------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

# -----------------------------------------------------------------------------
# 5. Пути к заголовкам
# -----------------------------------------------------------------------------
# Заголовки BearLibTerminal (обычно системные, подавляем предупреждения)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${BLT_INCLUDE_DIRS})

# Собственные заголовки проекта
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_HEADERS_DIR}"
    "${PROJECT_SOURCE_DIR}/include/ecs"
    "${PROJECT_SOURCE_DIR}/include/ecs/components"
    "${PROJECT_SOURCE_DIR}/include/ecs/components/tags"
    "${PROJECT_SOURCE_DIR}/include/ecs/entities"
    "${PROJECT_SOURCE_DIR}/include/ecs/systems"
    "${PROJECT_SOURCE_DIR}/include/enums"
    "${PROJECT_SOURCE_DIR}/include/scenes"
    "${PROJECT_SOURCE_DIR}/include/utils/game"
    "${PROJECT_SOURCE_DIR}/include/utils/math"
    "${PROJECT_SOURCE_DIR}/include/utils/service"
    "${PROJECT_SOURCE_DIR}/include/classes"
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/config"
    "${PROJECT_SOURCE_DIR}/src/symbolica/levels"
)

# -----------------------------------------------------------------------------
# 6. Линковка с библиотекой
# -----------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} ${BLT_LIBRARIES})

# -----------------------------------------------------------------------------
# 7. Копирование .dll в папку сборки
# -----------------------------------------------------------------------------
# Определяем путь к динамической библиотеке отдельно, потому что BLT_LIBRARY указывает на .lib
set(BLT_DLL_PATH "${BearLibTerminal_ROOT}/BearLibTerminal.dll")

if(WIN32)
    set(BLT_LIBRARY_DLL "${BearLibTerminal_ROOT}/BearLibTerminal.dll")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${BLT_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying BearLibTerminal.dll to output directory"
    )
elseif(UNIX)
    set(BLT_LIBRARY_SO "${BearLibTerminal_ROOT}/BearLibTerminal.so")

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${BLT_LIBRARY_SO}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying BearLibTerminal.so to output directory"
    )
    # Также можно установить rpath, чтобы исполняемый файл искал .so рядом с собой
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH "\$ORIGIN"
        BUILD_RPATH "\$ORIGIN"
    )
endif()

# -----------------------------------------------------------------------------
# 8. Линтинг (опционально)
# -----------------------------------------------------------------------------
if(EXISTS "${PROJECT_SOURCE_DIR}/CMake/CppLint.cmake")
    include(CppLint)
    ADD_STYLE_CHECK_TARGET(lint ${PROJECT_NAME} ${PROJECT_HEADERS_DIR} ${PROJECT_SOURCES_DIR})
    # add_dependencies(${PROJECT_NAME} lint)
else()
    message(STATUS "CppLint module not found, lint target disabled")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Symbolica PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
