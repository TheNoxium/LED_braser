#ifndef APP_DATABASE_H_
#define APP_DATABASE_H_

#include "main.hpp"

/**
 * @brief
 *
 */
class Configuration
{
public:
    Config_SISTEM config_SISTEM;
    Config_LOCAL_NETWORK config_LOCAL_NETWORK;

    Configuration();

    virtual ~Configuration();

    void get_configs();

    void get_station_config(void);
    void set_station_config(void);
    void default_station_config(void);

    void get_network_config(void);
    void set_network_config(void);
    void default_network_config(void);
};

#endif
