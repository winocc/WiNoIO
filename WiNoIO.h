// WiNoIO.h
// 
/// \mainpage WiNoIO library for Arduino
/// 
/// @author Adrien van den Bossche <vandenbo@univ-tlse2.fr>
///
///
///


#ifndef WiNoIO_h
#define WiNoIO_h

#include "Arduino.h"

class WiNoIO {

	public:
		///
		/// @brief Transceiver enumeration
		///
		typedef enum {
			LED_TYPE_NO_LED=0,	///< @brief No RGB LED on the board
			LED_TYPE_NORMAL=1,	///< @brief Regular (positive) RGB LED
			LED_TYPE_REVERTED=2,	///< @brief Reverted (negative) RGB LED
		} led_type_e;

		typedef enum {
			TRX_TYPE_NO_TRX=0,	///< @brief No transceiver onboard
			TRX_TYPE_RFM22=1,	///< @brief HopeRF RFM22
			TRX_TYPE_DW1000=2,	///< @brief DW1000 based transceivers (DWM1000...)
			TRX_TYPE_RFM95=3,	///< @brief HopeRF RFM95
		} trx_type_e;

		///
		/// @brief The WiNoIO configuration struct
		///
		typedef struct {
			uint16_t label;			///< @brief Node label
			uint16_t antennaDelay;		///< @brief Antenna delay (DW1000 based transceivers)
			uint8_t ledType;		///< @brief RGB LED type
			uint8_t rgbLedRedPin;		///< @brief RGB LED Red pin
			uint8_t rgbLedGreenPin;		///< @brief RGB LED Green pin
			uint8_t rgbLedBluePin;		///< @brief RGB LED Blue pin
			uint8_t radioType;		///< @brief The onboard transceiver
			uint8_t trxSckPin;		///< @brief The transceiver SPI clock (SCK) pin
		} conf_t;

		///
		/// @brief WiNoIO Constructor
		///
		WiNoIO();

		///
		/// @brief Get the WiNoIO debug status enabled/disabled
		/// @return true if the WiNoIO debug is active, false otherwise
		///
		bool getDebug();

		///
		/// @brief Set the WiNoIO debug status enabled/disabled
		/// @param status the debug status
		///
		void setDebug(bool status);

		///
		/// @brief Read configuration from EEPROM
		/// @param conf a pointer to the conf_t 
		/// @return true if a valid configuration has been loaded from EEPROM
		///
		bool readConfig(conf_t *conf);

		///
		/// @brief Load current configuration from EEPROM
		/// @return true if a valid configuration has been loaded from EEPROM
		///
		bool loadConfig();

		///
		/// @brief Store given configuration in EEPROM
		/// @param conf a pointer to the conf_t 
		///
		void writeConfig(conf_t *conf);

		///
		/// @brief Store current configuration in EEPROM
		///
		void commitConfig();
		
		///
		/// @brief Get the label
		/// @return The label
		///
		uint16_t getLabel(void);

		///
		/// @brief Set the label
		/// @param label The label
		///
		void setLabel(uint16_t label);

		///
		/// @brief Get the trxSckPin
		/// @return The trxSckPin
		///
		uint8_t getTrxSckPin(void);

		///
		/// @brief Set the trxSckPin
		/// @param trxSckPin The trxSckPin
		///
		void setTrxSckPin(uint8_t trxSckPin);

		///
		/// @brief Set the current configuration
		///
		void setCurrentConfig (
				uint16_t label,
				uint16_t antennaDelay,
				uint8_t ledType,
				uint8_t rgbLedRedPin,
				uint8_t rgbLedGreenPin,
				uint8_t rgbLedBluePin,
				uint8_t radioType,
				uint8_t trxSckPin );
				
		///
		/// @brief dump the given configuration on Serial
		///
		void dumpConfig(conf_t *conf);

		///
		/// @brief dump the current configuration on Serial
		///
		void dumpCurrentConfig();

		///
		/// @brief print the given configuration on Serial
		///
		void printConfig(conf_t *conf);

		///
		/// @brief print the current configuration on Serial
		///
		void printCurrentConfig();

		///
		/// @brief Draw given color on RGB LED
		/// @param red the red color
		/// @param green the green color
		/// @param blue the blue color
		/// 
		bool rgbDraw(uint8_t red, uint8_t green, uint8_t blue);
		
	private:

		///
		/// @brief Builds a valid config with given parameters
		/// @return The decoded uint16_t
		/// 
		void makeConfig ( conf_t *conf,
				  uint16_t label,
				  uint16_t antennaDelay,
				  uint8_t ledType,
				  uint8_t rgbLedRedPin,
				  uint8_t rgbLedGreenPin,
				  uint8_t rgbLedBluePin,
				  uint8_t radioType,
				  uint8_t trxSckPin );


		///
		/// @brief Init the RGB LED
		/// 
		bool initRgbLedOutputs(void);


		conf_t currentConfig;		///< @brief The current configuration
		bool _debug;			///< @brief Debug flag

	protected:

};

#endif
