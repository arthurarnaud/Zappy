var net = require('net');
var io = require('socket.io')();

var ZAPPY_SERVER_PORT = 4242;
var ZAPPY_SERVER_IP = '127.0.0.1';

var MW_SERVER_PORT = 3000;

var client = new net.Socket();
const WebSocket = require('ws');

// Websocket Server
var wss;

// History Management
var tnas = [];
var players = [{}];
var msz = "msz 10 10";
var gameMap = [
    []
];

var symbolsTab = {

    "msz": function(args) {
        var params = args.split(" ");

        var sizeX = params[1];
        var sizeY = params[2];

        // Re-init the game map
        gameMap = [];
        for (var y = 0; y < sizeY; ++y) {
            gameMap[y] = [];
            for (var x = 0; x < sizeX; ++x) {
                gameMap[y][x] = "";
            }
        }

        msz = args;
    },

    "bct": function(args) {
        var params = args.split(" ");

        if (params.length === 10) {
            gameMap[params[2]][params[1]] = args;
        }
    },

    "tna": function(args) {
        if (tnas.indexOf(args) < 0) {
            tnas.push(args);
        }
    },

    "ppo": function(args) {
        var params = args.split(" ");

        if (!players.find((e) => { return e.id == params[1]; })) {
            players.push({
                'id': params[1],
                'X': params[2],
                'Y': params[3],
                'O': params[4],
                'L': 1,
                'food': 0,
                'linemate': 0,
                'deraumere': 0,
                'sibur': 0,
                'mendiane': 0,
                'phiras': 0,
                'thystame': 0,
            });
        } else {
            players.find((e) => { return e.id == params[1]; }).X = params[2];
            players.find((e) => { return e.id == params[1]; }).Y = params[3];
            players.find((e) => { return e.id == params[1]; }).O = params[4];
        }
    },

    "pin": function(args) {

        var params = args.split(" ");

        players.find((e) => {
            if (e.id == params[1]) {
                e.X = params[2];
                e.Y = params[3];
                e.food = params[4];
                e.linemate = params[5];
                e.deraumere = params[6];
                e.sibur = params[7];
                e.mendiane = params[8];
                e.phiras = params[9];
                e.thystame = params[10];
                return true;
            }
            return false;
        });
    }

};

// Send History to new client
function getHistoryAsString() {
    var data = "";

    // MSZ
    data += msz + '\n';
    // BCT
    gameMap.forEach((line) => {
        line.forEach((e) => {
            data += e + '\n';
        });
    });
    // TNA
    tnas.forEach((e) => {
        data += e + '\n';
    });
    // PPOS
    players.forEach((e) => {

        data += ("pin " +
            e.id + " " +
            e.X + " " +
            e.Y + " " +
            e.food + " " +
            e.linemate + " " +
            e.deraumere + " " +
            e.sibur + " " +
            e.mendiane + " " +
            e.phiras + " " +
            e.thystame + '\n');
    });
    return data;
}

client.connect(ZAPPY_SERVER_PORT, ZAPPY_SERVER_IP, function() {
    console.log('[ZappyServer] Connected');

    // Notify the server that we are a graphic client
    client.write('GRAPHIC\n');

    // Start listening for socketIO clients
    wss = new WebSocket.Server({ port: MW_SERVER_PORT });

    wss.on('connection', function connection(ws, req) {

        // Notify in console that a new customer has logged in
        console.log("New client connected from " + req.connection.remoteAddress);

        ws.send(getHistoryAsString());

    });

    wss.on('disconnect', function() {
        console.log('[WebSocket] Client disconnected');
    });

});

// Parsing data
var parseData = function(data) {

    var lines = data.split("\n");

    lines.forEach((e) => {

        var sym = e.substr(0, e.indexOf(" "));

        if (sym in symbolsTab) {
            symbolsTab[sym](e);
        }

    });

};

// ZappyServer middleware
client.on('data', function(data) {

    var datastr = String.fromCharCode.apply(null, new Uint16Array(data));

    // Parse data
    console.log("data: " + datastr);
    parseData(datastr);

    // Send data to all clients
    wss.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send(datastr);
        }
    });

});

// ZappyServer close handler
client.on('close', function() {
    console.log('[ZappyServer] Connection closed');
});