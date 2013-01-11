//
// Created by Simon Schmid
//
// contact@sschmid.com
//


#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import "GIInjectionMapper.h"

@class GIModule;
@class GIInjectorEntryFactory;

#define inject(args...) \
    + (NSSet *)desiredProperties { \
        NSMutableSet *requirements = [NSMutableSet setWithObjects:args, nil]; \
        Class superClass = class_getSuperclass([self class]); \
        if ([superClass respondsToSelector:@selector(desiredProperties)]) { \
            NSSet *parentRequirements = [superClass performSelector:@selector(desiredProperties)]; \
            [requirements unionSet:parentRequirements]; \
        } \
        return requirements; \
    }

#define injection_complete(selectorName) \
    + (NSString *)injectionCompleteSelector { \
        return selectorName; \
    }


@interface GIInjector : NSObject <GIInjectionMapper>

+ (GIInjector *)sharedInjector;

- (id)getObject:(id)keyObject;

- (void)injectIntoObject:(id)object;

- (void)addModule:(GIModule *)module;
- (void)removeModule:(GIModule *)module;
- (void)removeModuleClass:(Class)moduleClass;

- (BOOL)hasModule:(GIModule *)module;
- (BOOL)hasModuleClass:(Class)moduleClass;

- (void)reset;

@end