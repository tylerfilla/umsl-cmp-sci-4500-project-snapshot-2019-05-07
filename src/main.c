/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <linenoise.h>

int main() {
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
