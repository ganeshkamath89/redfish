/*
 * Copyright 2011-2012 the Redfish authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef REDFISH_UTIL_FAST_LOG_MGR_H
#define REDFISH_UTIL_FAST_LOG_MGR_H

#include "util/bitfield.h"
#include "util/compiler.h"
#include "util/fast_log.h"
#include "util/queue.h"

#include <pthread.h> /* for pthread_spinlock_t */
#include <stdint.h> /* for uint32_t, etc. */

/* The fast log manager keeps track of fast log buffers and log settings.
 *
 * Typically there would be one fast log manager per daemon.  In a library
 * setting, the fast log manager would be associated with the library "context"
 * -- for example, in the client library, cthere would be one per Redfish
 *  client.
 */

struct fast_log_buf;

/** Initialize a fast log manager.
 *
 * @param dumpers	Array mapping fast_log message IDs to dumper functions.
 * 			We will keep a pointer to this parameter.
 *
 * @return		An error pointer on failure; the new fast log manager on
 *			success.
 */
extern struct fast_log_mgr* fast_log_mgr_init(const fast_log_dumper_fn_t *dumpers);

/** Release a fast log manager
 *
 * Decrement the reference count on the fast log manager, freeing it if
 * necessary.
 *
 * @param mgr		The fast log manager
 */
extern void fast_log_mgr_release(struct fast_log_mgr* mgr);

/** Registers a fast log buffer with a manager
 *
 * @param mgr		The fastlog buffer manager
 * @param fb		The fastlog buffer to register
 */
extern void fast_log_mgr_register_buffer(struct fast_log_mgr *mgr,
					struct fast_log_buf *fb);

/** Unregister a fast log buffer
 *
 * @param mgr		The fastlog buffer manager
 * @param fb		The fast_log buffer
 */
extern void fast_log_mgr_unregister_buffer(struct fast_log_mgr *mgr,
					struct fast_log_buf* fb);

/** Dump all fast_logs
 *
 * This function is signal-safe.
 * This function is _not_ re-entrant (only one caller at a time, please!)
 *
 * @param mgr		The fastlog buffer manager
 * @param fd		file descriptor to dump fast logs to.
 *
 * @return		0 on success; error code otherwise
 */
extern int fast_log_mgr_dump_all(struct fast_log_mgr* mgr, int fd);

/** Copy the manager's message storage settings
 *
 * @param mgr		The fastlog buffer manager
 * @param stored	(out-param) the stored bitfield
 * @param store		(out-param) the store callback
 * @param store_ctx	(out-param) context pointer to be passed to the
 *			store callback
 */
extern void fast_log_mgr_cp_storage_settings(struct fast_log_mgr *mgr,
		BITFIELD_DECL(stored, FAST_LOG_TYPE_MAX),
		fast_log_storage_fn_t *store, void **store_ctx);

/** Set the manager's message storage settings
 *
 * @param mgr		The fastlog buffer manager
 * @param stored	the new stored bitfield
 * @param store		the new store callback
 * @param store_ctx	the new context pointer to be passed to the store
 *			callback
 */
extern void fast_log_mgr_set_storage_settings(struct fast_log_mgr *mgr,
		BITFIELD_DECL(stored, FAST_LOG_TYPE_MAX),
		fast_log_storage_fn_t store, void *store_ctx);

#endif
