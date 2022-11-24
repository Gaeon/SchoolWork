var mysqlDB = require('mysql');

var connection = mysqlDB.createConnection({
    host: 'mm.konkuk.ac.kr',
    post: '3306',
    user: 'user_202012333',
    password: '202012333',
    database: 'user_202012333'
});

module.exports = connection;
