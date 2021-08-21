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
* OTA pull support (Froy pulls new firmware from a specified location)
* TLS support (single fingerprint only)
* relatively easy to solder by hand (nothing smaller than an 0805 package)

## Flavors

Frøy currently comes in three flavors:

### Froy Outdoor

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-outdoor-pcb.png)

![](https://raw.githubusercontent.com/xrstf/froy/master/docs/images/froy-outdoor-inside.jpg)

This is the original project. It runs using a CR123 battery, which lasts roughly 3-5
months when reporting data every 15 minutes.

The case can be bought on Amazon: https://www.amazon.de/gp/product/B072M2JKGW/ -- I am not
aware of any alternative sources. In case the product disappears, I saved the schematics
in `docs/images/froy-outdoor-case-drawings.jpg`.

### Froy Indoor

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
