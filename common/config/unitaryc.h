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

#ifndef REDFISH_COMMON_CONFIG_UNITARYC_DOT_H
#define REDFISH_COMMON_CONFIG_UNITARYC_DOT_H

#include "common/config/mdsc.h"
#include "common/config/osdc.h"

#include <unistd.h> /* for size_t */

#define JORM_CUR_FILE "common/config/unitaryc.jorm"
#include "jorm/jorm_generate_include.h"
#undef JORM_CUR_FILE

#if 0 /* Give the dependency scanner a clue */
#include "common/config/unitaryc.jorm"
#endif

/** Parse a unitary configuration file.
 *
 * @param fname		The file name to open
 * @param err		(out-param) the error message, on failure
 * @param err_len	length of the error buffer
 *
 * @return		the dynamically allocated unitary configuration data
 */
extern struct unitaryc *parse_unitary_conf_file(const char *fname,
					char *err, size_t err_len);

/** Harmonize the unitary configuration
 *
 * @param conf		The configuration
 * @param err		(out param) The error buffer
 * @param err_len	Length of the error buffer
 */
extern void harmonize_unitary_conf(struct unitaryc *conf, char *err,
					size_t err_len);

/** Free unitary configuration data.
 *
 * @param conf		The unitary configuration data
 */
extern void free_unitary_conf_file(struct unitaryc *conf);

/** Look up a given MDS configuration
 *
 * @param conf		The unitary configuration data
 * @param mid		The mid to look up
 *
 * @return 		NULL if there was no such mid; the conf otherwise
 */
extern struct mdsc *unitaryc_lookup_mdsc(struct unitaryc *conf, int mid);

/** Look up a given OSD configuration
 *
 * @param conf		The unitary configuration data
 * @param oid		The oid to look up
 *
 * @return 		NULL if there was no such oid; the conf otherwise
 */
extern struct osdc *unitaryc_lookup_osdc(struct unitaryc *conf, int oid);

#endif
