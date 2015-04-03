//
//  UNQDatabase.m
//  UnqliteKit
//
//  Created by Maxthon Chan on 4/2/15.
//  Copyright (c) 2015 DreamCity. All rights reserved.
//

#import "UNQDatabase.h"

#import "unqlite.h"

NSString *const UNQDatabaseErrorDomain = @"UNQDatabaseErrorDomain";
NSUInteger const UNQMaximumDataLength = 16 << 20; // 16MB

FOUNDATION_STATIC_INLINE NSError *_UNQMakeError(unqlite *db, int error)
{
    const char *estr;
    int estrl;
    
    unqlite_config(db, UNQLITE_CONFIG_ERR_LOG, &estr, &estrl);
    
    return [NSError errorWithDomain:UNQDatabaseErrorDomain
                               code:error
                           userInfo:@{NSLocalizedDescriptionKey: [[NSString alloc] initWithBytes:estr
                                                                                          length:estrl
                                                                                        encoding:NSUTF8StringEncoding]}];
}

@implementation UNQDatabase
{
    unqlite *_db;
}

- (instancetype)init
{
    return [self initWithURL:nil mode:UNQOpenModeInMemory];
}

- (instancetype)initWithURL:(NSURL *)URL mode:(UNQOpenMode)mode
{
    if (self = [super init])
    {
        if (unqlite_open(&_db, URL ? URL.path.UTF8String : ":mem:", mode | UNQOpenModeNonatomic))
            self = nil;
    }
    return self;
}

- (void)dealloc
{
    unqlite_close(_db);
}

- (NSData *)dataForKey:(NSString *)key error:(NSError **)error
{
    @synchronized (self)
    {
        unqlite_int64 length = 0;
        int rv = 0;
        if ((rv = unqlite_kv_fetch(_db,
                                   key.UTF8String, (int)[key lengthOfBytesUsingEncoding:NSUTF8StringEncoding],
                                   NULL, &length)) == UNQLITE_NOTFOUND)
            return nil;
        if (rv != UNQLITE_OK)
        {
            if (error)
                *error = _UNQMakeError(_db, rv);
            return nil;
        }
        
        NSMutableData *data = [NSMutableData dataWithLength:length];
        if (!data)
            return nil;
        
        rv = unqlite_kv_fetch(_db,
                              key.UTF8String, (int)[key lengthOfBytesUsingEncoding:NSUTF8StringEncoding],
                              data.mutableBytes, &length);
        if (rv != UNQLITE_OK)
        {
            if (error)
                *error = _UNQMakeError(_db, rv);
            return nil;
        }
        
        return data;
    }
}

- (BOOL)setData:(NSData *)data forKey:(NSString *)key error:(NSError *__autoreleasing *)error
{
    @synchronized (self)
    {
        int rv = 0;
        if (data)
        {
            rv = unqlite_kv_store(_db,
                                  key.UTF8String, (int)[key lengthOfBytesUsingEncoding:NSUTF8StringEncoding],
                                  data.bytes, data.length);
            if (rv & ~(UNQLITE_OK | UNQLITE_NOTFOUND))
            {
                if (error)
                    *error = _UNQMakeError(_db, rv);
                return NO;
            }
            return YES;
        }
        else
        {
            rv = unqlite_kv_delete(_db, key.UTF8String, (int)[key lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
            if (rv & ~(UNQLITE_OK | UNQLITE_NOTFOUND))
            {
                if (error)
                    *error = _UNQMakeError(_db, rv);
                return NO;
            }
            return YES;
        }
    }
}

@end

@implementation UNQDatabase (UNQObjectStorage)

- (BOOL)setObject:(id)object forKey:(NSString *)key error:(NSError *__autoreleasing *)error
{
    // Make a data out of an object.
    NSData *archivedData = [NSKeyedArchiver archivedDataWithRootObject:object];
    return [self setData:archivedData forKey:key error:error];
}

- (id)objectForKey:(NSString *)key error:(NSError *__autoreleasing *)error
{
    NSData *archivedData = [self dataForKey:key error:error];
    if (!archivedData)
        return nil;
    
    return [NSKeyedUnarchiver unarchiveObjectWithData:archivedData];
}

- (void)setObject:(id)object forKeyedSubscript:(NSString *)key
{
    [self setObject:object forKey:key error:NULL];
}

- (id)objectForKeyedSubscript:(NSString *)key
{
    return [self objectForKey:key error:NULL];
}

@end
