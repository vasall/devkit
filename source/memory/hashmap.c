#include <devkit/memory/hashmap.h>

#include <devkit/log/log.h>

#include <stdlib.h>
#include <string.h>

/*
 * Keys and values live in two parallel arrays of capacity slots; key 0 marks
 * an empty slot. Lookups start at the slot given by the mixed key and walk
 * forward until they find the key or an empty slot. The map grows at a load
 * of 0.7, and removal shifts later entries back, so there are no tombstones.
 */

/* Build a 64-bit constant from two 32-bit halves (no long long in C89) */
#define H_U64(hi, lo) (((u64)(hi) << 32) | (u64)(lo))

/******************************************************************************
 *
 * 				LOCAL INTERFACE
 *
 ******************************************************************************/

/* Spread the bits of a key, so keys differing in few bits don't cluster */
LOC u64 h_mix(u64 key);

/* Move all entries into a map with twice the capacity */
LOC s32 h_grow(HashMap *map);

/******************************************************************************
 *
 * 				PUBLIC FUNCTIONS
 *
 ******************************************************************************/

PUB s32 hashmap_init(HashMap *map, s32 ini)
{
        s32 cap = 16;

        if(!map || ini < 0) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        while(cap < ini * 2) cap *= 2;

        map->keys = calloc((size_t)cap, sizeof(u64));
        map->values = calloc((size_t)cap, sizeof(u64));
        if(!map->keys || !map->values) {
                LOG(LOG_ERROR, "Failed to allocate memory for hash map");
                free(map->keys);
                free(map->values);
                map->keys = NULL;
                map->values = NULL;
                return -1;
        }

        map->capacity = cap;
        map->count = 0;
        return 0;
}

PUB void hashmap_deinit(HashMap *map)
{
        if(!map) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        free(map->keys);
        free(map->values);

        map->keys = NULL;
        map->values = NULL;
        map->capacity = 0;
        map->count = 0;
}

PUB void hashmap_clear(HashMap *map)
{
        if(!map || !map->keys) {
                LOG(LOG_WARN, "Invalid parameter(s)");
                return;
        }

        memset(map->keys, 0, (size_t)map->capacity * sizeof(u64));
        map->count = 0;
}

PUB s32 hashmap_set(HashMap *map, u64 key, u64 value)
{
        u64 mask;
        u64 i;

        if(!map || !map->keys || key == 0) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }

        /* Keep the load factor below 0.7 */
        if((map->count + 1) * 10 > map->capacity * 7) {
                if(h_grow(map) < 0) return -1;
        }

        mask = (u64)map->capacity - 1;
        i = h_mix(key) & mask;
        while(map->keys[i] != 0) {
                if(map->keys[i] == key) {
                        map->values[i] = value;
                        return 0;
                }
                i = (i + 1) & mask;
        }

        map->keys[i] = key;
        map->values[i] = value;
        map->count++;
        return 0;
}

PUB s32 hashmap_get(HashMap *map, u64 key, u64 *value_out)
{
        u64 mask;
        u64 i;

        if(!map || !map->keys || key == 0) return 0;

        mask = (u64)map->capacity - 1;
        i = h_mix(key) & mask;
        while(map->keys[i] != 0) {
                if(map->keys[i] == key) {
                        if(value_out) *value_out = map->values[i];
                        return 1;
                }
                i = (i + 1) & mask;
        }
        return 0;
}

PUB s32 hashmap_remove(HashMap *map, u64 key)
{
        u64 mask;
        u64 i;
        u64 j;
        u64 home;

        if(!map || !map->keys || key == 0) return 0;

        mask = (u64)map->capacity - 1;
        i = h_mix(key) & mask;
        while(map->keys[i] != key) {
                if(map->keys[i] == 0) return 0;
                i = (i + 1) & mask;
        }

        /*
         * Backward-shift deletion: move later entries of the same probe run
         * into the hole, so lookups never stop early at a gap.
         */
        j = i;
        for(;;) {
                j = (j + 1) & mask;
                if(map->keys[j] == 0) break;

                home = h_mix(map->keys[j]) & mask;

                /* Leave entries whose home lies cyclically in (i, j] */
                if(i <= j) {
                        if(i < home && home <= j) continue;
                } else {
                        if(i < home || home <= j) continue;
                }

                map->keys[i] = map->keys[j];
                map->values[i] = map->values[j];
                i = j;
        }

        map->keys[i] = 0;
        map->count--;
        return 1;
}

PUB s32 hashmap_count(HashMap *map)
{
        if(!map) {
                LOG(LOG_ERROR, "Invalid parameter(s)");
                return -1;
        }
        return map->count;
}

/******************************************************************************
 *
 * 				LOCAL FUNCTIONS
 *
 ******************************************************************************/

LOC u64 h_mix(u64 key)
{
        /* Finalizer of MurmurHash3 */
        key ^= key >> 33;
        key *= H_U64(0xff51afd7UL, 0xed558ccdUL);
        key ^= key >> 33;
        key *= H_U64(0xc4ceb9feUL, 0x1a85ec53UL);
        key ^= key >> 33;
        return key;
}

LOC s32 h_grow(HashMap *map)
{
        HashMap bigger;
        s32 i;

        if(hashmap_init(&bigger, map->capacity) < 0) return -1;

        for(i = 0; i < map->capacity; i++) {
                if(map->keys[i] != 0)
                        hashmap_set(&bigger, map->keys[i], map->values[i]);
        }

        free(map->keys);
        free(map->values);
        *map = bigger;
        return 0;
}
