#include <assert.h>
#include <gen/bcd.h>
#include <gen/timeinf.h>
#include "mti.h"
#include "finfo.h"
#include "helper.h"

//------------------------------------------------------------------------------
static
int mti_get_corresponding_fun(int mti)
{
    switch( iso8583_mti_get_function(mti) )
    {
    case ISO8583_MTI_FUN_REQUEST      :  return ISO8583_MTI_FUN_RESPONSE;
    case ISO8583_MTI_FUN_RESPONSE     :  return ISO8583_MTI_FUN_REQUEST;
    case ISO8583_MTI_FUN_ADVICE       :  return ISO8583_MTI_FUN_ADV_RESPONSE;
    case ISO8583_MTI_FUN_ADV_RESPONSE :  return ISO8583_MTI_FUN_ADVICE;
    case ISO8583_MTI_FUN_NOTI         :  return ISO8583_MTI_FUN_NOTI_ACK;
    case ISO8583_MTI_FUN_NOTI_ACK     :  return ISO8583_MTI_FUN_NOTI;
    case ISO8583_MTI_FUN_INST         :  return ISO8583_MTI_FUN_INST_ACK;
    case ISO8583_MTI_FUN_INST_ACK     :  return ISO8583_MTI_FUN_INST;
    }

    return -1;
}
//------------------------------------------------------------------------------
static
int mti_get_corresponding_ori_from_resp(int mti)
{
    switch( iso8583_mti_get_origin(mti) )
    {
    case ISO8583_MTI_ORI_ACQ           :  return ISO8583_MTI_ORI_ACQ;
    case ISO8583_MTI_ORI_ACQ_REPEAT    :  return ISO8583_MTI_ORI_ACQ;
    case ISO8583_MTI_ORI_ISSUER        :  return ISO8583_MTI_ORI_ISSUER;
    case ISO8583_MTI_ORI_ISSUER_REPEAT :  return ISO8583_MTI_ORI_ISSUER;
    case ISO8583_MTI_ORI_OTHER         :  return ISO8583_MTI_ORI_OTHER;
    case ISO8583_MTI_ORI_OTHER_REPEAT  :  return ISO8583_MTI_ORI_OTHER;
    }

    return -1;
}
//------------------------------------------------------------------------------
bool ISO8583_CALL iso8583_helper_check_mti(int resp, int req)
{
    /**
     * Check MTI value of a response message.
     *
     * @param resp MTI of the response message.
     * @param req  MTI of the request message.
     * @return TRUE if check passed; and FALSE if not.
     */
    return ( iso8583_mti_get_version(resp)             == iso8583_mti_get_version(req)  ) &&
           ( iso8583_mti_get_class(resp)               == iso8583_mti_get_class(req)    ) &&
           ( mti_get_corresponding_fun(resp)           == iso8583_mti_get_function(req) ) &&
           ( mti_get_corresponding_ori_from_resp(resp) == iso8583_mti_get_origin(req)   );
}
//------------------------------------------------------------------------------
ISO8583_API(bool) iso8583_helper_set_bin(iso8583_fields_t *fields, int id, const void *data, size_t size)
{
    /**
     * Set binary data to field item.
     *
     * @param fields The field item container to be operated.
     * @param id     A field ID to set field value.
     * @param data   The data to set to the field item.
     * @param size   Size of data to set.
     * @return TRUE if succeed; and FALSE if failed.
     */
    assert( fields );

    if( !data || !size ) return false;
    if( id < ISO8583_FITEM_ID_MIN || ISO8583_FITEM_ID_MAX < id ) return false;

    iso8583_fitem_t item;
    iso8583_fitem_init_value(&item, id, data, size);

    bool res = !iso8583_fields_insert(fields, &item);

    iso8583_fitem_deinit(&item);

    return res;
}
//------------------------------------------------------------------------------
uint64_t ISO8583_CALL iso8583_helper_get_int(const iso8583_fields_t *fields, int id, uint64_t errval)
{
    /**
     * Get integer value from field item.
     *
     * @param fields The field item container to be operated.
     * @param id     A field ID to get field value.
     * @param errval Assign a value that will be returned when the field cannot be read.
     * @return The integer value read from the specific field item; or
     *         @a errval if read failed.
     */
    assert( fields );

    const iso8583_fitem_t *item = iso8583_fields_get_item(fields, id);
    if( !item ) return errval;

    const uint8_t *data = iso8583_fitem_get_data(item);
    size_t         size = iso8583_fitem_get_size(item);
    if( !data || !size ) return errval;

    return bcd_decode(data, size);
}
//------------------------------------------------------------------------------
bool ISO8583_CALL iso8583_helper_set_int(iso8583_fields_t *fields, int id, uint64_t value)
{
    /**
     * Set integer value to field item.
     *
     * @param fields The field item container to be operated.
     * @param id     A field ID to set field value.
     * @param value  A value to set to the field item.
     * @return TRUE if succeed; and FALSE if failed.
     */
    assert( fields );

    if( id < ISO8583_FITEM_ID_MIN || ISO8583_FITEM_ID_MAX < id ) return false;
    const finfo_t *finfo = &finfo_list[id];

    int size = ( finfo->maxcount + 1 ) >> 1;
    uint8_t data[size];
    bcd_encode(data, size, value);

    iso8583_fitem_t item;
    iso8583_fitem_init_value(&item, id, data, size);

    bool res = !iso8583_fields_insert(fields, &item);

    iso8583_fitem_deinit(&item);

    return res;
}
//------------------------------------------------------------------------------
char* ISO8583_CALL iso8583_helper_get_str(const iso8583_fields_t *fields, int id, char *buf, size_t bufsz)
{
    /**
     * Get string value from field item.
     *
     * @param fields The field item container to be operated.
     * @param id     A field ID to get field value.
     * @param buf    A buffer to receive the result.
     * @param bufsz  Size of the output buffer.
     * @return The output buffer.
     *
     * @remarks The result string will be an empty string if data read failed,
     *          such like the field item does not existed, or
     *          the output buffer is too small to hold all data.
     */
    assert( fields );

    if( !buf || !bufsz ) return buf;
    memset(buf, 0, bufsz);

    const iso8583_fitem_t *item = iso8583_fields_get_item(fields, id);
    if( !item ) return buf;

    const char *data = iso8583_fitem_get_data(item);
    size_t      size = iso8583_fitem_get_size(item);
    if( !data || !size ) return buf;
    if( bufsz <= size ) return buf;

    strncpy(buf, data, size);
    return buf;
}
//------------------------------------------------------------------------------
bool ISO8583_CALL iso8583_helper_set_str(iso8583_fields_t *fields, int id, const char *str)
{
    /**
     * Set string value to field item.
     *
     * @param fields The field item container to be operated.
     * @param id     A field ID to set field value.
     * @param str    The string to set to the field item.
     * @return TRUE if succeed; and FALSE if failed.
     */
    assert( fields );

    if( !str ) return false;

    if( id < ISO8583_FITEM_ID_MIN || ISO8583_FITEM_ID_MAX < id ) return false;
    const finfo_t *finfo = &finfo_list[id];

    char   data[finfo->maxcount];
    size_t size = strlen(str);
    if( size > sizeof(data) ) return false;

    memcpy(data, str, size);

    iso8583_fitem_t item;
    iso8583_fitem_init_value(&item, id, data, size);

    bool res = !iso8583_fields_insert(fields, &item);

    iso8583_fitem_deinit(&item);

    return res;
}
//------------------------------------------------------------------------------
unsigned ISO8583_CALL iso8583_helper_get_proccode(const iso8583_fields_t *fields)
{
    /**
     * Get processing code.
     *
     * @return The processing code in field items;
     *         or ZERO if not found.
     */
    assert( fields );
    return iso8583_helper_get_int(fields, 3, 0);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_helper_set_proccode(iso8583_fields_t *fields, unsigned proccode)
{
    /**
     * Set processing code.
     */
    assert( fields );
    iso8583_helper_set_int(fields, 3, proccode%1000000);
}
//------------------------------------------------------------------------------
unsigned ISO8583_CALL iso8583_helper_get_stan(const iso8583_fields_t *fields)
{
    /**
     * Get System Trace Audit Number (STAN).

     * @return The STAN value in field items;
     *         or ZERO if not found.
     */
    assert( fields );
    return iso8583_helper_get_int(fields, 11, 0);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_helper_set_stan(iso8583_fields_t *fields, unsigned stan)
{
    /**
     * Set System Trace Audit Number (STAN).
     */
    assert( fields );
    iso8583_helper_set_int(fields, 11, stan);
}
//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_helper_set_local_datetime(iso8583_fields_t *fields, long long uxtime)
{
    /**
     * Set local time.
     *
     * @param fields The field item container to be operated.
     * @param uxtime The time to set in UNIX time stamp format.
     */
    assert( fields );

    #pragma pack(push,1)
    struct bcddate_t
    {
        uint8_t month[1];
        uint8_t day  [1];
    } bcddate;
    #pragma pack(pop)

    #pragma pack(push,1)
    struct bcdtime_t
    {
        uint8_t hour  [1];
        uint8_t minute[1];
        uint8_t second[1];
    } bcdtime;
    #pragma pack(pop)

    timeinf_t timeinf = timeinf_from_uxtime(uxtime);
    bcd_encode(bcddate.month , sizeof(bcddate.month ), timeinf.month );
    bcd_encode(bcddate.day   , sizeof(bcddate.day   ), timeinf.day   );
    bcd_encode(bcdtime.hour  , sizeof(bcdtime.hour  ), timeinf.hour  );
    bcd_encode(bcdtime.minute, sizeof(bcdtime.minute), timeinf.minute);
    bcd_encode(bcdtime.second, sizeof(bcdtime.second), timeinf.second);

    iso8583_fitem_t item;
    iso8583_fitem_init(&item);

    iso8583_fitem_set_id(&item, 12);
    iso8583_fitem_set_data(&item, &bcdtime, sizeof(bcdtime));
    iso8583_fields_insert(fields, &item);

    iso8583_fitem_set_id(&item, 13);
    iso8583_fitem_set_data(&item, &bcddate, sizeof(bcddate));
    iso8583_fields_insert(fields, &item);

    iso8583_fitem_deinit(&item);
}
//------------------------------------------------------------------------------
char* ISO8583_CALL iso8583_helper_get_respcode(const iso8583_fields_t *fields, char respcode[2+1])
{
    /**
     * Get response code.
     *
     * @param fields   The field item container to be operated.
     * @param respcode A buffer to receive the result in null-terminated string format;
     *                 and it will get an empty string if the value not found.
     * @return The output buffer.
     */
    assert( fields && respcode );
    return iso8583_helper_get_str(fields, 39, respcode, 2+1);
}
//------------------------------------------------------------------------------
bool ISO8583_CALL iso8583_helper_set_respcode(iso8583_fields_t *fields, const char *respcode)
{
    /**
     * Set response code.
     */
    assert( fields && respcode );
    return iso8583_helper_set_str(fields, 39, respcode);
}
//------------------------------------------------------------------------------
char* ISO8583_CALL iso8583_helper_get_terminal_id(const iso8583_fields_t *fields, char id[8+1])
{
    /**
     * Get terminal ID.
     *
     * @param fields The field item container to be operated.
     * @param id     A buffer to receive the result in null-terminated string format;
     *               and it will get an empty string if the value not found.
     * @return The output buffer.
     */
    assert( fields && id );
    return iso8583_helper_get_str(fields, 41, id, 8+1);
}
//------------------------------------------------------------------------------
bool ISO8583_CALL iso8583_helper_set_terminal_id(iso8583_fields_t *fields, const char *id)
{
    /**
     * Set terminal ID.
     */
    assert( fields && id );
    return iso8583_helper_set_str(fields, 41, id);
}
//------------------------------------------------------------------------------
char* ISO8583_CALL iso8583_helper_get_merchant_id(const iso8583_fields_t *fields, char id[15+1])
{
    /**
     * Get merchant ID.
     *
     * @param fields The field item container to be operated.
     * @param id     A buffer to receive the result in null-terminated string format;
     *               and it will get an empty string if the value not found.
     * @return The output buffer.
     */
    assert( fields && id );
    return iso8583_helper_get_str(fields, 42, id, 15+1);
}
//------------------------------------------------------------------------------
bool ISO8583_CALL iso8583_helper_set_merchant_id(iso8583_fields_t *fields, const char *id)
{
    /**
     * Set merchant ID.
     */
    assert( fields && id );
    return iso8583_helper_set_str(fields, 42, id);
}
//------------------------------------------------------------------------------
