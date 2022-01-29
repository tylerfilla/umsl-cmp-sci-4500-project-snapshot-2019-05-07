/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdlib.h>

#include "log.h"
#include "service.h"

struct service_state {
  /** Nonzero iff started. */
  int started;
};

int service_load(struct service* svc) {
  LOGT("Loading {}", _str(svc->name));

  // If service has allocated state, ...
  if (svc->state) {
    // ... then it is already loaded
    LOGE("Already loaded %s", svc->name);
    return 1;
  }

  // Allocate service state
  svc->state = malloc(sizeof(struct service_state));
  svc->state->started = 0;

  // Call back to service
  if (svc->iface) {
    int code;
    if ((code = svc->iface->on_load(svc))) {
      LOGW("%s on_load() returned code %d", svc->name, code);
    }
  }

  LOGI("Loaded %s", svc->name);
  return 0;
}

int service_unload(struct service* svc) {
  LOGT("Unloading %s", svc->name);

  // If service does NOT have allocated state, ...
  if (!svc->state) {
    // ... then it is NOT already loaded
    LOGE("Not loaded %s", svc->name);
    return 1;
  }

  // Call back to service
  if (svc->iface) {
    int code;
    if ((code = svc->iface->on_unload(svc))) {
      LOGW("%s on_unload() returned code %d", svc->name, code);
    }
  }

  // Deallocate service state
  free(svc->state);

  LOGI("Unloaded %s", svc->name);
  return 0;
}

int service_start(struct service* svc) {
  LOGT("Starting %s", svc->name);

  // If service does NOT have allocated state, ...
  if (!svc->state) {
    // ... then it is NOT already loaded
    LOGE("Not loaded %s", svc->name);
    return 1;
  }

  // If service is already started
  if (svc->state->started) {
    LOGE("Already started %s", svc->name);
    return 1;
  }

  // Set started flag
  svc->state->started = 1;

  // Call back to service
  if (svc->iface) {
    int code;
    if ((code = svc->iface->on_start(svc))) {
      LOGW("%s on_start() returned code %d", svc->name, code);
    }
  }

  LOGI("Started %s", svc->name);
  LOGI("%s", svc->description);
  return 0;
}

int service_stop(struct service* svc) {
  LOGT("Stopping %s", svc->name);

  // If service does NOT have allocated state, ...
  if (!svc->state) {
    // ... then it is NOT already loaded
    LOGE("Not loaded %s", svc->name);
    return 1;
  }

  // If service is not already started
  if (!svc->state->started) {
    LOGE("Not started %s", svc->name);
    return 1;
  }

  // Call back to service
  if (svc->iface) {
    int code;
    if ((code = svc->iface->on_stop(svc))) {
      LOGW("%s on_stop() returned code %d", svc->name, code);
    }
  }

  // Clear started flag
  svc->state->started = 0;

  LOGI("Stopped %s", svc->name);
  return 0;
}

int service_call(struct service* svc, int fn, const void* a, void* b) {
  // If service does NOT have allocated state, ...
  if (!svc->state) {
    // ... then it is NOT already loaded
    LOGE("Not loaded %s", svc->name);
    return 1;
  }

  // If service is not already started
  if (!svc->state->started) {
    LOGE("Not started %s", svc->name);
    return 1;
  }

  if (svc->iface) {
    // Get the actual procedure
    int (* proc)(const void*, void*) = svc->iface->proc(fn);

    // And call it
    int code;
    if ((code = proc(a, b))) {
      LOGW("%s proc #%d returned code %d", svc->name, fn, code);
    }
  }

  return 0;
}
