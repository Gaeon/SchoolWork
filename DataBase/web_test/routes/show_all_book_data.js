//express 모듈을 불러오고 라우팅 로직을 설정
var express = require('express');
var router = express.Router();

var mysqlDB = require('../mysqlDB')

/*
 * 클라이언트로 부터 get 호출이 되었을 때 아래의 코드를 수행
 * '/': 함수가 적용되는 경로(라우트)
 * req: 함수에 대한 HTTP 요청 인수
 * res: 함수에 대한 HTTP 응답 인수
 * next: 함수에 대한 콜백 인수
 */
router.get('/', function (req, res, next) {
    /*
    * mysql 쿼리 요청
    * sql: sql 쿼리문
    * values: sql 쿼리 요청 후 리턴 받은 값
    * err: mysql 쿼리 요청 중 오류가 있을 경우 저장되는 파라미터
    * rows: 쿼리 결과
    * fields: 테이블의 필드 정보
    */
    mysqlDB.query('select * from SMBookInfo', [], function (err, rows, fields) {
        if (!err) {         //오류가 없으면 웹 페이지에 값 출력
            console.log(rows);
            console.log(fields);

            //json형식으로 리턴된 값 저장
            var result = 'rows : ' + JSON.stringify(rows) + '<br><br>' +
                'fields : ' + JSON.stringify(fields);       // row: row info \n\n field: field info

            //클라이언트에 응답을 수행 -> 결과 값 출력
            res.send(result);

        } else {            //오류가 있으면 오류 코드 출력
            console.log('query error : ' + err);

            //클라이언트에 응답을 수행 -> 오류 코드 출력
            res.send(err);
        }
    });
});

module.exports = router;