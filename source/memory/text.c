#include <devkit/memory/text.h>

#include <devkit/log/log.h>
#include <devkit/util/helper.h>

#include <stdlib.h>
#include <string.h>

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

/* Get the length of buf: len itself, or the '\0'-terminated length if -1 */
LOC s32 t_length(const char *buf, s32 len);

/* Make room for at least min_bytes bytes plus the '\0' */
LOC s32 t_reserve(Text *txt, s32 min_bytes);

/* Insert len bytes of valid UTF-8 at the byte offset */
LOC s32 t_insert_bytes(Text *txt, s32 offset, const char *buf, s32 len);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 text_init(Text *txt, s32 length, const char *buf)
{
        s32 bytes;

        if(!txt || (!buf && length < 0)) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        bytes = buf ? t_length(buf, length) : 0;

        if(buf && utf8_validate(buf, bytes) < 0) {
                LOG(LOG_ERROR, "Text is not valid UTF-8");
                return -1;
        }

        /* Always room for the '\0', even for an empty text */
        txt->capacity = MAX(buf ? bytes : length, 0) + 1;
        if(!(txt->buffer = malloc(txt->capacity))) {
                LOG(LOG_ERROR, "Failed to allocate memory for text");
                txt->capacity = 0;
                return -1;
        }

        if(bytes > 0) {
                memcpy(txt->buffer, buf, bytes);
        }
        txt->length = bytes;
        txt->buffer[bytes] = '\0';

        return 0;
}

PUB void text_deinit(Text *txt)
{
        if(!txt) {
                return;
        }

        free(txt->buffer);
        txt->buffer = NULL;
        txt->length = 0;
        txt->capacity = 0;
}

PUB void text_clear(Text *txt)
{
        if(!txt || !txt->buffer) {
                return;
        }

        txt->length = 0;
        txt->buffer[0] = '\0';
}

PUB s32 text_merge(Text *txt_out, Text txt1, Text txt2)
{
        if(!txt_out) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if(text_init(txt_out, txt1.length + txt2.length, NULL) < 0) {
                return -1;
        }

        /* Both are valid UTF-8 already, so the bytes can just be joined */
        memcpy(txt_out->buffer, txt1.buffer, txt1.length);
        memcpy(txt_out->buffer + txt1.length, txt2.buffer, txt2.length);
        txt_out->length = txt1.length + txt2.length;
        txt_out->buffer[txt_out->length] = '\0';

        return 0;
}

PUB const char *text_cstr(Text *txt)
{
        if(!txt || !txt->buffer) {
                return "";
        }

        return txt->buffer;
}

PUB s32 text_count(Text *txt)
{
        if(!txt || !txt->buffer) {
                return 0;
        }

        return utf8_count(txt->buffer, txt->length);
}

PUB s32 text_offset(Text *txt, s32 index)
{
        s32 off = 0;
        s32 i;

        if(!txt || !txt->buffer || index < 0) {
                return -1;
        }

        for(i = 0; i < index; i++) {
                s32 step;

                if(off >= txt->length) {
                        return -1;
                }

                step = utf8_decode(txt->buffer + off, txt->length - off, NULL);
                if(step < 0) {
                        return -1;
                }
                off += step;
        }

        return off;
}

PUB s32 text_get(Text *txt, s32 index, u32 *cp_out)
{
        s32 off;

        if(!cp_out || (off = text_offset(txt, index)) < 0) {
                return -1;
        }

        if(off >= txt->length) {
                return -1;
        }

        return utf8_decode(txt->buffer + off, txt->length - off, cp_out) < 0 ?
                -1 : 0;
}

PUB s32 text_next(Text *txt, s32 *offset, u32 *cp_out)
{
        s32 step;

        if(!txt || !txt->buffer || !offset || *offset < 0 ||
                        *offset >= txt->length) {
                return -1;
        }

        step = utf8_decode(txt->buffer + *offset, txt->length - *offset,
                        cp_out);
        if(step < 0) {
                return -1;
        }

        *offset += step;
        return 0;
}

PUB s32 text_append(Text *txt, const char *buf, s32 len)
{
        if(!txt || !txt->buffer || !buf) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        return t_insert_bytes(txt, txt->length, buf, t_length(buf, len));
}

PUB s32 text_append_cp(Text *txt, u32 cp)
{
        char bytes[UTF8_MAX_BYTES];
        s32 len;

        if(!txt || !txt->buffer) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if((len = utf8_encode(cp, bytes)) < 0) {
                LOG(LOG_ERROR, "Invalid codepoint");
                return -1;
        }

        return t_insert_bytes(txt, txt->length, bytes, len);
}

PUB s32 text_insert(Text *txt, s32 index, const char *buf, s32 len)
{
        s32 off;

        if(!txt || !txt->buffer || !buf) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if((off = text_offset(txt, index)) < 0) {
                LOG(LOG_ERROR, "Index out of bounds");
                return -1;
        }

        return t_insert_bytes(txt, off, buf, t_length(buf, len));
}

PUB s32 text_remove(Text *txt, s32 index, s32 num)
{
        s32 start;
        s32 end;
        s32 removed = 0;

        if(!txt || !txt->buffer || num < 0) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        if((start = text_offset(txt, index)) < 0) {
                LOG(LOG_ERROR, "Index out of bounds");
                return -1;
        }

        /* Walk num codepoints forward, or until the end */
        end = start;
        while(removed < num && end < txt->length) {
                end += utf8_decode(txt->buffer + end, txt->length - end, NULL);
                removed++;
        }

        /* Move the rest, including the '\0', to the front */
        memmove(txt->buffer + start, txt->buffer + end,
                        txt->length - end + 1);
        txt->length -= end - start;

        return removed;
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC s32 t_length(const char *buf, s32 len)
{
        return len < 0 ? (s32)strlen(buf) : len;
}

LOC s32 t_reserve(Text *txt, s32 min_bytes)
{
        s32 new_cap;
        char *ptr;

        if(min_bytes + 1 <= txt->capacity) {
                return 0;
        }

        new_cap = MAX(txt->capacity * 2, min_bytes + 1);

        if(!(ptr = realloc(txt->buffer, new_cap))) {
                LOG(LOG_ERROR, "Failed to allocate memory for text");
                return -1;
        }

        txt->buffer = ptr;
        txt->capacity = new_cap;

        return 0;
}

LOC s32 t_insert_bytes(Text *txt, s32 offset, const char *buf, s32 len)
{
        if(len == 0) {
                return 0;
        }

        if(utf8_validate(buf, len) < 0) {
                LOG(LOG_ERROR, "Text is not valid UTF-8");
                return -1;
        }

        if(t_reserve(txt, txt->length + len) < 0) {
                return -1;
        }

        /* Make room, move the rest including the '\0' back */
        memmove(txt->buffer + offset + len, txt->buffer + offset,
                        txt->length - offset + 1);
        memcpy(txt->buffer + offset, buf, len);
        txt->length += len;

        return 0;
}
