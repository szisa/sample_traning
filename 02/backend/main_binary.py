#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pickle
import os
import sys
import time
from random import random

save_path = 'data.bin'

def set_name(data):
    print('请输入你的名字：')
    data['name'] = raw_input().decode(sys.stdin.encoding)
    return save(data)

def guess(data):
    name = data['name']
    rand_number = int(random() * 1000 + 1)
    guess_number = 0
    count = 0
    start = int(time.time())

    print('请输入1~1000的数字：')
    while rand_number != guess_number:
        guess_number = input()
        if guess_number < rand_number:
            print('小了')
        elif guess_number > rand_number:
            print('大了')
        count += 1
    cost = int(time.time() - start)
    print('恭喜你！猜中了！你一共猜测了{}次'.format(count))


    if not name:
        print('这是你第一次玩猜数字。')
        data = set_name(data)
        
    data['records'].append({
        'name': data['name'],
        'number': rand_number,
        'count': count,
        'start': start,
        'cost': cost
    })
    return data

def load(path):
    data = {
        'name': '',
        'records': []
    }
    if os.path.exists(path):
        with open(path, 'r') as fp:
            data = pickle.load(fp)
    return data

def save(data):
    with open(save_path, 'w') as fp:
        pickle.dump(data, fp)
    return data

def view(data):
    if data['records']:
        print('姓名\t所猜数字\t猜测次数\t花费秒数\t开始时间')
        for record in data['records']:
            print(u'{name}\t{number}\t\t{count}\t\t{cost}\t\t{start}'.format(
                name = record['name'],
                number = record['number'],
                count = record['count'],
                cost = record['cost'],
                start=time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(record['start']))
            ))
    else:
        print('你还没有玩过呢。')
    print('')
    return data

def menu(name):
    if name:
		print(u'你好！{name}！'.format(name=name))
    print('欢迎来玩『 猜数字 』!')
    print('')
    print('1. 开始游戏！')
    print('2. 查看历史！')
    print('3. 更改昵称!')
    print('4. 退出游戏！')
    print('')

    return raw_input()


def main():
    data = load(save_path)
    fun_dict = {
        '1': lambda: save(guess(data)),
        '2': lambda: view(data),
        '3': lambda: set_name(data),
        '4': exit
    }
    while True:
        cmd = menu(data['name'])
        fun = fun_dict.get(cmd, None)
        if fun:
            data = fun()

if __name__ == '__main__':
    main()