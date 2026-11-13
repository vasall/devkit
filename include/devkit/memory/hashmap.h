#ifndef VASALL_DEVKIT_HASHMAP_H
#define VASALL_DEVKIT_HASHMAP_H

#include <devkit/scope.h>
#include <devkit/types.h>

/******************************************************************************
 *
 * 				   STRUCTURES
 *
 ******************************************************************************/

/**
 * Open-addressing hash map from u64 keys to u64 values, with linear probing.
 * Key 0 is reserved as the empty marker and can't be stored. To map to
 * bigger values, store an index or a PoolHandle packed into the u64.
 */
typedef struct HashMap {
        u64 *keys;
        u64 *values;
        s32 capacity;           /* Always a power of two */
        s32 count;              /* The number of stored keys */
} HashMap;

/******************************************************************************
 *
 * 				PUBLIC INTERFACE
 *
 ******************************************************************************/

/**
 * Initialize a map with room for at least ini entries before it grows.
 *
 * @returns 0 on success, -1 on error
 */
PUB s32 hashmap_init(HashMap *map, s32 ini);

/**
 * Free the buffers and reset all fields.
 */
PUB void hashmap_deinit(HashMap *map);

/**
 * Remove all entries. The buffers are kept for reuse.
 */
PUB void hashmap_clear(HashMap *map);

/**
 * Insert a key or overwrite its value. Grows the map if needed.
 *
 * @returns 0 on success, -1 on error (key 0 or out of memory)
 */
PUB s32 hashmap_set(HashMap *map, u64 key, u64 value);

/**
 * Look up a key.
 *
 * @param value_out Receives the value if found (may be NULL)
 *
 * @returns 1 if the key was found, 0 if not
 */
PUB s32 hashmap_get(HashMap *map, u64 key, u64 *value_out);

/**
 * Remove a key.
 *
 * @returns 1 if it was removed, 0 if it wasn't there
 */
PUB s32 hashmap_remove(HashMap *map, u64 key);

/**
 * Returns the number of stored keys, or -1 on error.
 */
PUB s32 hashmap_count(HashMap *map);

#endif /* VASALL_DEVKIT_HASHMAP_H */
