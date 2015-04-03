//
//  UNQDatabase.h
//  UnqliteKit
//
//  Created by Maxthon Chan on 4/2/15.
//  Copyright (c) 2015 DreamCity. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_OPTIONS(NSUInteger, UNQOpenMode)
{
    UNOQpenModeReadOnly = 1 << 0,
    UNQOpenModeReadWrite = 1 << 1,
    UNQOpenModeCreate = 1 << 2,
    UNQOpenModeExclusive = 1 << 3,
    UNQOpenModeTemporary = 1 << 4,
    UNQOpenModeNonatomic = 1 << 5,
    UNQOpenModeUnjourneled = 1 << 6,
    UNQOpenModeInMemory = 1 << 7,
    UNQOpenModeMemoryMap = 1 << 8,
};

FOUNDATION_EXPORT NSString *const UNQDatabaseErrorDomain;
FOUNDATION_EXPORT NSUInteger const UNQMaximumDataLength;

@interface UNQDatabase : NSObject

- (instancetype)init;
- (instancetype)initWithURL:(NSURL *)URL mode:(UNQOpenMode)mode NS_DESIGNATED_INITIALIZER;

- (NSData *)dataForKey:(NSString *)key error:(NSError **)error;
- (BOOL)setData:(NSData *)data forKey:(NSString *)key error:(NSError **)error;

@end

@interface UNQDatabase (UNQObjectStorage)

- (id)objectForKey:(NSString *)key error:(NSError **)error;
- (BOOL)setObject:(id)object forKey:(NSString *)key error:(NSError **)error;

- (id)objectForKeyedSubscript:(NSString *)key;
- (void)setObject:(id)object forKeyedSubscript:(NSString *)key;

@end
