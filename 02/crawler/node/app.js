#!/usr/bin/env node
const request = require('request');
const { JSDOM } = require('jsdom');

function ip(callback) {
    request('http://www.myip.cn/', (err, rsp, body) => {
        if (err) throw (err)
        const window = new JSDOM(rsp.body).window;
        const document = window.document;
        // 获取所有的 font 标签
        let fonts = document.getElementsByTagName('font');
        // 过滤出包含IP的标签
        let ipElem = Array.from(fonts).filter(f => f.textContent.indexOf('您的IP') >= 0)[0] || { textContent: '' };
        // 过滤出包含电信运营商的标签
        let telecomElem = Array.from(fonts).filter(f => f.textContent.indexOf('来自') >= 0)[0] || { textContent: '' };

        // 取出标签文本
        let ip = ipElem.textContent.trim();
        let telecom = telecomElem.textContent.trim();

        // 根据文本特征提取关键内容
        ip = ip.slice(ip.indexOf(':') + 1).trim();
        telecom = telecom.slice(telecom.indexOf(':') + 1, telecom.indexOf('.')).trim();

        if (callback) callback({
            ip: ip,
            telecom: telecom
        })
    })
}

module.exports = ip;

if (require.main === module) {
    ip(info => console.log('IP:', info.ip, '运营商：', info.telecom));
}