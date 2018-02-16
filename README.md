# WiNoIO
WiNoIO enables simple I/O (Input/Output) manipulation on the *WiNo* (DecaWiNo, TeensyWiNo...) boards. The board configuration and and mapping are stored in the non-volatile memory (EEPROM). 

Once configuration has been loaded, WiNoIO enables simple usage of the LED, getting node label to use it as an address, etc. 

## Typical Usage

Include library:

    #include <WiNoIO.h>
    WiNoIO wino;

In setup, call `loadConfig()` method to load configuration from EEPROM. You can block the sketch execution if a valid configuration has not been founded in EEPROM:  

    if (!wino.loadConfig() ) while (1);

To get the label:

    uint16_t label = wino.getLabel();

To use the RGB LED:

    wino.rgbDraw(128,128,0); // Red, Green, Blue. Here: Red+Green=Yellow

## Store Configuration

To store the board configuration, use the board-corresponding example in the examples directory.
