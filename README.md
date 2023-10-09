##
# Qt_Weather_Station
Development of a project made for classes on Visualization of Sensory Data at WUST. Project of main application wrote in C++ with Qt5 library.

## Table of contents
<!-- - [costam](#costam) -->
- [Description](#description)
- [Data frame](#data-frame)
- [Visualization](#peripherials)
- [Dependiecies](#dependiecies)
- [Installation](#installation)
    - [Whole repo](#whole-repo)
    - [Main Qt APP](#main-qt-app)
    - [Weather Station on stm32-Nucleo476RG](#weather-station-on-stm32-nucleo476rg)
    - [Weather Station on ATmega328p](#weather-station-on-atmega328p)
- [Usage](#usage)

    
<!-- - [](#) -->

<!-- ## costam -->

## Description 
Project of a Weather Station visualisation data made for classes on Visualization of Sensory Data at WUST. It is a window application write in C++ using Qt5. Part of the project is weather station based on STM32 Nucleo-L476RG or ATmega328p. 

The application enables connection with MCU via USART. Data correctness is checked using the CRC8 checksum.


<!-- <sup>[1]</sup>, rain density<sup>[1]</sup>.  -->
<!-- <i><sup>[1]</sup> Based on Analog to Digital Converter.</i> -->

## Data Frame
- Usart using 9600 baudrate, and dataframe 8N1.

- Data that is send with USART has following structure: 
  - start character: '**A**',
  - spacebar character
  - sensors data separated with spacebar,
  - spacebar character
  - control sum: CRC8.



## Dependiecies
Tested on:
- **Ubuntu 20.04**,
- **Qt 5.12.8**,
- **QMake 3.1**.


## Installation
### Whole repo
Clone repo with:
 <pre>git clone https://github.com/KacSz123/Qt_Weather_Station</pre>

### Main Qt APP:
 <pre>git clone --branch master https://github.com/KacSz123/Qt_Weather_Station</pre>
 Import project into Qt Creator and build.


### Weather Station on stm32-Nucleo476RG
 Check branch: stm32L476RG_project

### Weather Station on ATmega328p
Check branch: ATmega328p_C_Code


## Usage 
TBA.