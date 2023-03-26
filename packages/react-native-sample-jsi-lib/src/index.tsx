import {NativeModules} from 'react-native';

// @ts-ignore
if (global.RNSampleJSILibTurboModule === undefined) {
    NativeModules.RNSampleJSILibObjC.installTurboModule();
}

export class RNSampleJSILib {
    static foo(arg: string): any {
        // @ts-ignore
        return global.RNSampleJSILibTurboModule.foo(arg);
    }
}
