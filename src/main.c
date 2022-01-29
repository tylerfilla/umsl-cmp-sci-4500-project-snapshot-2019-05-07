/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "console.h"
#include "service.h"

int main() {
  service_load(SERVICE_CONSOLE);
  service_start(SERVICE_CONSOLE);
  service_stop(SERVICE_CONSOLE);
  service_unload(SERVICE_CONSOLE);
}
