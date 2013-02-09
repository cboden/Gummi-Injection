//
// Created by Simon Schmid
//
// contact@sschmid.com
//

#import "GIInjectorBlockEntry.h"
#import "GIInjector.h"

@interface GIInjectorBlockEntry ()
@property(nonatomic) BOOL asSingleton;
@property(nonatomic) id singletonCache;
@end

@implementation GIInjectorBlockEntry

- (id)initWithObject:(id)object mappedTo:(id)keyObject asSingleton:(BOOL)singleton injector:(GIInjector *)injector {
    self = [super initWithObject:object mappedTo:keyObject injector:injector];
    if (self) {
        self.asSingleton = singleton;
    }
    
    return self;
}

- (id)extractObject {
    if (self.asSingleton) {
        if (!self.singletonCache) {
            id (^factoryBlock)(GIInjector *) = _object;
            self.singletonCache = factoryBlock(_injector);
            [_injector injectIntoObject:self.singletonCache];

            Block_release((__bridge void*)_object);
            _object = nil;
        }

        return self.singletonCache;
    }

    id (^factoryBlock)(GIInjector *) = _object;
    return factoryBlock(_injector);
}

@end