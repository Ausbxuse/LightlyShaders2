# CMake generated Testfile for 
# Source directory: /home/peter/.local/src/public-repos/LightlyShaders
# Build directory: /home/peter/.local/src/public-repos/LightlyShaders/qt5build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(appstreamtest "/usr/bin/cmake" "-DAPPSTREAMCLI=/usr/bin/appstreamcli" "-DINSTALL_FILES=/home/peter/.local/src/public-repos/LightlyShaders/qt5build/install_manifest.txt" "-P" "/usr/share/ECM/kde-modules/appstreamtest.cmake")
set_tests_properties(appstreamtest PROPERTIES  _BACKTRACE_TRIPLES "/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;161;add_test;/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;179;appstreamtest;/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;0;;/home/peter/.local/src/public-repos/LightlyShaders/CMakeLists.txt;29;include;/home/peter/.local/src/public-repos/LightlyShaders/CMakeLists.txt;0;")
