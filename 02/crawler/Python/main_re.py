#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests
import re

def get_html(url, encoding='utf-8'):
    rsp = requests.get(url)
    return rsp.content.decode(encoding)

def main():
    html = get_html('http://www.myip.cn/')
    ip_match = re.search(ur'您的IP地址:\s*(?P<IP>(\d{1,3}\.){3}\d{1,3})', html)
    telecom_match = re.search(ur'来自:\s*(?P<telecom>[^.]*?)\.', html)
    
    if ip_match:
        my_ip = ip_match.group('IP')
    else:
        my_ip = 'not found'
        
    if telecom_match:
        telecom = telecom_match.group('telecom')
    else:
        telecom = 'not found'

    print(u'IP: {ip} \n运营商: {telecom}'.format(ip=my_ip, telecom=telecom))
    
if __name__ == '__main__':
    main()