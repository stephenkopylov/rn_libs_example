#include "RNSampleJSILib.hpp"
#include <string>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <fstream>
#include <sstream>
#elif __ANDROID__

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#endif

#ifdef __ANDROID__

#include <jni.h>
#include <android/log.h>

RNAssetReaderStorage assetReaderStorageInstance;

void RNAssetReaderStorage::init(AAssetManager *cAssetsManager) {
    assetsManager = cAssetsManager;
}

#define TAG "ASSET"
#define printLog(...) __android_log_print(ANDROID_LOG_ERROR,     TAG, __VA_ARGS__)
#else
#define printLog(...) printf(__VA_ARGS__)
#endif

namespace RNSampleJSILib {
    void install(Runtime &jsiRuntime, std::shared_ptr<CallInvoker> callInvoker) {
        auto moduleName = "RNSampleJSILibTurboModule";
        auto nativeModule = std::make_shared<RNSampleJSILibTurboModule>(jsiRuntime, callInvoker);
        auto object = Object::createFromHostObject(jsiRuntime, nativeModule);
        jsiRuntime.global().setProperty(jsiRuntime, moduleName, std::move(object));
    }


    static Value foo(Runtime &rt, TurboModule &turboModule,
                             const Value *args, size_t arg_count){
		std::string arg = args[0].getString(rt).utf8(rt);
		std::string copy(arg);
		std::reverse(copy.begin(), copy.end());
        return String::createFromUtf8(rt, copy);
    }


RNSampleJSILibTurboModule::RNSampleJSILibTurboModule(Runtime &jsiRuntime,
                                                       std::shared_ptr<CallInvoker> jsInvoker)
            : TurboModule("RNSampleJSILibTurboModule", jsInvoker) {
        methodMap_["foo"] = MethodMetadata{0, foo};
    }
}
