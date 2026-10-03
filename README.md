# minesync
A tool for syncing minecraft worlds across multiple devices.

## workflow
minesync is composed of two parts - a server and a client. 
- The **Server** is an HTTP server which servers as a central source of truth for all *clients*. Persistent data is stored here, and routed per request.
- The **Client** is an application which probes the server. So far, it has only two functions - uploading and syncing existing local saves.
This workflow provides a really simple and reliable system for persisting state.


## architecture
The server uses Crow routes for exposing API endpoints.
The client uses an MVP (Model, View, Presenter) pattern, and all client specifications must follow it.


### building

`cmake --build ./cmake-build --target [minesync_client/minesync_server] -j 6`
