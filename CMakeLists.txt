cmake_minimum_required(VERSION 3.1)

set(APP_NAME bombman)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
if(NOT USE_COCOS_PREBUILT)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

include_directories(
        Classes
        ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)
# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/HelloWorldScene.cpp

	 Classes/src/ecs/system_manager.cpp
	 Classes/src/ecs/entity_manager.cpp
	 Classes/src/ecs/entity.cpp
	
	 Classes/src/system/move_system.cpp
	 Classes/src/system/controller_system.cpp
	 Classes/src/system/render_system.cpp
	 Classes/src/system/skill_system.cpp
	 Classes/src/system/collision_system.cpp

	 Classes/src/component/moveable.cpp
	 Classes/src/component/transform.cpp
	 Classes/src/component/controller.cpp
	 Classes/src/component/model.cpp
	 Classes/src/component/skill.cpp
	 Classes/src/component/collision.cpp

	 Classes/src/context/game_context.cpp

	 Classes/src/factory/entity_factory.cpp

     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/HelloWorldScene.h

	 Classes/src/ecs/system_manager.h
	 Classes/src/ecs/system.h
	 Classes/src/ecs/entity_manager.h
	 Classes/src/ecs/entity.hpp

	 Classes/src/system/move_system.h
	 Classes/src/system/controller_system.h
	 Classes/src/system/render_system.h
	 Classes/src/system/skill_system.h
	 Classes/src/system/collision_system.h

	 Classes/src/component/moveable.hpp
	 Classes/src/component/transform.hpp
	 Classes/src/component/controller.hpp
	 Classes/src/component/model.hpp
	 Classes/src/component/skill.hpp
	 Classes/src/component/collision.hpp

	 Classes/src/factory/entity_factory.h
	 Classes/src/context/game_context.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(APP_SRC
    ${GAME_SOURCE}
    ${GAME_HEADER}
    )
cocos_build_app(${APP_NAME}
                APP_SRC "${APP_SRC}"
                DEPEND_COMMON_LIBS "cocos2d"
                DEPEND_ANDROID_LIBS "cocos2d_android"
                )

if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RES_DIR})
endif()

if(LINUX OR WINDOWS)
    cocos_copy_res(COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
