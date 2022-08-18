#!/usr/bin/python
# -*- coding: utf-8 -*-
#
#######################################################################################################################
#                                                 ,__ __          __                                                  #
#                                                /|  |  |        /  )                                                 #
#                                                 |  |  |          /                                                  #
#                                                 |  |  |  |   |  /                                                   #
#                                                 |  |  |_/ \_/|//___                                                 #
#                                                             /|                                                      #
#                                                             \|                                                      #
#######################################################################################################################
"""
my2.py
-------------------------------------------------------------------
This script was created by Xuanming in 2022, thanks for your reading
Location: Host: python/lib/my2.py
Statement: This Python package file support some basic obj/fun to us in Python2 environment
Usage:
     import my2
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
    pass


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
    """
    def wrapper(*args, **kwargs):
        meta = func(*args, **kwargs)
        for k, v in meta.items():
            if v is not None and type(v) is str and 'UTF' is not in sys.stdin.encoding.upper():
                meta[k] = v.decode('GBK').encode('UTF-8')
        return meta
    return wrapper
