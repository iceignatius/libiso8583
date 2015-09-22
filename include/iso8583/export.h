/*
 * ISO 8583 library function export definition.
 *
 * This file copied and modified from "shrdlibdef.h" from "genutil",
 * The following site can be refer for more information:
 * http://www.openfoundry.org/of/projects/2419
 */
#ifndef _ISO8583_EXPORT_H_
#define _ISO8583_EXPORT_H_

// Function import and export.
#if   defined(__linux__) && defined(__GNUC__)
    #define  ISO8583_IMPORT
    #define  ISO8583_EXPORT  __attribute__((visibility("default")))
#elif defined(_WIN32)
    #define  ISO8583_IMPORT  __declspec(dllimport)
    #define  ISO8583_EXPORT  __declspec(dllexport)
#else
    #error No implementation on this platform!
#endif

// Calling convention.
#if   defined(__linux__) && defined(__i386__) && defined(__GNUC__)
    #define  ISO8583_CALL  __attribute__((cdecl))
#elif defined(_WIN32)
    #define  ISO8583_CALL  __stdcall
#else
    #define  ISO8583_CALL
#endif

// Library interface.
#ifdef ISO8583_MAKESHARED
    #define ISO8583_API(type) ISO8583_EXPORT type ISO8583_CALL
#else
    #define ISO8583_API(type) ISO8583_IMPORT type ISO8583_CALL
#endif

#endif
