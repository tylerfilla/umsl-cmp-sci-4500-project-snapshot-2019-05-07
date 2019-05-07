/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stddef.h>

#include "console.h"
#include "service.h"

/** Called when the console service loads. */
static int on_load(struct service* svc) {
  return 1; // TODO
}

/** Called when the console service unloads. */
static int on_unload(struct service* svc) {
  return 1; // TODO
}

/** Called when the console service starts. */
static int on_start(struct service* svc) {
  return 1; // TODO
}

/** Called when the console service stops. */
static int on_stop(struct service* svc) {
  return 1; // TODO
}

/** Handle a call to the console service. */
static int on_call(struct service* svc, int fn, const void* arg1, void* arg) {
  return 1; // TODO
}

static struct service_iface* const IFACE = &(struct service_iface) {
  .on_load = &on_load,
  .on_unload = &on_unload,
  .on_start = &on_start,
  .on_stop = &on_stop,
  .on_call = &on_call,
};

struct service* const SERVICE_CONSOLE = &(struct service) {
  .name = "console",
  .description = "The console service runs the console user interface (CUI).",
  .iface = IFACE,
};
