//
// Created by NOsipov on 11/28/2021.
//

#ifndef ALED_FIXED_STREAM_H
#define ALED_FIXED_STREAM_H

#include "Arduino.h"

#include "pb_common.h"
#include "pb_encode.h"
#include "pb_decode.h"

/**
 * Converts passed Stream to pb_istream_t
 *
 * @param stream a stream to convert
 * @return a converted pb_istream_t
 */
extern pb_istream_t convertStreamToPbIstream(Stream& stream);

#endif //ALED_FIXED_STREAM_H
