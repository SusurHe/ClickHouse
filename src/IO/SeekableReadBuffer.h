#pragma once

#include <IO/ReadBuffer.h>

namespace DB
{

class SeekableReadBuffer : public ReadBuffer
{
public:
    SeekableReadBuffer(Position ptr, size_t size)
        : ReadBuffer(ptr, size) {}
    SeekableReadBuffer(Position ptr, size_t size, size_t offset)
        : ReadBuffer(ptr, size, offset) {}

    /**
     * Shifts buffer current position to given offset.
     * @param off Offset.
     * @param whence Seek mode (@see SEEK_SET, @see SEEK_CUR).
     * @return New position from the beginning of underlying buffer / file.
     */
    virtual off_t seek(off_t off, int whence) = 0;

    /**
     * Keep in mind that seekable buffer may encounter eof() once and the working buffer
     * may get into inconsistent state. Don't forget to reset it on the first nextImpl()
     * after seek().
     */

    /**
     * @return Offset from the begin of the underlying buffer / file corresponds to the buffer current position.
     */
    virtual off_t getPosition() = 0;
};

using SeekableReadBufferPtr = std::shared_ptr<SeekableReadBuffer>;
}
