/**
 * @file
 * @brief     ISO 8583 library exchange module.
 * @author    王文佑
 * @date      2016.01.04
 * @copyright ZLib Licence
 * @see       https://www.openfoundry.org/of/projects/2747/
 */
#ifndef _ISO8583_EXCHANGE_H_
#define _ISO8583_EXCHANGE_H_

#include "iso8583.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ISO8583_EXG_BUFSIZE 8192  // Size of the internal data buffer.

/**
 * @brief Send data.
 *
 * @param userarg A user defined argument.
 * @param data    The data to be sent.
 * @param size    Size of the data.
 * @retval Positive Size of data sent.
 * @retval Zero     Currently no data be sent out.
 * @retval Negative Error occurred.
 */
typedef int(*iso8583_on_send_t)(void *userarg, const void *data, size_t size);

/**
 * @brief Receive data.
 *
 * @param userarg A user defined argument.
 * @param buf     A buffer to receive data.
 * @param size    Size of the buffer.
 * @retval Positive Size of data that received.
 * @retval Zero     Currently no data received.
 * @retval Negative Error occurred.
 */
typedef int(*iso8583_on_recv_t)(void *userarg, void *buf, size_t size);

/**
 * @class iso8583_exg_t
 * @brief ISO 8583 message exchange module.
 */
typedef struct iso8583_exg_t
{
    /*
     * WARNING : All members are private.
     */
    int encode_flags;

    void              *userarg;
    iso8583_on_send_t  on_send;
    iso8583_on_recv_t  on_recv;

} iso8583_exg_t;

ISO8583_API(void) iso8583_exg_init(iso8583_exg_t *cfg, int                encode_flags,
                                                       void              *userarg,
                                                       iso8583_on_send_t  on_send,
                                                       iso8583_on_recv_t  on_recv);

ISO8583_API(int) iso8583_exg_send(const iso8583_exg_t *cfg, const iso8583_t *msg, unsigned timeout);
ISO8583_API(int) iso8583_exg_recv(const iso8583_exg_t *cfg, iso8583_t *msg, unsigned timeout);

#ifdef __cplusplus
}  // extern "C"
#endif

#ifdef __cplusplus
/// C++ wrapper.
namespace ISO8583
{

/**
 * @brief C++ wrapper of iso8583_exg_t.
 */
class TExchange : protected iso8583_exg_t
{
public:
    TExchange(int                encode_flags,
              void              *userarg,
              iso8583_on_send_t  on_send,
              iso8583_on_recv_t  on_recv)
    {
        /// @see iso8583_exg_t::iso8583_exg_init
        iso8583_exg_init(this, encode_flags, userarg, on_send, on_recv);
    }

public:
    int Send(const TISO8583 &msg, unsigned timeout) { return iso8583_exg_send(this, &msg, timeout); }  ///< @see iso8583_exg_t::iso8583_exg_send
    int Recv(      TISO8583 &msg, unsigned timeout) { return iso8583_exg_recv(this, &msg, timeout); }  ///< @see iso8583_exg_t::iso8583_exg_recv

};

}  // namespace ISO8583
#endif  // __cplusplus

#endif
