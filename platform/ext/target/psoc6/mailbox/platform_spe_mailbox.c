/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* -------------------------------------- Includes ----------------------------------- */
#include "cmsis.h"
#include "cmsis_compiler.h"

#include "cy_device.h"
#include "cy_device_headers.h"
#include "cy_ipc_drv.h"
#include "cy_sysint.h"

#include "spe_ipc_config.h"
#include "tfm_spe_mailbox.h"
#include "platform_multicore.h"

/* -------------------------------------- HAL API ------------------------------------ */

int32_t tfm_mailbox_notify_peer(void)
{
    return MAILBOX_SUCCESS;
}
#if CY_SYSTEM_CPU_CM0P
static void mailbox_ipc_config(void)
{
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    Cy_SysInt_SetIntSource(PSA_CLIENT_CALL_IRQn, cpuss_interrupts_ipc_4_IRQn);

    NVIC_SetPriority(PSA_CLIENT_CALL_IRQn, PSA_CLIENT_CALL_INTR_PRIORITY);

    NVIC_EnableIRQ(PSA_CLIENT_CALL_IRQn);
}
#else
static void mailbox_ipc_config(void)
{
}
#endif

int32_t tfm_mailbox_hal_init(struct secure_mailbox_queue_t *s_queue)
{
    struct ns_mailbox_queue_t *ns_queue = NULL;

    /* Inform NSPE that NSPE mailbox initialization can start */
    platform_mailbox_send_msg_data(NS_MAILBOX_INIT_ENABLE);

    platform_mailbox_wait_for_notify();

    /* Receive the address of NSPE mailbox queue */
    platform_mailbox_fetch_msg_ptr((void **)&ns_queue);

    /*
     * FIXME
     * Necessary sanity check of the address of NPSE mailbox queue should
     * be implemented there.
     */

    s_queue->ns_queue = ns_queue;

    mailbox_ipc_config();

    /* Inform NSPE that SPE mailbox service is ready */
    platform_mailbox_send_msg_data(S_MAILBOX_READY);

    return MAILBOX_SUCCESS;
}

void tfm_mailbox_enter_critical(void)
{
}

void tfm_mailbox_exit_critical(void)
{
}