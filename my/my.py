#!/usr/bin/python
# -*- coding: utf-8 -*-
#
#######################################################################################################################
#                                                   ,__ __                                                            #
#                                                  /|  |  |                                                           #
#                                                   |  |  |                                                           #
#                                                   |  |  |  |   |                                                    #
#                                                   |  |  |_/ \_/|/                                                   #
#                                                               /|                                                    #
#                                                               \|                                                    #
#######################################################################################################################
"""
my.py
-------------------------------------------------------------------
This script was created by Xuanming in 2022, thanks for your reading
Location: Host: python/lib/my.py
Statement: This Python package file support some basic obj/fun to us in Python2/3 environment
Usage:
     import my
     from my import *
"""


import os
import sys
import logging


# =====================================================================================================================
# Common Class
# =====================================================================================================================
class Logger(object):
    """
    提供标准的日志输出工具, 日志输出格式为 2022-02-22 22:22:22.222 INFO This is demo output.
    默认的:
        * DEBUG 及其以上级别的日志都是有效输出
        * INFO  及其以上级别的日志输出到日志文件
        * ERROR 及其以上级别的日志输出到终端
    """
    output = logging.getLogger()
    output.setLevel(logging.DEBUG)
    formatter = logging.Formatter(fmt='%(asctime)s.%(msecs)03d %(levelname)s %(message)s', datefmt='%Y-%m-%d %H:%M:%S')
    logfile = os.path.join(os.path.dirname(os.path.abspath('__file__')), 'log', 'xxxxxx.log')
    if not os.path.isdir(os.path.dirname(logfile)):
        os.makedirs(os.path.dirname(logfile))
    _x = logging.FileHandler(filename=logfile, mode='a', encoding='UTF-8')
    _x.setLevel(logging.INFO)
    _x.setFormatter(formatter)
    _y = logging.StreamHandler()
    _y.setLevel(logging.ERROR)
    _y.setFormatter(formatter)
    output.addHandler(_x)
    output.addHandler(_y)

    @staticmethod
    def debug(message=str):
        Logger.output.debug(message)

    @staticmethod
    def info(message=str):
        Logger.output.info(message)

    @staticmethod
    def warn(message=str):
        Logger.output.warn(message)

    @staticmethod
    def error(message=str):
        Logger.output.error(message)

class RaisePoint(Exception):
    """
    提供多层嵌套循环的循环跳出工具
    """
    def __str__(self):
        message = 'Function: ' + self.__class__.__name__ + '() Exception: ' + 'Escape from multiple nested loop'
        return message


# =====================================================================================================================
# Common Function
# =====================================================================================================================
def except_return_none(func):
    """
    捕获未知错误的装饰器
    """
    def wrapper(*args, **kwargs):
        try:
            return func(*args, **kwargs)
        except Exception as error:
            Logger.error('Function: ' + func.__name__ + '() Exception: ' + str(error))
            return None
    return wrapper

@except_return_none
def gbk_to_utf8(func):
    """
    转换 GBK 字符编码到 UTF-8 字符编码的装饰器
    """
    def wrapper(*args, **kwargs):
        meta = func(*args, **kwargs)
        for k, v in meta.items():
            if v is not None and type(v) is str and 'UTF' not in sys.stdin.encoding.upper():
                meta[k] = v.decode('GBK').encode('UTF-8')
        return meta
    return wrapper
