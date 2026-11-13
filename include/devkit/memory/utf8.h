#ifndef VASALL_DEVKIT_UTF8_H
#define VASALL_DEVKIT_UTF8_H

#include <devkit/scope.h>
#include <devkit/types.h>

/******************************************************************************
 *
 * 				 DEFINES/MACROS
 *
 ******************************************************************************/

/* The maximum number of bytes a single UTF-8 encoded codepoint can take */
#define UTF8_MAX_BYTES 4

/******************************************************************************
 *
 * 				PUBLIC INTERFACE
 *
 ******************************************************************************/

/**
 * Functions to work with UTF-8 data in any char buffer. For a growable text
 * that always holds valid UTF-8, see devkit/memory/text.h.
 */

/**
 * Decode the codepoint at the start of the buffer. Overlong encodings,
 * surrogates and codepoints above U+10FFFF are rejected.
 *
 * @param buf The UTF-8 data
 * @param len The number of bytes available in buf
 * @param cp_out Receives the codepoint (may be NULL)
 *
 * @returns The number of bytes the codepoint takes, or -1 if the data is not
 *          valid UTF-8
 */
PUB s32 utf8_decode(const char *buf, s32 len, u32 *cp_out);

/**
 * Encode a codepoint as UTF-8.
 *
 * @param cp The codepoint
 * @param buf_out Receives the bytes, must have room for UTF8_MAX_BYTES
 *
 * @returns The number of bytes written, or -1 if cp is not a valid codepoint
 */
PUB s32 utf8_encode(u32 cp, char *buf_out);

/**
 * Check if the buffer contains only valid UTF-8.
 *
 * @param buf The data
 * @param len The number of bytes, or -1 to use the '\0'-terminated length
 *
 * @returns 0 if the data is valid, -1 if not
 */
PUB s32 utf8_validate(const char *buf, s32 len);

/**
 * Count the codepoints in a valid UTF-8 buffer.
 *
 * @param buf The data
 * @param len The number of bytes, or -1 to use the '\0'-terminated length
 *
 * @returns The number of codepoints, or -1 if the data is not valid UTF-8
 */
PUB s32 utf8_count(const char *buf, s32 len);

#endif /* VASALL_DEVKIT_UTF8_H */
