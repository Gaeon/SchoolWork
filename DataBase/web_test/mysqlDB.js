//mysql 모듈 불러오기
var mysqlDB = require('mysql');

//DB 연결 정보
var connection = mysqlDB.createConnection({
    host: 'mm.konkuk.ac.kr',
    post: '3306',
    user: 'user_20201233',
    password: '202012333',
    database: 'user_202012333'
});

//mysql 모듈 내보내기
module.exports = connection;
