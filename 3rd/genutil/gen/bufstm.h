/**
 * @file
 * @brief     Buffer stream
 * @details   Helper tools to make an allocated data buffer be used like a stream,
 *            to help user to read, push, and pop data easier.
 * @author    王文佑
 * @date      2014.09.05
 * @copyright ZLib Licence
 * @see       http://www.openfoundry.org/of/projects/2419
 */
#ifndef _GEN_BUFSTM_H_
#define _GEN_BUFSTM_H_

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inline.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @class bufistm_t
 * @brief Buffer stream - input.
 */
typedef struct bufistm_t
{
    const uint8_t *pos_read;
    size_t         size_rest;
    size_t         size_read;
} bufistm_t;

INLINE void bufistm_init(bufistm_t *stream, const void *buf, size_t size)
{
    /**
     * @memberof bufistm_t
     * @brief Initializer.
     *
     * @param stream Object instance.
     * @param buf    The input buffer that will be used to read data.
     * @param size   Size of the input buffer.
     */
    assert( stream );

    stream->pos_read  = (const uint8_t*) buf;
    stream->size_rest = buf ? size : 0;
    stream->size_read = 0;
}

INLINE const void* bufistm_get_readbuf(const bufistm_t *stream)
{
    /**
     * @memberof bufistm_t
     * @brief Get the current read position.
     *
     * @param stream Object instance.
     * @return A pointer to the current read position.
     *
     * @attention The object will not be responsible about how you use the buffer.
     *            User can read data by their own way,
     *            and then call ::bufistm_read_notify to notify
     *            how many data that you had read.
     */
    assert( stream );
    return stream->pos_read;
}

INLINE size_t bufistm_get_restsize(const bufistm_t *stream)
{
    /**
     * @memberof bufistm_t
     * @brief Get the size unread.
     *
     * @param stream Object instance.
     * @return The size of data unread.
     */
    assert( stream );
    return stream->size_rest;
}

INLINE size_t bufistm_get_readsize(const bufistm_t *stream)
{
    /**
     * @memberof bufistm_t
     * @brief Get the size that has been read.
     *
     * @param stream Object instance.
     * @return The size of data that has been read.
     */
    assert( stream );
    return stream->size_read;
}

INLINE bool bufistm_read(bufistm_t *stream, void *buf, size_t size)
{
    /**
     * @memberof bufistm_t
     * @brief Read data.
     *
     * @param stream Object instance.
     * @param buf    A buffer to receive data.
     * @param size   Size of data to read.
     * @return TRUE if succeed; and FALSE if not.
     */
    assert( stream );

    if( !buf ) return false;
    if( size > stream->size_rest ) return false;

    memcpy(buf, stream->pos_read, size);
    stream->pos_read  += size;
    stream->size_rest -= size;
    stream->size_read += size;

    return true;
}

INLINE bool bufistm_read_notify(bufistm_t *stream, size_t size)
{
    /**
     * @memberof bufistm_t
     * @brief   Notify data read.
     * @details Notify the object that we already read some data from the read buffer directly.
     *
     * @param stream Object instance.
     * @param size   The size that has read.
     * @return TRUE if succeed; and FALSE if not.
     */
    assert( stream );

    if( size > stream->size_rest ) return false;

    stream->pos_read  += size;
    stream->size_rest -= size;
    stream->size_read += size;

    return true;
}

INLINE bool bufistm_skip(bufistm_t *stream, size_t size)
{
    /**
     * @memberof bufistm_t
     * @brief Skip some data.
     *
     * @param stream Object instance.
     * @param size   The size that want to be skipped from the current read position.
     * @return TRUE if succeed; and FALSE if not.
     */
    return bufistm_read_notify(stream, size);
}


/**
 * @class bufostm_t
 * @brief Buffer stream - output.
 */
typedef struct bufostm_t
{
    uint8_t *pos_write;
    size_t   size_rest;
    size_t   size_write;
} bufostm_t;

INLINE void bufostm_init(bufostm_t *stream, void *buf, size_t size)
{
    /**
     * @memberof bufostm_t
     * @brief Initializer.
     *
     * @param stream Object instance.
     * @param buf    The data output buffer.
     * @param size   Size of the output buffer.
     */
    assert( stream );

    stream->pos_write  = (uint8_t*) buf;
    stream->size_rest  = buf ? size : 0;
    stream->size_write = 0;
}

INLINE void* bufostm_get_writebuf(bufostm_t *stream)
{
    /**
     * @memberof bufostm_t
     * @brief Get the current write position.
     *
     * @param stream Object instance.
     * @return A pointer to the current write position.
     *
     * @attention The object will not be responsible about how you use the buffer.
     *            User can write data by their own way,
     *            and then call ::bufostm_write_notify to notify
     *            how many data that you had wrote.
     */
    assert( stream );
    return stream->pos_write;
}

INLINE size_t bufostm_get_restsize(const bufostm_t *stream)
{
    /**
     * @memberof bufostm_t
     * @brief Get rest size of the output buffer that we can write data.
     *
     * @param stream Object instance.
     * @return Size rest of the output buffer.
     */
    assert( stream );
    return stream->size_rest;
}

INLINE size_t bufostm_get_datasize(const bufostm_t *stream)
{
    /**
     * @memberof bufostm_t
     * @brief Get total data size of the output buffer.
     *
     * @param stream Object instance.
     * @return Total size of the output buffer.
     */
    assert( stream );
    return stream->size_write;
}

INLINE bool bufostm_write(bufostm_t *stream, const void *data, size_t size)
{
    /**
     * @memberof bufostm_t
     * @brief Write data.
     *
     * @param stream Object instance.
     * @param data   Data to write.
     * @param size   Size of data to write.
     * @return TRUE if succeed; and FALSE if not.
     */
    assert( stream );

    if( !data ) return false;
    if( size > stream->size_rest ) return false;

    memcpy(stream->pos_write, data, size);
    stream->pos_write  += size;
    stream->size_rest  -= size;
    stream->size_write += size;

    return true;
}

INLINE bool bufostm_write_notify(bufostm_t *stream, size_t size)
{
    /**
     * @memberof bufostm_t
     * @brief   Notify data read.
     * @details Notify the object that we already wrote some data to the write buffer directly
     *
     * @param stream Object instance.
     * @param size   The size that has wrote.
     * @return TRUE if succeed; and FALSE if not.
     */
    assert( stream );

    if( size > stream->size_rest ) return false;

    stream->pos_write  += size;
    stream->size_rest  -= size;
    stream->size_write += size;

    return true;
}

INLINE bool bufostm_putbyte(bufostm_t *stream, uint8_t byte)
{
    /**
     * @memberof bufostm_t
     * @brief Write a single byte of data.
     *
     * @param stream Object instance.
     * @param byte   The byte data to write.
     * @return TRUE if succeed; and FALSE if not.
     */
    assert( stream );

    if( !stream->size_rest ) return false;

    *stream->pos_write++ = byte;
    -- stream->size_rest;
    ++ stream->size_write;

    return true;
}

#ifdef __cplusplus
}  // extern "C"
#endif

#endif
