//
//  RNImageFetcherView.m
//  appcenter
//

#import "RNSampleJSILibObjC.h"
#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <ReactCommon/CallInvoker.h>
#import "RCTTurboModule.h"
#import <ReactCommon/RCTTurboModule.h>
#import "RNSampleJSILib.hpp"

@interface RNSampleJSILibObjC()
@end

@implementation RNSampleJSILibObjC

RCT_EXPORT_MODULE();

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(installTurboModule)
{
	[self installLibrary];
	return NULL;
}

+(BOOL)requiresMainQueueSetup{
	return YES;
}

- (NSArray<NSString *> *)supportedEvents
{
	return @[];
}

- (void)installLibrary {
	RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
	
	if (cxxBridge.runtime) {
		RNSampleJSILib::install(*(facebook::jsi::Runtime *)cxxBridge.runtime, cxxBridge.jsCallInvoker);
	}else{
		dispatch_after(100, dispatch_get_main_queue(), ^{
			[self installLibrary];
		});
	}
}

@end
