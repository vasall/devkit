#ifndef VASALL_DEVKIT_TEXT_H
#define VASALL_DEVKIT_TEXT_H

#include <devkit/scope.h>
#include <devkit/types.h>

#include <devkit/memory/utf8.h>

/******************************************************************************
 *
 * 				   STRUCTURES
 *
 ******************************************************************************/

/**
 * A growable UTF-8 text. The buffer always contains valid UTF-8 and is
 * always terminated with a '\0', so it can be passed to C functions directly.
 *
 * Positions given as "index" count codepoints (characters), positions given
 * as "offset" count bytes.
 */
typedef struct Text {
        s32 length;     /* The number of bytes, without the '\0' */
        s32 capacity;   /* The number of allocated bytes, with the '\0' */
        char *buffer;   /* The UTF-8 data */
} Text;

/******************************************************************************
 *
 * 				PUBLIC INTERFACE
 *
 ******************************************************************************/

/**
 * Initialize a text and preallocate memory. Optionally a buffer can be
 * provided, which will be copied into the text.
 *
 * @param txt Pointer to the text
 * @param length Without buf: the number of bytes to preallocate. With buf:
 *               the number of bytes to copy from buf, or -1 to use the
 *               '\0'-terminated length of buf
 * @param buf The UTF-8 data to copy (may be NULL)
 *
 * @returns 0 on success, -1 on error or if buf is not valid UTF-8
 */
PUB s32 text_init(Text *txt, s32 length, const char *buf);

/**
 * Free the buffer and reset all fields.
 */
PUB void text_deinit(Text *txt);

/**
 * Remove all content. The buffer is kept for reuse.
 */
PUB void text_clear(Text *txt);

/**
 * Merge two texts to one new text: txt_out = txt1 + txt2. txt_out must not
 * be initialized yet and has to be freed with text_deinit.
 *
 * @returns 0 on success, -1 on error
 */
PUB s32 text_merge(Text *txt_out, Text txt1, Text txt2);

/**
 * Get the text as a '\0'-terminated C string. The pointer stays valid until
 * the text is changed.
 */
PUB const char *text_cstr(Text *txt);

/**
 * Get the number of codepoints (characters) in the text.
 */
PUB s32 text_count(Text *txt);

/**
 * Get the byte offset of the codepoint at the given index. An index equal to
 * the number of codepoints gives the offset of the end of the text.
 *
 * @returns The byte offset, or -1 if the index is out of range
 */
PUB s32 text_offset(Text *txt, s32 index);

/**
 * Get the codepoint at the given index. Every call walks the text from the
 * start, so use text_next to go through all codepoints.
 *
 * @param txt Pointer to the text
 * @param index The codepoint index
 * @param cp_out Receives the codepoint
 *
 * @returns 0 on success, -1 if the index is out of range
 */
PUB s32 text_get(Text *txt, s32 index, u32 *cp_out);

/**
 * Iterate over the codepoints. Start with *offset = 0, every call returns
 * the codepoint at *offset and moves *offset to the next one.
 *
 *   s32 off = 0;
 *   u32 cp;
 *   while(text_next(&txt, &off, &cp) == 0) { ... }
 *
 * @returns 0 if a codepoint was read, -1 at the end of the text
 */
PUB s32 text_next(Text *txt, s32 *offset, u32 *cp_out);

/**
 * Append UTF-8 data to the end of the text.
 *
 * @param txt Pointer to the text
 * @param buf The UTF-8 data
 * @param len The number of bytes, or -1 to use the '\0'-terminated length
 *
 * @returns 0 on success, -1 on error or if buf is not valid UTF-8
 */
PUB s32 text_append(Text *txt, const char *buf, s32 len);

/**
 * Append a single codepoint to the end of the text.
 *
 * @returns 0 on success, -1 on error or if cp is not a valid codepoint
 */
PUB s32 text_append_cp(Text *txt, u32 cp);

/**
 * Insert UTF-8 data before the codepoint at the given index. An index equal
 * to the number of codepoints appends to the end.
 *
 * @param txt Pointer to the text
 * @param index The codepoint index to insert at
 * @param buf The UTF-8 data
 * @param len The number of bytes, or -1 to use the '\0'-terminated length
 *
 * @returns 0 on success, -1 on error or if buf is not valid UTF-8
 */
PUB s32 text_insert(Text *txt, s32 index, const char *buf, s32 len);

/**
 * Remove codepoints starting at the given index. If fewer than num
 * codepoints follow the index, everything up to the end is removed.
 *
 * @param txt Pointer to the text
 * @param index The index of the first codepoint to remove
 * @param num The number of codepoints to remove
 *
 * @returns The number of codepoints removed, or -1 on error
 */
PUB s32 text_remove(Text *txt, s32 index, s32 num);

#endif /* VASALL_DEVKIT_TEXT_H */
