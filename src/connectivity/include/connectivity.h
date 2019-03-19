/*
 * IoT-Labs-2018 
 * Copyright (C) 2018 Massinissa Hamidi 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "phy_layer.h"
#include "net_layer.h"
#include "trans_layer.h"
#include "app_layer.h"

struct conn_config_t {
    enum MAC_PHY_interfaces phy_proto;
    enum net_protocols      net_proto;
    enum trans_protocols    trans_proto;
    int flag_ssl;
    enum app_protocols      app_proto;
};

void setup_connectivity(void *pvParameters);

