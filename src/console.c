/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <linenoise.h>

#include "console.h"
#include "log.h"
#include "service.h"

/** The main function. */
static void console() {
  char* line;
  while ((line = linenoise("> "))) {
    if (!strcmp(line, "quit")) {
      free(line);
      break;
    } else if (!strcmp(line, "auto on")) {
      printf("request to enable automatic mode\n");
    } else if (!strcmp(line, "auto off")) {
      printf("request to disable automatic mode\n");
    } else if (!strcmp(line, "start face-watcher")) {
      printf("request to start faces diversion\n");
    } else if (!strcmp(line, "start conversation")) {
      printf("request to start conversation diversion\n");
    } else if (!strcmp(line, "start wander")) {
      printf("request to start wander diversion\n");
    } else {
      printf("Invalid command\n");
    }

    free(line);
  }
}

/** Called when the console service loads. */
static int on_load(struct service* svc) {
  pid_t pid = fork();

  switch (pid) {
    case -1:
      LOGE("Failed to create console process");
      return 1;
    case 0:
      console();
      exit(0);
    default:
      LOGT("Created console process");
      return 0;
  }
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

/** Obtain a procedure on the console service. */
static (* proc(struct service* svc, int fn))(const void* arg1, void* arg2) {
  return 1; // TODO
}

static struct service_iface IFACE = (struct service_iface) {
  .on_load = &on_load,
  .on_unload = &on_unload,
  .on_start = &on_start,
  .on_stop = &on_stop,
  .proc = &proc,
};

struct service* const SERVICE_CONSOLE = &(struct service) {
  .name = "console",
  .description = "The console service runs the console user interface (CUI).",
  .iface = &IFACE,
};
