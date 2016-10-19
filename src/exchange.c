#include <assert.h>
#include <stdint.h>
#include <gen/systime.h>
#include <gen/timectr.h>
#include "exchange.h"

//------------------------------------------------------------------------------
void ISO8583_CALL iso8583_exg_init(iso8583_exg_t *cfg, int                encode_flags,
                                                       void              *userarg,
                                                       iso8583_on_send_t  on_send,
                                                       iso8583_on_recv_t  on_recv)
{
    /**
     * @memberof iso8583_exg_t
     * @brief
     *
     * @param cfg          Object instance.
     * @param encode_flags Encoding flags.
     * @param userarg      A user defined argument that will be passed to
     *                     the send and receive callbacks.
     * @param on_send      A callback function that will be called to send data,
     * @param on_recv      A callback function that will be called to receive data,
     *
     * @remarks The size header flag ::ISO8583_FLAG_HAVE_SIZEHDR will be added by force,
     *          no matter what @a encode_flags is.
     * @see ::iso8583_on_send_t, ::iso8583_on_recv_t.
     */
    assert( cfg );

    cfg->encode_flags = encode_flags | ISO8583_FLAG_HAVE_SIZEHDR;
    cfg->userarg      = userarg;
    cfg->on_send      = on_send;
    cfg->on_recv      = on_recv;
}
//------------------------------------------------------------------------------
static
int send_bin(const iso8583_exg_t *cfg, timectr_t *timer, const uint8_t *data, size_t size)
{
    assert( cfg && cfg->on_send && timer && data && size );

    while( size && !timectr_is_expired(timer) )
    {
        int sentsz = cfg->on_send(cfg->userarg, data, size);
        if( sentsz < 0 || size < sentsz ) return ISO8583_ERR_STREAM_FAILED;

        if( sentsz )
        {
            data += sentsz;
            size -= sentsz;
        }
        else
        {
            systime_sleep_awhile();
        }
    }

    return size ? ISO8583_ERR_TIMEOUT : ISO8583_ERR_SUCCESS;
}
//------------------------------------------------------------------------------
static
int recv_bin(const iso8583_exg_t *cfg, timectr_t *timer, uint8_t *buf, size_t size)
{
    assert( cfg && cfg->on_recv && timer && buf && size );

    while( size && !timectr_is_expired(timer) )
    {
        int recvsz = cfg->on_recv(cfg->userarg, buf, size);
        if( recvsz < 0 || size < recvsz ) return ISO8583_ERR_STREAM_FAILED;

        if( recvsz )
        {
            buf  += recvsz;
            size -= recvsz;
        }
        else
        {
            systime_sleep_awhile();
        }
    }

    return size ? ISO8583_ERR_TIMEOUT : ISO8583_ERR_SUCCESS;
}
//------------------------------------------------------------------------------
int ISO8583_CALL iso8583_exg_send(const iso8583_exg_t *cfg, const iso8583_t *msg, unsigned timeout)
{
    /**
     * @memberof iso8583_exg_t
     * @brief
     *
     * @param cfg     Object instance.
     * @param msg     The message to be sent.
     * @param timeout Time out in milliseconds to send message.
     * @return One of the result codes defined in ::iso8583_err_t.
     */
    assert( cfg );

    if( !cfg->on_send || !msg ) return ISO8583_ERR_INVALID_ARG;

    uint8_t buf[ISO8583_EXG_BUFSIZE];
    int size = iso8583_encode(msg, buf, sizeof(buf), cfg->encode_flags);
    if( size < 0 ) return size;

    timectr_t timer;
    timectr_init(&timer, timeout);
    return send_bin(cfg, &timer, buf, size);
}
//------------------------------------------------------------------------------
int ISO8583_CALL iso8583_exg_recv(const iso8583_exg_t *cfg, iso8583_t *msg, unsigned timeout)
{
    /**
     * @memberof iso8583_exg_t
     * @brief
     *
     * @param cfg     Object instance.
     * @param msg     The received message.
     * @param timeout Time out in milliseconds to receive message.
     * @return One of the result codes defined in ::iso8583_err_t.
     */
    assert( cfg );

    if( !cfg->on_recv || !msg ) return ISO8583_ERR_INVALID_ARG;

    timectr_t timer;
    timectr_init(&timer, timeout);

    uint8_t buf[ISO8583_EXG_BUFSIZE];
    int errcode;

    // Receive size header.
    static const size_t header_size = 2;
    if(( errcode = recv_bin(cfg, &timer, buf, header_size) )) return errcode;

    // Calculate size.
    size_t payload_size = ( buf[0] << 8 ) | buf[1];
    size_t packet_size = header_size + payload_size;
    if( packet_size > ISO8583_EXG_BUFSIZE ) return ISO8583_ERR_BUF_NOT_ENOUGH;

    // Receive the rest data.
    if(( errcode = recv_bin(cfg, &timer, buf+header_size, payload_size) )) return errcode;

    // Decode message.
    int readsz = iso8583_decode(msg, buf, packet_size, cfg->encode_flags);
    if( readsz < 0 ) return readsz;

    return ISO8583_ERR_SUCCESS;
}
//------------------------------------------------------------------------------
