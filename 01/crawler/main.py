#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
if sys.version_info.major == 3:
    from urllib.request import urlopen # Python 3
else:
    from urllib2 import urlopen        # Python 2


def ip():
    rsp = urlopen('http://ip.sxisa.com/')
    return rsp.read()

if __name__ == '__main__':
    print(ip())