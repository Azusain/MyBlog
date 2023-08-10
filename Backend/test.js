const http = require('http');

const body = 'a'.repeat(1500);
const options = {
  hostname: 'localhost',
  port: 8080,
  path: '/',
  method: 'GET',
  headers: {
    'Content-Length': Buffer.byteLength(body)
  }
};

const req = http.request(options, res => {
  console.log(`状态码: ${res.statusCode}`);

  res.on('data', d => {
    process.stdout.write(d);
  });
});

req.on('error', error => {
  console.error(error);
});

req.write(body);
req.end();
