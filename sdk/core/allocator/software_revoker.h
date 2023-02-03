// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include <cdefs.h>
#include <stdint.h>

/**
 * Prod the software revoker to do some work.  This does not do a complete
 * revocation pass, it will scan a region of memory and then return.
 */
[[cheri::interrupt_state(disabled)]] __cheri_compartment(
  "software_revoker") void revoker_tick();

/**
 * Returns a read-only capability to the current revocation epoch.  If the low
 * bit of the epoch is 1 then revocation is running.  The revocation epoch will
 * wrap, the caller is responsible for handling overflow.
 */
const uint32_t *__cheri_compartment("software_revoker") revoker_epoch_get();
