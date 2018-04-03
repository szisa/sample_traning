#!/usr/bin/env node
const request = require('request');

function ip(callback) {
    request('http://ip.sxisa.com/', (err, rsp, body) => {
        if (err) throw (err)
        if (callback) callback(body)
    })
}

module.exports = ip;

if (require.main === module) {
    ip(console.log);
}