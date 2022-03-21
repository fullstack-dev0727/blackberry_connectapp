/*
 * StatusEventHandler.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: petarvasilev
 */
#include "StatusEventHandler.h"

#include <bps/bps.h>
#include <bps/netstatus.h>
#include <bps/locale.h>

StatusEventHandler::StatusEventHandler()
{
    subscribe(netstatus_get_domain());
    subscribe(locale_get_domain());

    bps_initialize();

    netstatus_request_events(0);
    locale_request_events(0);
}

StatusEventHandler::~StatusEventHandler()
{
    bps_shutdown();
}

void StatusEventHandler::event(bps_event_t *event) {
    bool status = false;
    const char* language = "";
    const char* country = "";
    const char* locale = "";
    const char* interface = "";
    const char* type = "none";

    if (bps_event_get_domain(event) == netstatus_get_domain()) {
        if (NETSTATUS_INFO == bps_event_get_code(event)) {
            netstatus_info_t *info = netstatus_event_get_info(event);
            if (info)
            {
                status = netstatus_info_get_availability(info);
                interface = netstatus_info_get_default_interface(info);

                netstatus_interface_details_t *details;

                int success = netstatus_get_interface_details(interface, &details);
                if (success == BPS_SUCCESS) {
                    switch (netstatus_interface_get_type(details)) {

                    case NETSTATUS_INTERFACE_TYPE_UNKNOWN:
                        type = "Unknown";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_WIRED:
                        type = "Wired";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_WIFI:
                        type = "Wi-Fi";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_BLUETOOTH_DUN:
                        type = "Bluetooth";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_USB:
                        type = "USB";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_VPN:
                        type = "VPN";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_BB:
                        type = "BB";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_CELLULAR:
                        type = "Cellular";
                        break;

                    case NETSTATUS_INTERFACE_TYPE_P2P:
                        type = "P2P";
                        break;
                    }
                }

                netstatus_free_interface_details(&details);
                emit networkStatusUpdated(status, type);
            }
        }
    } else if (bps_event_get_domain(event) == locale_get_domain()) {
        if (LOCALE_INFO == bps_event_get_code(event)) {
            language = locale_event_get_language(event);
            country = locale_event_get_country(event);
            locale = locale_event_get_locale(event);
            emit localeUpdated(language, country, locale);
        }
    }
}
