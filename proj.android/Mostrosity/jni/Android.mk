LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../cocos2d/cocos/platform/android/jni/JniLink.cpp \
                   ../../../cocos2d/cocos/editor-support/spine/Json.h \
                   ../../../Classes/HelloWorldScene.cpp \
                   ../../../Classes/Preguntator.cpp \
                   ../../../Classes/Akuerdate.cpp \
                   ../../../Classes/Dimeketekito.cpp \
                   ../../../Classes/Armame.cpp \
                   ../../../Classes/Configuracion.cpp \
                   ../../../Classes/MiMostro.cpp \
                   ../../../Classes/Ajustes.cpp \
                   ../../../Classes/Mosterland.cpp \
                   ../../../Classes/Splash.cpp \
                   ../../../Classes/CMostro.cpp \
                   ../../../Classes/CProfesionAkuerdate.cpp \
                   ../../../Classes/CPanelArmame.cpp \
                   ../../../Classes/LanguageManager.cpp \
                   ../../../Classes/FileOperation.cpp \
                   ../../../Classes/CPreguntasPreguntator.cpp \
                   ../../../Classes/CGestorRecursos.cpp \
                   ../../../Classes/CTipoRecurso.cpp \
                   ../../../Classes/CRecurso.cpp \
                   ../../../Classes/Acerca.cpp \
                   ../../../Classes/SelectorProfesor.cpp
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../cocos2d/cocos/platform/android/jni

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
 LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
 $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
$(call import-module,network)
$(call import-module,extensions)
