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

#ifndef OC_COAP_H
#define OC_COAP_H

#include "oc_ri.h"
#include "separate.h"
#include "util/oc_list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct oc_separate_response_s
{
  OC_LIST_STRUCT(requests);
  int active;
#ifdef OC_DYNAMIC_ALLOCATION
  uint8_t *buffer;
#else  /* OC_DYNAMIC_ALLOCATION */
  uint8_t buffer[OC_MAX_APP_DATA_SIZE];
#endif /* !OC_DYNAMIC_ALLOCATION */
  size_t len;
};

struct oc_response_buffer_s
{
  uint8_t *buffer;
  size_t buffer_size;
  size_t response_length;
  int code;
  oc_content_format_t content_format;
};

#ifdef __cplusplus
}
#endif

#endif /* OC_COAP_H */
