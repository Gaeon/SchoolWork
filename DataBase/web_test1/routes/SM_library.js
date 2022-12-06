var express = require('express');
var router = express.Router();

var mysqlDB = require('../mysqlDB');

/*
* 클라이언트로 부터 post 호출이 되었을때 아래의 코드를 수행
* req: 클라이언트 요청정보를 담은 객체
* res: 요청한 클라이어트로 응답을 위한 객체
* next: 다음 로직 수행을 위한 함수명
*/
router.post('/', function (req, res, next) {
    id=req.body.user_id
    //console.log(id)

    
    var query_string='select * from SMBookBorrowingHistory as BH join SMBookInfo as BI on BH.b_code=BI.b_code where u_id=?'
    mysqlDB.query(query_string,[id], function (err, rows, fields){

        if (!err) {                   
            console.log(rows)      
            res.render('user_library', {id:id, items:rows})

        } else {                        
            res.send('error : ' + err);
        }
    }); 
   

});


module.exports = router;