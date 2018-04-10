#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests
from bs4 import BeautifulSoup

def get_html(url, encoding='utf-8'):
    rsp = requests.get(url)
    return rsp.content.decode(encoding)

def analyze(html):
    return BeautifulSoup(html, 'lxml')

def main():
    html = get_html('http://www.myip.cn/')
    document = analyze(html)
    fonts = document.find_all('font')
    my_ip = 'not found'
    telecom = 'not found'
    for font in fonts:
        innerText = font.get_text().strip()
        if innerText.find(u'您的IP') >= 0:
            my_ip = innerText[innerText.find(':') + 1:].strip()
        elif innerText.find(u'来自') >= 0:
            telecom = innerText[innerText.find(':') + 1:innerText.find('.')].strip()

    print(u'IP: {ip} \n运营商: {telecom}'.format(ip=my_ip, telecom=telecom))
    
if __name__ == '__main__':
    main()