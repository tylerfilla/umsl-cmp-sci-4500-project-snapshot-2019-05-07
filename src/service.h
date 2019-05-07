/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_H
#define SERVICE_H

struct service_iface;
struct service_state;

/** Definition of a service. */
struct service {
  /** The service name. */
  const char* name;

  /** The service description. */
  const char* description;

  /**
   * The service interface.
   *
   * This provides ways to call into the service.
   */
  struct service_iface* iface;

  /**
   * The service state.
   *
   * This is used internally to keep state.
   */
  struct service_state* state;
};

/** A service interface. */
struct service_iface {
  /** The load callback. */
  int (* on_load)(struct service* svc);

  /** The unload callback. */
  int (* on_unload)(struct service* svc);

  /** The start callback. */
  int (* on_start)(struct service* svc);

  /** The stop callback. */
  int (* on_stop)(struct service* svc);

  /** Call into a service. */
  int (* on_call)(struct service* svc, int fn, const void* arg1, void* arg2);
};

/**
 * Load a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_load(struct service* svc);

/**
 * Unload a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_unload(struct service* svc);

/**
 * Start a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_start(struct service* svc);

/**
 * Stop a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_stop(struct service* svc);

/**
 * Call into a service.
 *
 * @param svc The service definition
 * @param fn The function ordinal
 * @param arg1 An immutable argument
 * @param arg2 A mutable argument
 * @return Zero on success, otherwise nonzero
 */
int service_call(struct service* svc, int fn, const void* arg1, void* arg2);

#endif // #ifndef SERVICE_H
