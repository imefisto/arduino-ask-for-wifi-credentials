#ifndef HTML_H
#define HTML_H

#include "Arduino.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h1>Select a wifi</h1>
  <form id="wifi" method="post" action="/connect">
    <select id="networks" name="ssid" placeholder="Select SSID" />
    <input type="password" name="password" placeholder="Enter password" />
    <input id="connect-button" type="submit" value="Connect" />
  </form>

  <script>
  function startScan() {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 202) {
        addNetworks();
      }
    };

    xhr.open("POST", "/scan", true);
    xhr.send();
  }

  function addNetworks() {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var networks = JSON.parse(this.responseText);
        var select = document.getElementById("networks");
        for (var i = 0, len = networks.length; i<len; i++) {
          select.options.add(new Option(networks[i]));
        }
      } else if (this.readyState == 4 && this.status == 202) {
        addNetworks();
      }
    };
    xhr.open("GET", "/networks", true);
    xhr.send();
  }

  startScan();

  var form_el = document.getElementById("wifi");
  var connectButton = document.getElementById("connect-button");

  function startConnection(evt) {
    evt.preventDefault();

    connectButton.value = "Connecting";
    connectButton.setAttribute("disabled", true);

    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/connect", true);
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
    xhr.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 202) {
        checkIfConnected(0);
      }
    };

    var data = new URLSearchParams({
      ssid: form_el["ssid"].value,
      password: form_el["password"].value
    });

    xhr.send(data);
  }

  form_el.addEventListener("submit", startConnection);

  function checkIfConnected(attempt) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var response = JSON.parse(this.responseText);
        if (response.status == "connected") {
          setStatusAndEnableForm("Connected");
        } else if (attempt < 20) {
          setTimeout(checkIfConnected.bind(this, attempt + 1), 1000);
        } else {
          setStatusAndEnableForm("Not connected");
        }
      }
    }

    xhr.open("GET", "/connected", true);
    xhr.send();
  }

  function setStatusAndEnableForm(message) {
    alert(message);
    connectButton.value = "Connect";
    connectButton.removeAttribute("disabled");
  }
  </script>
</body>
</html>
)rawliteral";

#endif
