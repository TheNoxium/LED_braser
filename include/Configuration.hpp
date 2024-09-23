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
    Config_HP config_HP;

    Configuration();

    virtual ~Configuration();

    void get_configs();

    void get_station_config(void);
    void set_station_config(void);
    void default_station_config(void);
};

#endif
