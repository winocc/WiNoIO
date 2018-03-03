// WiNoIO.cpp
// 

#include <EEPROM.h>
#include "WiNoIO.h"

///
/// @brief ...
///

WiNoIO::WiNoIO()
{
	_debug = false;
}

bool WiNoIO::readConfig(conf_t *conf)
{
	uint8_t confBytes[sizeof(conf_t)];
	
	if (   ( EEPROM.read(EEPROM.length()-1) == 0xFF )
	    || ( EEPROM.read(EEPROM.length()-sizeof(conf_t)) == 0xFF ) )
		return false;
	
	for (uint8_t i=0; i<sizeof(conf_t); i++)
		confBytes[i] = EEPROM.read(EEPROM.length()-1-i);
	memcpy(conf, confBytes, sizeof(conf_t));
	return true;
}

bool WiNoIO::loadConfig()
{
	bool ret = readConfig(&currentConfig);
	if ( ret ) 
	{
		initRgbLedOutputs();
	}
	return ret;
}

void WiNoIO::writeConfig(conf_t *conf)
{
	uint8_t confBytes[sizeof(conf_t)];
	memcpy(confBytes, conf, sizeof(conf_t));
	for (uint8_t i=0; i<sizeof(conf_t); i++)
		EEPROM.write(EEPROM.length()-1-i, confBytes[i]);
}

void WiNoIO::commitConfig()
{
	writeConfig(&currentConfig);
}

bool WiNoIO::getDebug()
{
	//if ( _debug ) Serial.println("WINOIO\t Get debug status");
	return _debug;
}

void WiNoIO::setDebug(boolean status)
{
	_debug = status;
	if ( _debug ) Serial.println("WINOIO\t debug set");
}

uint16_t WiNoIO::getLabel()
{
	return currentConfig.label;
}

void WiNoIO::setLabel(uint16_t label)
{
	currentConfig.label = label;
	if ( _debug ) Serial.println("WINOIO\t Node address set");
}

uint8_t WiNoIO::getTrxSckPin()
{
	return currentConfig.trxSckPin;
}

void WiNoIO::setTrxSckPin(uint8_t trxSckPin)
{
	currentConfig.trxSckPin = trxSckPin;
	if ( _debug ) Serial.println("WINOIO\t Node address set");
}

void WiNoIO::setCurrentConfig (	uint16_t label,
				uint16_t antennaDelay,
				uint8_t ledType,
				uint8_t rgbLedRedPin,
				uint8_t rgbLedGreenPin,
				uint8_t rgbLedBluePin,
				uint8_t radioType,
				uint8_t trxSckPin )
{
	makeConfig(&currentConfig, label, antennaDelay, ledType, rgbLedRedPin, rgbLedGreenPin, rgbLedBluePin, radioType, trxSckPin);
}

void WiNoIO::dumpConfig(conf_t *conf)
{
	uint8_t confBytes[sizeof(conf_t)];
	if ( _debug ) Serial.printf("WINOIO\t Dump WiNoIO configuration\t");
	memcpy(confBytes, conf, sizeof(conf_t));
	for (uint8_t i=0; i<sizeof(conf_t); i++) Serial.printf("%02x ", confBytes[i]);
	Serial.println();
}

void WiNoIO::dumpCurrentConfig()
{
	dumpConfig(&currentConfig);
}

void WiNoIO::printConfig(conf_t *conf)
{
	if ( _debug ) Serial.printf("WINOIO\t Print WiNoIO configuration\n");
	Serial.printf("label=0x%04x\n", conf->label);
	Serial.printf("antennaDelay=%d\n", conf->antennaDelay);
	Serial.printf("ledType=%d\n", conf->ledType);
	Serial.printf("rgbLedRedPin=%d\n", conf->rgbLedRedPin);
	Serial.printf("rgbLedGreenPin=%d\n", conf->rgbLedGreenPin);
	Serial.printf("rgbLedBluePin=%d\n", conf->rgbLedBluePin);
	Serial.printf("radioType=%d\n", conf->radioType);
	Serial.printf("trxSckPin=%d\n", conf->trxSckPin);
}

void WiNoIO::printCurrentConfig()
{
	printConfig(&currentConfig);
}

bool WiNoIO::rgbDraw(uint8_t red, uint8_t green, uint8_t blue)
{
	if ( currentConfig.ledType == LED_TYPE_NO_LED ) return false;
	if ( currentConfig.ledType == LED_TYPE_REVERTED )
	{
		// If color is 0, disable PWM and set HIGH level to fully disable the LED
		if ( red == 0 )
		{
			analogWrite(currentConfig.rgbLedRedPin, 0);
			digitalWrite(currentConfig.rgbLedRedPin, HIGH);
		}
		else analogWrite(currentConfig.rgbLedRedPin, 255-red);

		if ( green == 0 )
		{
			analogWrite(currentConfig.rgbLedGreenPin, 0);
			digitalWrite(currentConfig.rgbLedGreenPin, HIGH);
		}
		else analogWrite(currentConfig.rgbLedGreenPin, 255-green);
		
		if ( blue == 0 )
		{
			analogWrite(currentConfig.rgbLedBluePin, 0);
			digitalWrite(currentConfig.rgbLedBluePin, HIGH);
		}
		else analogWrite(currentConfig.rgbLedBluePin, 255-blue);
	}
	else
	{
		analogWrite(currentConfig.rgbLedRedPin, red);
		analogWrite(currentConfig.rgbLedGreenPin, green);
		analogWrite(currentConfig.rgbLedBluePin, blue);
	}
	return true;
}

void WiNoIO::makeConfig(conf_t *conf,
		  uint16_t label,
		  uint16_t antennaDelay,
		  uint8_t ledType,
		  uint8_t rgbLedRedPin,
		  uint8_t rgbLedGreenPin,
		  uint8_t rgbLedBluePin,
		  uint8_t radioType,
		  uint8_t trxSckPin )
{
	conf->label = label;
	conf->antennaDelay = antennaDelay;
	conf->ledType = ledType;
	conf->rgbLedRedPin = rgbLedRedPin;
	conf->rgbLedGreenPin = rgbLedGreenPin;
	conf->rgbLedBluePin = rgbLedBluePin;
	conf->radioType = radioType;
	conf->trxSckPin = trxSckPin;
}

bool WiNoIO::initRgbLedOutputs(void)
{
	if ( currentConfig.ledType == LED_TYPE_NO_LED ) return false;
	pinMode(currentConfig.rgbLedRedPin, OUTPUT);
	pinMode(currentConfig.rgbLedGreenPin, OUTPUT);
	pinMode(currentConfig.rgbLedBluePin, OUTPUT);
	rgbDraw(0,0,0);
	return true;
}
