#include "abstract_medium.h"

/**
 * @class Abstract_Medium
 * @details Abstract class for all medium classes
 * like network, bluetooth, or usb.
 */

Abstract_Medium::Abstract_Medium()
{
    is_connected = false;
    is_open = false;
}

/**
 * @brief Wifi_Connection::Is_Open
 * @return true if medium is open
 */

bool Abstract_Medium::Is_Open()
{
    return is_open;
}

/**
 * @brief Wifi_Connection::Is_Connected
 * @return true if medium is connected in client
 */

bool Abstract_Medium::Is_Connected()
{
    return is_connected;
}