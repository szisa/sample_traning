#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
if sys.version_info.major == 3:
    from urllib.request import urlopen # Python 3
else:
    from urllib2 import urlopen        # Python 2


rsp = urlopen('http://ip.sxisa.com/')
print(rsp.read())