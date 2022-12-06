//express 모듈을 불러오고 라우팅 로직을 설정
var express = require('express');
var router = express.Router();

//mysql_db.js파일의 연결 정보를 mysqlDB 객체에 할당
var mysqlDB = require('../mysqlDB');

/*
* 클라이언트로 부터 get 호출이 되었을때 아래의 코드를 수행
* req: 클라이언트 요청정보를 담은 객체
* res: 요청한 클라이어트로 응답을 위한 객체
* next: 다음 로직 수행을 위한 함수명
*/
router.get('/', function (req, res, next) {   
    res.render('login');

});

/*
* 클라이언트로 부터 post 호출이 되었을때 아래의 코드를 수행
* req: 클라이언트 요청정보를 담은 객체
* res: 요청한 클라이어트로 응답을 위한 객체
* next: 다음 로직 수행을 위한 함수명
*/
router.post('/', function (req, res, next) {

    //html body로 부터 request 받은 변수
    var user_id = req.body['user_id'];
    var user_pw = req.body['user_pw'];

    /*
    * mysql 쿼리 요청
    * sql: sql 쿼리문
    * values: sql 쿼리 요청 후 리턴 받은 값
    * err: mysql 쿼리 요청 중 오류가 있을 경우 저장되는 파라미터
    * rows: 쿼리 결과
    * fields: 테이블의 필드 정보
    */
    mysqlDB.query('select * from SMBookAccount where u_id=? and u_pw=?',[user_id, user_pw], function (err, rows, fields){

        if (!err) {                         //오류가 없으면 웹 페이지에 값 출력
            if (rows[0]!=undefined) {       //row가 존재하면 회원정보 출력
                
                //회원정보 각 변수에 저장
                var id=rows[0]['u_id'];
                var name=rows[0]['u_name'];
                var phone=rows[0]['phone'];
                //console.log(rows)
                
                
                //리소스 보냄
                res.send(id+'님 환영합니다. <hr><br>' +
                    '회원님의 정보는 아래와 같습니다.<br>'+
                    'id:'+id+'<br>'+
                    'name:'+name+'<br>'+
                    'phone:'+phone+'<br>');
                


            } else {                    //row가 없으면 no data 출력
                res.send('로그인에 실패하였습니다.');
            }

        } else {                        //오류가 있으면 오류코드 출력
            res.send('error : ' + err);
        }

    });
});

module.exports = router;