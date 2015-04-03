//
//  unqlite_config.h
//  UnqliteKit
//
//  Created by Maxthon Chan on 4/2/15.
//  Copyright (c) 2015 DreamCity. All rights reserved.
//

/*
 * ------------------------------
 * Compile time directives
 * ------------------------------
 * For most purposes, UnQLite can be built just fine using the default compilation options.
 * However, if required, the compile-time options documented below can be used to omit UnQLite
 * features (resulting in a smaller compiled library size) or to change the default values
 * of some parameters.
 * Every effort has been made to ensure that the various combinations of compilation options
 * work harmoniously and produce a working library.
 *
 * UNQLITE_ENABLE_THREADS
 *  This option controls whether or not code is included in UnQLite to enable it to operate
 *  safely in a multithreaded environment. The default is not. All mutexing code is omitted
 *  and it is unsafe to use UnQLite in a multithreaded program. When compiled with the
 *  UNQLITE_ENABLE_THREADS directive enabled, UnQLite can be used in a multithreaded program
 *  and it is safe to share the same virtual machine and engine handle between two or more threads.
 *  The value of UNQLITE_ENABLE_THREADS can be determined at run-time using the unqlite_lib_is_threadsafe()
 *  interface.
 *  When UnQLite has been compiled with threading support then the threading mode can be altered
 * at run-time using the unqlite_lib_config() interface together with one of these verbs:
 *    UNQLITE_LIB_CONFIG_THREAD_LEVEL_SINGLE
 *    UNQLITE_LIB_CONFIG_THREAD_LEVEL_MULTI
 *  Platforms others than Windows and UNIX systems must install their own mutex subsystem via
 *  unqlite_lib_config() with a configuration verb set to UNQLITE_LIB_CONFIG_USER_MUTEX.
 *  Otherwise the library is not threadsafe.
 *  Note that you must link UnQLite with the POSIX threads library under UNIX systems (i.e: -lpthread).
 *
 * Options To Omit/Enable Features
 *
 * The following options can be used to reduce the size of the compiled library by omitting optional
 * features. This is probably only useful in embedded systems where space is especially tight, as even
 * with all features included the UnQLite library is relatively small. Don't forget to tell your
 * compiler to optimize for binary size! (the -Os option if using GCC). Telling your compiler
 * to optimize for size usually has a much larger impact on library footprint than employing
 * any of these compile-time options.
 *
 * JX9_DISABLE_BUILTIN_FUNC
 *  Jx9 is shipped with more than 312 built-in functions suitable for most purposes like
 *  string and INI processing, ZIP extracting, Base64 encoding/decoding, JSON encoding/decoding
 *  and so forth.
 *  If this directive is enabled, then all built-in Jx9 functions are omitted from the build.
 *  Note that special functions such as db_create(), db_store(), db_fetch(), etc. are not omitted
 *  from the build and are not affected by this directive.
 *
 * JX9_ENABLE_MATH_FUNC
 *  If this directive is enabled, built-in math functions such as sqrt(), abs(), log(), ceil(), etc.
 *  are included in the build. Note that you may need to link UnQLite with the math library in same
 *  Linux/BSD flavor (i.e: -lm).
 *
 * JX9_DISABLE_DISK_IO
 *  If this directive is enabled, built-in VFS functions such as chdir(), mkdir(), chroot(), unlink(),
 *  sleep(), etc. are omitted from the build.
 *
 * UNQLITE_ENABLE_JX9_HASH_IO
 * If this directive is enabled, built-in hash functions such as md5(), sha1(), md5_file(), crc32(), etc.
 * are included in the build.
 */

#define UNQLITE_ENABLE_THREADS
#define JX9_ENABLE_MATH_FUNC
#define JX9_DISABLE_DISK_IO
#define UNQLITE_ENABLE_JX9_HASH_IO

