/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdbool.h>
#include "tfm_platform_api.h"
#include "tfm_multicore_api.h"

#include "platform_multicore.h"


enum tfm_platform_err_t tfm_ns_wait_for_s_cpu_ready(void)
{
    return platform_ns_wait_for_s_cpu_ready();
}