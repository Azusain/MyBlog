const http = require('http');

const body = 'a'.repeat(1500);
const options = {
    hostname: 'localhost',
    port: 8080,
    path: '/columns/topic_1',
    method: 'GET',
    headers: {
        'Content-Length': Buffer.byteLength(body),
        'token': 'QWEwMjAxsMTE=',
    }
};

const req = http.request(options, res => {
    console.log(`状态码: ${res.statusCode}`);
    console.log(`响应头: ${JSON.stringify(res.headers)}`);

    res.on('data', d => {
        process.stdout.write(d);
    });
});

req.on('response', response => {
    console.log(`响应报文: ${response.rawHeaders}`);
});

req.on('error', error => {
    console.error(error);
});

req.write(body);
req.end();
