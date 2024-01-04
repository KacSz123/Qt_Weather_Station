##
# Qt_Weather_Station
Development of a project made for classes on Visualization of Sensory Data at WUST. Project on STM32 Nucleo-L476EG.

## Table of contents
<!-- - [costam](#costam) -->
- [Description](#description)
- [Sensors](#sensors)
- [Peripherials](#peripherials)
- [Dependiecies](#dependiecies)
- [Installation](#installation)
- [](#)

<!-- ## costam -->

## Description 
Project of a Weather Station based on stm32 Nucleo-L476RG. Device collects data about: temperature, pressure, rain density, luminosity. Project uses Serial  interface to communicate with PC (data correctness is checked with CRC8).


<!-- <sup>[1]</sup>, rain density<sup>[1]</sup>.  -->
<!-- <i><sup>[1]</sup> Based on Analog to Digital Converter.</i> -->

## Sensors
- Temperature and Pressure: **BMP280** <i>(future BMPX80)</i> --> I<i><sup>2</sup>C interface.
- Rain Density: **FC-37** electrode pad and **YL-38 LM393** converter module.
- Luminosity: **voltage divider with photoresistor**.

## Peripherials
Peripherials description can be find in **Qt_Weather_Station.pdf** file.

## Dependiecies
Tested on **Ubuntu 20.04** and **STM32CubeIDE 1.6.0**.


## Installation

1. Clone repo branch with:
 <pre>git clone --branch stm32L476RG_project https://github.com/KacSz123/Qt_Weather_Station</pre>

2. Import project into STM32CubeIDE:
    File --> Import --> General --> Import an Existing STM32CubeMX Configuration File (.ioc) --> Insert: Qt_Weather_Station.ioc.

3. Compile and load into MCU.