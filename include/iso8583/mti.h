/**
 * @file
 * @brief     ISO 8583 message type indicator (MTI).
 * @author    王文佑
 * @date      2015.09.15
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_MTI_H_
#define _ISO8583_MTI_H_

#include <stddef.h>
#include "errcode.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ISO 8583 version definition.
 */
enum iso8583_mti_ver_t
{
    ISO8583_MTI_VER_1987            = 0x0000,  ///< ISO 8583-1:1987 version.
    ISO8583_MTI_VER_1993            = 0x1000,  ///< ISO 8583-1:1993 version.
    ISO8583_MTI_VER_2003            = 0x2000,  ///< ISO 8583-1:2003 version.
    ISO8583_MTI_VER_MASK            = 0xF000,  // Internal use.
};

/**
 * @brief ISO 8583 class definition.
 */
enum iso8583_mti_cla_t
{
    ISO8583_MTI_CLA_AUTH            = 0x0100,  ///< Authorization Message.
    ISO8583_MTI_CLA_FINANCIAL       = 0x0200,  ///< Financial Messages.
    ISO8583_MTI_CLA_FILEACT         = 0x0300,  ///< File Actions Message.
    ISO8583_MTI_CLA_REVERSAL        = 0x0400,  ///< Reversal and Charge back Messages.
    ISO8583_MTI_CLA_RECON           = 0x0500,  ///< Reconciliation Message.
    ISO8583_MTI_CLA_ADMIN           = 0x0600,  ///< Administrative Message.
    ISO8583_MTI_CLA_FEE             = 0x0700,  ///< Fee Collection Messages.
    ISO8583_MTI_CLA_NETWORK         = 0x0800,  ///< Network Management Message.
    ISO8583_MTI_CLA_MASK            = 0x0F00,  // Internal use.
};

/**
 * @brief ISO 8583 function definition.
 */
enum iso8583_mti_fun_t
{
    ISO8583_MTI_FUN_REQUEST         = 0x0000,  ///< Request.
    ISO8583_MTI_FUN_RESPONSE        = 0x0010,  ///< Request Response.
    ISO8583_MTI_FUN_ADVICE          = 0x0020,  ///< Advice.
    ISO8583_MTI_FUN_ADV_RESPONSE    = 0x0030,  ///< Advice Response.
    ISO8583_MTI_FUN_NOTI            = 0x0040,  ///< Notification.
    ISO8583_MTI_FUN_NOTI_ACK        = 0x0050,  ///< Notification Acknowledgement.
    ISO8583_MTI_FUN_INST            = 0x0060,  ///< Instruction (ISO 8583:2003 only).
    ISO8583_MTI_FUN_INST_ACK        = 0x0070,  ///< Instruction Acknowledgement (ISO 8583:2003 only).
    ISO8583_MTI_FUN_MASK            = 0x00F0,  // Internal use.
};

/**
 * @brief ISO 8583 origin definition.
 */
enum iso8583_mti_ori_t
{
    ISO8583_MTI_ORI_ACQ             = 0x0000,  ///< Acquirer.
    ISO8583_MTI_ORI_ACQ_REPEAT      = 0x0001,  ///< Acquirer Repeat.
    ISO8583_MTI_ORI_ISSUER          = 0x0002,  ///< Issuer.
    ISO8583_MTI_ORI_ISSUER_REPEAT   = 0x0003,  ///< Issuer Repeat.
    ISO8583_MTI_ORI_OTHER           = 0x0004,  ///< Other.
    ISO8583_MTI_ORI_OTHER_REPEAT    = 0x0005,  ///< Other Repeat.
    ISO8583_MTI_ORI_MASK            = 0x000F,  // Internal use.
};

int iso8583_mti_encode(int  mti, void *buf, size_t size, int flags);
int iso8583_mti_decode(int *mti, const void *data, size_t size, int flags);

static inline
int iso8583_mti_make(int ver, int cla, int fun, int ori)
{
    /**
     * Make a MTI value.
     *
     * @param ver ISO 8583 version value, see ::iso8583_mti_ver_t for more information.
     * @param cla ISO 8583 class value, see ::iso8583_mti_cla_t for more information.
     * @param fun ISO 8583 function value, see ::iso8583_mti_fun_t for more information.
     * @param ori ISO 8583 origin value, see ::iso8583_mti_ori_t for more information.
     * @return The final MTI value.
     */
    return ( ver & ISO8583_MTI_VER_MASK ) |
           ( cla & ISO8583_MTI_CLA_MASK ) |
           ( fun & ISO8583_MTI_FUN_MASK ) |
           ( ori & ISO8583_MTI_ORI_MASK );
}

static inline
int iso8583_mti_get_version(int mti)
{
    /// Get ISO 8583 version value from MTI.
    /// @return ISO 8583 version value, see ::iso8583_mti_ver_t for more information.
    return mti & ISO8583_MTI_VER_MASK;
}

static inline
int iso8583_mti_get_class(int mti)
{
    /// Get ISO 8583 class value from MTI.
    /// @return ISO 8583 class value, see ::iso8583_mti_cla_t for more information.
    return mti & ISO8583_MTI_CLA_MASK;
}

static inline
int iso8583_mti_get_function(int mti)
{
    /// Get ISO 8583 function value from MTI.
    /// @return ISO 8583 function value, see ::iso8583_mti_fun_t for more information.
    return mti & ISO8583_MTI_FUN_MASK;
}

static inline
int iso8583_mti_get_origin(int mti)
{
    /// Get ISO 8583 origin value from MTI.
    /// @return ISO 8583 origin value, see ::iso8583_mti_ori_t for more information.
    return mti & ISO8583_MTI_ORI_MASK;
}

static inline
int iso8583_mti_set_version(int mti, int ver)
{
    /// Set ISO 8583 version value to MTI.
    /// @return The final MTI value.
    return ( mti & ~ISO8583_MTI_VER_MASK ) | ( ver & ISO8583_MTI_VER_MASK );
}

static inline
int iso8583_mti_set_class(int mti, int cla)
{
    /// Set ISO 8583 class value to MTI.
    /// @return The final MTI value.
    return ( mti & ~ISO8583_MTI_CLA_MASK ) | ( cla & ISO8583_MTI_CLA_MASK );
}

static inline
int iso8583_mti_set_function(int mti, int fun)
{
    /// Set ISO 8583 function value to MTI.
    /// @return The final MTI value.
    return ( mti & ~ISO8583_MTI_FUN_MASK ) | ( fun & ISO8583_MTI_FUN_MASK );
}

static inline
int iso8583_mti_set_origin(int mti, int ori)
{
    /// Set ISO 8583 origin value to MTI.
    /// @return The final MTI value.
    return ( mti & ~ISO8583_MTI_ORI_MASK ) | ( ori & ISO8583_MTI_ORI_MASK );
}

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{
/// Message Type Indicator (MTI).
namespace mti
{

inline int Make(int ver, int cla, int fun, int ori) { return iso8583_mti_make(ver, cla, fun, ori); }  ///< @see ::iso8583_mti_make

inline int Encode(int  mti, void *buf, size_t size, int flags)        { return iso8583_mti_encode(mti, buf, size, flags); }    ///< @see ::iso8583_mti_encode
inline int Decode(int &mti, const void *data, size_t size, int flags) { return iso8583_mti_decode(&mti, data, size, flags); }  ///< @see ::iso8583_mti_decode

inline int GetVersion (int mti) { return iso8583_mti_get_version (mti); }  ///< @see ::iso8583_mti_get_version
inline int GetClass   (int mti) { return iso8583_mti_get_class   (mti); }  ///< @see ::iso8583_mti_get_class
inline int GetFunction(int mti) { return iso8583_mti_get_function(mti); }  ///< @see ::iso8583_mti_get_function
inline int GetOrigin  (int mti) { return iso8583_mti_get_origin  (mti); }  ///< @see ::iso8583_mti_get_origin

inline int SetVersion (int mti, int ver) { return iso8583_mti_set_version (mti, ver); }  ///< @see ::iso8583_mti_set_version
inline int SetClass   (int mti, int cla) { return iso8583_mti_set_class   (mti, cla); }  ///< @see ::iso8583_mti_set_class
inline int SetFunction(int mti, int fun) { return iso8583_mti_set_function(mti, fun); }  ///< @see ::iso8583_mti_set_function
inline int SetOrigin  (int mti, int ori) { return iso8583_mti_set_origin  (mti, ori); }  ///< @see ::iso8583_mti_set_origin

}  // namespace mti
}  // namespace ISO8583
#endif  // __cplusplus

#endif
