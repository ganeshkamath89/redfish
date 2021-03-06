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

#ifndef REDFISH_UTIL_THREAD_CTX_DOT_H
#define REDFISH_UTIL_THREAD_CTX_DOT_H

#include <pthread.h> /* for pthread_t */
#include <stdint.h> /* for uint32_t, etc */

struct fast_log_buf;
struct redfish_thread;

typedef int (*redfish_thread_fn_t)(struct redfish_thread*);

struct redfish_thread
{
	pthread_t pthread;
	struct fast_log_buf *fb;
	uint32_t thread_id;
	redfish_thread_fn_t fn;
	void *priv;
};

/** Create a redfish thread
 *
 * @param fb		fast log buffer to use
 * @param rt		(out param) thread structure to be initialized
 * @param fn		function to run
 * @param priv		some data to pass to the new thread
 *
 * @return		0 on success; error code otherwise
 */
int redfish_thread_create_with_fb(struct fast_log_buf *fb,
	struct redfish_thread* rt, redfish_thread_fn_t fn, void *priv);

/** Create a redfish thread
 *
 * @param mgr		fast log manager to use
 * @param rt		(out param) thread structure to be initialized
 * @param fn		function to run
 * @param priv		some data to pass to the new thread
 *
 * @return		0 on success; error code otherwise
 */
extern int redfish_thread_create(struct fast_log_mgr *mgr,
		struct redfish_thread* rt, redfish_thread_fn_t fn,
		void *priv);

/** Join a Redfish thread
 *
 * @param rt		the thread
 *
 * @return		0 on thread success; error code otherwise
 */
extern int redfish_thread_join(struct redfish_thread *rt);

/** Initialize a condition variable to use CLOCK_MONOTONIC
 *
 * @param cond		the condition variable to initialize
 *
 * @return		0 on thread success; error code otherwise
 */
extern int pthread_cond_init_mt(pthread_cond_t *cond);

#endif
