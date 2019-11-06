// Initialize Firebase
  const config = {
      apiKey: "*******",
      authDomain: "********",
      databaseURL: "*********",
      storageBucket: "*************"
  }

  firebase.initializeApp(config);

  //Get elements
  const preObject = document.getElementById('object');

  // Create references
  const dbRefObject = firebase.database().ref().child('2');

  // Sync object changes
  dbRefObject.on('value', (snap) => {
      var statusLampu = snap.val().StatusLampu;
      console.log(statusLampu);
      console.log(typeof statusLampu);
  });

// Global Variable
var status = "OFF";
document.getElementById("lamp").innerHTML = status;
document.getElementById("connection").innerHTML = "connected";
document.getElementById("on_off").innerHTML = status;

// Get data from firebase
var data;

function changeState() {
  if (status === "OFF") {
    status = "ON";
    document.querySelector("#lamp").style.background = "#be174f";

  } else {
    status = "OFF";
    document.querySelector("#lamp").style.background = "#c8dce2";
  }
  const dbUpObject = firebase.database().ref('2').child('Status');
  dbUpObject.set(status);
  document.getElementById("lamp").innerHTML = status;
  }
