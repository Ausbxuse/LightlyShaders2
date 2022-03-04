# Install script for directory: /home/peter/.local/src/public-repos/LightlyShaders

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xkwin4_effect_lightlyshadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/plugins/kwin4_effect_lightlyshaders.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/plugins/kwin4_effect_lightlyshaders.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/plugins/kwin4_effect_lightlyshaders.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/qt/plugins/kwin/effects/plugins/kwin4_effect_lightlyshaders.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/qt/plugins/kwin/effects/plugins" TYPE MODULE FILES "/home/peter/.local/src/public-repos/LightlyShaders/qt5build/kwin4_effect_lightlyshaders.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/plugins/kwin4_effect_lightlyshaders.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/plugins/kwin4_effect_lightlyshaders.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/plugins/kwin4_effect_lightlyshaders.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xkwin4_effect_lightlyshadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kwin/shaders/1.40/lightlyshaders.frag")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/kwin/shaders/1.40" TYPE FILE FILES "/home/peter/.local/src/public-repos/LightlyShaders/shaders_140/lightlyshaders.frag")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xkwin4_effect_lightlyshadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kwin/shaders/1.40/lightlyshaders_diff.frag")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/kwin/shaders/1.40" TYPE FILE FILES "/home/peter/.local/src/public-repos/LightlyShaders/shaders_140/lightlyshaders_diff.frag")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xkwin4_effect_lightlyshadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kwin/shaders/1.10/lightlyshaders.frag")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/kwin/shaders/1.10" TYPE FILE FILES "/home/peter/.local/src/public-repos/LightlyShaders/shaders_110/lightlyshaders.frag")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xkwin4_effect_lightlyshadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/kwin/shaders/1.10/lightlyshaders_diff.frag")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/kwin/shaders/1.10" TYPE FILE FILES "/home/peter/.local/src/public-repos/LightlyShaders/shaders_110/lightlyshaders_diff.frag")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xkwin4_effect_lightlyshadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/configs/kwin4_lightlyshaders_config.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/configs/kwin4_lightlyshaders_config.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/configs/kwin4_lightlyshaders_config.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/qt/plugins/kwin/effects/configs/kwin4_lightlyshaders_config.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/qt/plugins/kwin/effects/configs" TYPE MODULE FILES "/home/peter/.local/src/public-repos/LightlyShaders/qt5build/kwin4_lightlyshaders_config.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/configs/kwin4_lightlyshaders_config.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/configs/kwin4_lightlyshaders_config.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/qt/plugins/kwin/effects/configs/kwin4_lightlyshaders_config.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xkwin4_effect_lightlyshadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/kservices5/kwin" TYPE FILE FILES "/home/peter/.local/src/public-repos/LightlyShaders/lightlyshaders_config.desktop")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/peter/.local/src/public-repos/LightlyShaders/qt5build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
