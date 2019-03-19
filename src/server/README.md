# Simple TCP server
`index.js` contains a simple TCP server which is configured to listen for connections on port 3000. It is only capable of printing incomming requests and is useful for debugging.

## Prerequesties
* `nodejs`
* `npm` (optional but recommended)

## Run
In order to run the server at address `0.0.0.0` on port `3000`, use `node` command followed by the main file containing the server:

```
node index.js
```

# JSON server
for more information, take a look at [`json-server`](https://github.com/typicode/json-server)

## Install
You can install `json-server` via node package manager (`npm`):
```
npm install -g json-server
```

## Run
Using a toy database, `db.json` which is provided, you can get a fake REST API by running the following command:

```
json-server --watch db.json
```
