/*
// Copyright (c) 2016 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/
/*
 *
 * Copyright (c) 2013, Institute for Pervasive Computing, ETH Zurich
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 */

#ifndef OBSERVE_H
#define OBSERVE_H

#include "coap.h"
#include "oc_ri.h"
#include "transactions.h"
#include "util/oc_list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct coap_observer
{
  struct coap_observer *next; /* for LIST */

  oc_resource_t *resource;

  oc_string_t url;
  oc_endpoint_t endpoint;
  uint8_t token_len;
  uint8_t token[COAP_TOKEN_LEN];
  uint16_t last_mid;

#ifdef OC_BLOCK_WISE
  uint16_t block2_size;
#endif /* OC_BLOCK_WISE */

  int32_t obs_counter;
  oc_interface_mask_t iface_mask;
  struct oc_etimer retrans_timer;
  uint8_t retrans_counter;
} coap_observer_t;

oc_list_t coap_get_observers(void);
void coap_remove_observer(coap_observer_t *o);
int coap_remove_observer_by_client(oc_endpoint_t *endpoint);
int coap_remove_observer_by_token(oc_endpoint_t *endpoint, uint8_t *token,
                                  size_t token_len);
int coap_remove_observer_by_mid(oc_endpoint_t *endpoint, uint16_t mid);
int coap_remove_observer_by_resource(const oc_resource_t *rsc);
void coap_remove_discovery_batch_observers_by_resource(oc_resource_t *resource);
void coap_free_all_observers(void);
int coap_notify_collection_observers(oc_resource_t *resource,
                                     oc_response_buffer_t *response_buf,
                                     oc_interface_mask_t iface_mask);
void coap_notify_discovery_batch_observers(oc_resource_t *resource);
int coap_notify_observers(oc_resource_t *resource,
                          oc_response_buffer_t *response_buf,
                          oc_endpoint_t *endpoint);
bool coap_want_be_notified(oc_resource_t *resource);
int coap_notify_collection_links_list(oc_collection_t *collection);
int coap_notify_collection_batch(oc_collection_t *collection);
int coap_notify_collection_baseline(oc_collection_t *collection);
void notify_resource_defaults_observer(oc_resource_t *resource,
                                       oc_interface_mask_t iface_mask,
                                       oc_response_buffer_t *response_buf);

#ifdef OC_BLOCK_WISE
int coap_observe_handler(void *request, void *response, oc_resource_t *resource,
                         uint16_t block2_size, oc_endpoint_t *endpoint,
                         oc_interface_mask_t iface_mask);
#else  /* OC_BLOCK_WISE */
int coap_observe_handler(void *request, void *response, oc_resource_t *resource,
                         oc_endpoint_t *endpoint,
                         oc_interface_mask_t iface_mask);
#endif /* !OC_BLOCK_WISE */

int coap_remove_observers_on_dos_change(size_t device, bool reset);

#ifdef __cplusplus
}
#endif

#endif /* OBSERVE_H */
