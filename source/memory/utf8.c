#include <devkit/memory/utf8.h>

#include <stddef.h>
#include <string.h>

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 utf8_decode(const char *buf, s32 len, u32 *cp_out)
{
        const u8 *b = (const u8 *)buf;
        s32 need;
        u32 cp;
        u8 lo = 0x80;   /* Allowed range of the second byte */
        u8 hi = 0xBF;
        s32 i;

        if(!buf || len < 1) {
                return -1;
        }

        /* The first byte tells how many bytes follow */
        if(b[0] < 0x80) {
                if(cp_out) *cp_out = b[0];
                return 1;
        } else if(b[0] >= 0xC2 && b[0] <= 0xDF) {
                need = 2;
                cp = b[0] & 0x1F;
        } else if(b[0] >= 0xE0 && b[0] <= 0xEF) {
                need = 3;
                cp = b[0] & 0x0F;
                if(b[0] == 0xE0) lo = 0xA0;     /* Overlong */
                if(b[0] == 0xED) hi = 0x9F;     /* Surrogates */
        } else if(b[0] >= 0xF0 && b[0] <= 0xF4) {
                need = 4;
                cp = b[0] & 0x07;
                if(b[0] == 0xF0) lo = 0x90;     /* Overlong */
                if(b[0] == 0xF4) hi = 0x8F;     /* Above U+10FFFF */
        } else {
                /* A continuation byte, C0/C1 (overlong) or F5..FF */
                return -1;
        }

        if(len < need) {
                return -1;
        }

        /* The second byte has a narrower range for some first bytes */
        if(b[1] < lo || b[1] > hi) {
                return -1;
        }

        for(i = 1; i < need; i++) {
                if((b[i] & 0xC0) != 0x80) {
                        return -1;
                }
                cp = (cp << 6) | (b[i] & 0x3F);
        }

        if(cp_out) *cp_out = cp;
        return need;
}

PUB s32 utf8_encode(u32 cp, char *buf_out)
{
        u8 *b = (u8 *)buf_out;

        if(!buf_out) {
                return -1;
        }

        if(cp < 0x80) {
                b[0] = (u8)cp;
                return 1;
        }
        if(cp < 0x800) {
                b[0] = (u8)(0xC0 | (cp >> 6));
                b[1] = (u8)(0x80 | (cp & 0x3F));
                return 2;
        }
        if(cp < 0x10000) {
                /* Surrogates are reserved for UTF-16 */
                if(cp >= 0xD800 && cp <= 0xDFFF) {
                        return -1;
                }
                b[0] = (u8)(0xE0 | (cp >> 12));
                b[1] = (u8)(0x80 | ((cp >> 6) & 0x3F));
                b[2] = (u8)(0x80 | (cp & 0x3F));
                return 3;
        }
        if(cp <= 0x10FFFF) {
                b[0] = (u8)(0xF0 | (cp >> 18));
                b[1] = (u8)(0x80 | ((cp >> 12) & 0x3F));
                b[2] = (u8)(0x80 | ((cp >> 6) & 0x3F));
                b[3] = (u8)(0x80 | (cp & 0x3F));
                return 4;
        }

        return -1;
}

PUB s32 utf8_validate(const char *buf, s32 len)
{
        return utf8_count(buf, len) < 0 ? -1 : 0;
}

PUB s32 utf8_count(const char *buf, s32 len)
{
        s32 off = 0;
        s32 num = 0;
        s32 step;

        if(!buf) {
                return -1;
        }

        if(len < 0) {
                len = (s32)strlen(buf);
        }

        while(off < len) {
                if((step = utf8_decode(buf + off, len - off, NULL)) < 0) {
                        return -1;
                }
                off += step;
                num++;
        }

        return num;
}
