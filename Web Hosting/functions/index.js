const path = require("path");
const functions = require("firebase-functions");
const firebase = require("firebase-admin");
const express = require("express");

const firebaseApp = firebase.initializeApp(functions.config().firebase);

const app = express();

// Use CSS files
app.use(express.static('view'));

// Use cache control and edge server
app.get("/", (request, response) => {
  response.sendFile(path.join(__dirname, '/view/', 'index.html'));
});

// Exports module
exports.app = functions.https.onRequest(app);
