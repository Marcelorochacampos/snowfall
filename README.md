# Snowfall
Snowfall is a C++ HTTP Framework project which is currently a WIP.

## Table of Contents

1. [Server](#server)
2. [Routing](#routing)
3. [Middleware](#middleware)
4. [Json](#json)

## Server

The **Server** section provides an overview of how to set up and configure the server component of the framework. It includes instructions on initializing the server, handling incoming requests, and managing server settings. More on the examples folder.

Example
```
#include <snowfall/core/server.h>

int main()
{
  ::snowfall::core::Server server{"0.0.0.0", 50056};
  server.run();
}
```

## Routing

The **Routing** section details the routing capabilities of the framework. It explains how to define routes, handle different HTTP methods, and manage route parameters. This section will guide you through setting up routes and directing requests to the appropriate handlers. More on the examples folder.

```
#include <snowfall/core/server.h>
#include <snowfall/core/router.h>

#include "my_controller.h"

int main()
{
  ::snowfall::core::Server server{"0.0.0.0", 50056};

  MyController my_controller;

  ::snowfall::core::Router& router = ::snowfall::core::Router::instance();

  router.route("/api/hello", &MyController::Hello, &my_controller, HttpMethods::POST);
  router.route("/api/users", &MyController::List, &my_controller, HttpMethods::GET);

  server.run();
}
```

## Middleware

The **Middleware** section describes the middleware system used in the framework. It covers how to create, configure, and use middleware to process requests and responses. Learn how to apply middleware functions globally or per route to add custom logic to your application's request handling. More on the examples folder.

```
#include <snowfall/core/router.h>
#include <snowfall/core/server.h>

#include <iostream>

#include "my_controller.h"
#include "my_middleware.h"

int main()
{
  ::snowfall::core::Server server{"0.0.0.0", 50056};

  MyController my_controller;
  MyMiddleware my_middleware;

  ::snowfall::core::Router& router = ::snowfall::core::Router::instance();

  router.route("/api/users", &MyController::List, &my_controller, HttpMethods::GET);

  std::vector<std::shared_ptr<::snowfall::core::Middleware>> middlewares;
  middlewares.push_back(std::make_shared<MyMiddleware>());
  std::unordered_map<std::string, HttpMethods> for_routes = {{"/api/users", HttpMethods::GET}};
  router.middlewares(middlewares).for_routes(for_routes);

  server.run();
}
```

## Json

The **Json** section explains how to work with JSON data within the framework. The Snowfall framework has a built in Json builder which will help create complex data structures. This section will help you integrate JSON handling into your application efficiently. More on the examples folder.

```
::snowfall::core::JsonObject body;
body["name"] = ::snowfall::core::JsonValue("Foo");
body["surname"] = ::snowfall::core::JsonValue("Bar");
body["age"] = ::snowfall::core::JsonValue(35);
body["number_of_things"] = ::snowfall::core::JsonValue(22.2f);
```