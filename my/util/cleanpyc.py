#!/usr/bin/python
# -*- coding: utf-8 -*-
#
#######################################################################################################################
#                                           _                                                                         #
#                                          | |                                                                        #
#                                      __  | |  _   __,   _  _     _         __                                       #
#                                     /    |/  |/  /  |  / |/ |  |/ \_|   | /                                         #
#                                     \___/|__/|__/\_/|_/  |  |_/|__/  \_/|/\___/                                     #
#                                                               /|       /|                                           #
#                                                               \|       \|                                           #
#######################################################################################################################
"""
cleanpyc.py
-------------------------------------------------------------------
This script was created by Xuanming in 2022, thanks for your reading
Location: Host: project/cleanpyc.py
Statement: This Python script file clean every *.pyc files in project directory
Usage:
     $ python cleanpyc.py
"""


import os


# =====================================================================================================================
# Main Part
# =====================================================================================================================
if __name__ == '__main__':
     for prefix, dirs, files in os.walk(os.path.dirname(os.path.abspath('__file__'))):
          for name in files:
               if name.endswith('.pyc'):
                    filename = os.path.join(prefix, name)
                    os.remove(filename)
