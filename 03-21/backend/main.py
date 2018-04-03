#!/usr/bin/env python
# -*- coding: utf-8 -*-

from random import random

def main():
    rand_number = int(random() * 1000 + 1)
    guess_number = 0
    count = 0

    print('请输入1~1000的数字：')
    while rand_number != guess_number:
        guess_number = input()
        if guess_number < rand_number:
            print('小了')
        elif guess_number > rand_number:
            print('大了')
        count += 1
    print('恭喜你！猜中了！你一共猜测了{}次'.format(count))


if __name__ == '__main__':
    main()