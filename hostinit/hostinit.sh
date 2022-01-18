#!/bin/bash
# -*- coding: utf-8 -*-
#
#######################################################################################################################
#                                         ,                                                                           #
#                                        /|   |             o          o                                              #
#                                         |___|  __   , _|_     _  _     _|_                                          #
#                                         |   |\/  \_/ \_|  |  / |/ |  |  |                                           #
#                                         |   |/\__/  \/ |_/|_/  |  |_/|_/|_/                                         #
#                                                                                                                     #
#                                                                                                                     #
#######################################################################################################################
#
# hostinit
# -------------------------------------------------------------------
# This script was created by Xuanming in 2022, thanks for your reading
# Location: Host: /srv/hostinit/hostinit.sh
# Statement: This command could initialize virtual host in public cloud environment
# Usage:
#     $ sh hostinit.sh [option...]



# =====================================================================================================================
# Load Environment
# =====================================================================================================================
source /etc/init.d/functions
source /etc/profile
if [[ ${?} != 0 ]]; then
    action "Load host environment" /bin/false
    exit 1
fi

/usr/bin/getopt -T &> /dev/null
if [[ ${?} != 4 ]]; then
    action "Load /usr/bin/getopt command" /bin/false
    exit 1
fi



# =====================================================================================================================
# Define Function
# =====================================================================================================================
function usage() {
    /usr/bin/echo -e ""
    /usr/bin/echo -e "Usage: \033[33;1mhostinit [option...]\033[0m"
    /usr/bin/echo -e "    --directory /path/to/dir        directory prefix for business"
    /usr/bin/echo -e "    --domain ipaddr,...             nameservers in /etc/sysconfig/network-scripts/ifcfg-eth0"
    /usr/bin/echo -e "    --env environment               environment tag code in PS1"
    /usr/bin/echo -e "    --host hostname                 hostname for virtual host"
    /usr/bin/echo -e "    --string str                    welcome string for user session"
    /usr/bin/echo -e "    --help                          show this help information"
    /usr/bin/echo -e "    --version                       show this command version information"
    /usr/bin/echo -e ""
    exit 0
}

function version() {
    /usr/bin/echo -e ""
    /usr/bin/echo -e "command version: alpha 1.0.0"
    /usr/bin/echo -e "created by FuXuanming (waitspring)"
    /usr/bin/echo -e ""
    exit 0
}