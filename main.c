/**
 * Copyright (c) 2009 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
* @brief Example template project.
* @defgroup nrf_templates_example Example Template
*
*/

#include <stdbool.h>
#include <stdint.h>

#include "boards.h"
#include "nordic_common.h"
#include "nrf.h"
#include "nrf_ble_scan.h"
#include "nrf_error.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_sdh_soc.h"
#include "sdk_common.h"

#define APP_BLE_CONN_CFG_TAG 1
#define APP_BLE_OBSERVER_PRIO 3

nrf_ble_scan_t m_scan;

static void ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context) {
  UNUSED_PARAMETER(p_context);

  ble_gap_evt_t const *p_gap_evt = &p_ble_evt->evt.gap_evt;

  switch (p_ble_evt->header.evt_id) {
  case BLE_GAP_EVT_ADV_REPORT:
    NRF_LOG_INFO("BLE Device Found!");
    nrf_ble_scan_start(&m_scan);
    break;

  default:
    break;
  }
}

static void log_init(void) {
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

  NRF_LOG_DEFAULT_BACKENDS_INIT();
}

static void ble_stack_init(void) {
  APP_ERROR_CHECK(nrf_sdh_enable_request());

  uint32_t ram_start = 0;
  APP_ERROR_CHECK(nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start));

  APP_ERROR_CHECK(nrf_sdh_ble_enable(&ram_start));

  NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);
}

static void scan_init(void) {
  APP_ERROR_CHECK(nrf_ble_scan_init(&m_scan, NULL, NULL));
}

static void scan_start(void) {
  APP_ERROR_CHECK(nrf_ble_scan_start(&m_scan));
}

int main(void) {
  log_init();
  ble_stack_init();
  scan_init();
  scan_start();

  NRF_LOG_INFO("Initialization... Done");

  while (true) {
    // Do nothing.
  }
}
/** @} */