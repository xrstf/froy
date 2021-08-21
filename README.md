# Frøy - ESP8266+BME Hygrometer

This repository contains the source code, schematics and everything else for my
personal fancy homegrown hygrometer (sensor that reports temperature, humidity and
pressure).

## Features

* push or pull mode
* supports BME280, BME680 and BMP280 chips
* programming via USB (only for indoor variant, others need a standalone USB->UART converter)
* webserver with Prometheus compatible `/metrics` endpoint
* reconfiguration via USB or WiFi (i.e. `curl -XPOST -d'{"new":"config"}' http://device/`)
* OTA pull support (Frøy pulls new firmware from a specified location)
* TLS support (single fingerprint only)
* relatively easy to solder by hand (nothing smaller than an 0805 package)

## Mode of Operation

Both indoor and outdoor versions can work in one of two modes:

* **Pull Mode** ("server mode") -- in this mode, Frøy is constantly running and connected
  to your WiFi. It provides an HTTP server and expects you to fetch the data whenever
  you need it (for example via Prometheus).
* **Push Mode** -- in this mode, Frøy will make a measurement, connect to WiFi, send out the
  data to a preconfigured URL and then go to sleep for a configurable amount of time. Rinse
  and repeat.

The advantage of the Pull Mode is that the interval can be centralled controlled (if you have
multiple devices). It also makes it easier to trigger an OTA, as Frøy is constantly listening
for requests.

The advantage of the Push Mode is that Frøy doesn't need any Firewall rules to be reachable
and it saves power (critical for the Outdoor version). Also, indoor versions in Pull Mode would
considerable heat up (an ESP8266 that is connected to WiFi can be 35-40°C) and skew the sensor
readings. So even for indoor versions it is advisable to use Push Mode instead.

While Frøy is not reachable in Push Mode (it never starts a webserver and you'd be pretty luck
to send a request to it the moment it wakes up and before it goes back to sleep), it is still
possible to reconfigurable Frøy remotely by putting the new configuration in the _response_ to
Frøy's push request.

## Flavors

Frøy currently comes in three flavors:

### Frøy Outdoor

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-outdoor-pcb.png)

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-outdoor-inside.jpg)

This is the original project. It runs using a CR123 battery, which lasts roughly 3-5
months when reporting data every 15 minutes.

The case can be bought on Amazon: https://www.amazon.de/gp/product/B072M2JKGW/ -- I am not
aware of any alternative sources. In case the product disappears, I saved the schematics
in `docs/images/froy-outdoor-case-drawings.jpg`.

### Frøy Indoor

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-indoor-pcb.png)

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-indoor.jpg)

This variant is powered by USB and suitable for indoor use.

### Froy ForMen

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-formen-pcb.png)

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-formen-top.jpg)

This variant is powered by mains voltage and is suitable for locations where changing
the battery regularly is not desirable.

The case can be bought on Amazon, for example https://www.amazon.de/gp/product/B07B9KY9X4/ --
alternatively search for "Snowsound case" on your favorite search engine.

---

Frøy was named after the character in the NRK series ["Norsemen"](https://tv.nrk.no/serie/vikingane).
