//
// Created by NOsipov on 11/28/2021.
//

#include "stream.h"

/**
 * Reads PB Stream
 *
 * @param stream a PB stream
 * @param buffer a buffer for reading
 * @param count  a count of bytes to read
 *
 * @return true if all bytes were written or false else
 */
bool readPbStream(pb_istream_t *stream, pb_byte_t* buffer, size_t count) {
    Stream* streamCasted = reinterpret_cast<Stream*>(stream->state);
    size_t written = streamCasted->readBytes(buffer, count);

    return written == count;
};

pb_istream_t convertStreamToPbIstream(Stream& stream) {
    return {
        readPbStream,
        &stream,
        SIZE_MAX,
        nullptr
    };
};
