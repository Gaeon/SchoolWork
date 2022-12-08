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
    res.render('search');
});

/*
* 클라이언트로 부터 post 호출이 되었을때 아래의 코드를 수행
* req: 클라이언트 요청정보를 담은 객체
* res: 요청한 클라이어트로 응답을 위한 객체
* next: 다음 로직 수행을 위한 함수명
*/
router.post('/', function (req, res, next) {
    //html body로 부터 request 받은 변수
    var search_name = req.body['search_name'];

    /*
    * mysql 쿼리 요청
    * sql: sql 쿼리문
    * values: sql 쿼리 요청 후 리턴 받은 값
    * err: mysql 쿼리 요청 중 오류가 있을 경우 저장되는 파라미터
    * rows: 쿼리 결과
    * fields: 테이블의 필드 정보
    */
    mysqlDB.query('select * from SMBookInfo where b_name=?',[search_name], function (err, rows, fields){

        if (!err) {                         //오류가 없으면 웹 페이지에 값 출력
            if (rows[0]!=undefined) {       //row가 존재하면 책정보 출력
                
                //회원정보 각 변수에 저장
                var b_code=rows[0]['b_code'];
                var b_name=rows[0]['b_name'];
                var auther=rows[0]['auther'];
                var publisher=rows[0]['publisher'];
                //console.log(rows)
                            
                //리소스 보냄
                

                mysqlDB.query('select * from SMBookBorrowingHistory where b_code=?',[b_code], function (err, rows, fields){
                    if (!err) {                         //오류가 없으면 웹 페이지에 값 출력
                        if (rows[0]!=undefined) {       //row가 존재하면 책정보 출력
                            
                            //회원정보 각 변수에 저장
                            var return_day=rows[0]['return_day'];
                            var is_return=rows[0]['is_return'];
                            //console.log(rows)    
            
                            //리소스 보냄
                            res.send('찾으시는 책 정보는 다음과 같습니다 <hr><br>' +
                                     '코드:'+b_code+'<br>'+
                                     '제목:'+b_name+'<br>'+
                                     '저자:'+auther+'<br>'+
                                     '출판사:'+publisher+'<br><br>'+
                                     '대출 가능 여부:'+is_return+'<br>');            
                        } else{
                            res.send('찾으시는 책 정보는 다음과 같습니다 <hr><br>' +
                            '코드:'+b_code+'<br>'+
                            '제목:'+b_name+'<br>'+
                            '저자:'+auther+'<br>'+
                            '출판사:'+publisher+'<br><br>'+
                            '대출 가능 여부: Y<br>');
                        }
                    } else{
                        res.send('error : ' + err);
                    }
                });

            } else {                    //row가 없으면 no data 출력
                res.send(search_name + '에 대한 결과가 없습니다.');
            }

        } else {                        //오류가 있으면 오류코드 출력
            res.send('error : ' + err);
        }
    });

    // mysqlDB.query('select * from SMBookBorrowingHistory where b_code=(select b_code from SM_BookInfo where b_name=?)',[search_name], function (err, rows, fields){
    //     if (!err) {                         //오류가 없으면 웹 페이지에 값 출력
    //         if (rows[0]!=undefined) {       //row가 존재하면 책정보 출력
                
    //             //회원정보 각 변수에 저장
    //             var return_day=rows[0]['return_day'];
    //             var is_return=rows[0]['is_return'];
    //             //console.log(rows)    

    //             //리소스 보냄
    //             res.send('대출 가능 여부:'+is_return+'<br');

    //         } else{
    //             res.send('대출 가능 여부: Y<br>');
    //         }
    //     } else{
    //         res.send('error : ' + err);
    //     }
    // });

});

module.exports = router;