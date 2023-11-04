#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#pragma comment (lib, "libmysql.lib")

#define MYSQLUSER "root"//유저 이름
#define MYSQLPASSWORD "dgu1234!"//비밀번호
#define MYSQLIP "localhost"//연결할 ip 자기자신은 localhost 아니면 ipconfig로 자신의 ip를 친다.
//localhost는 다른컴퓨터로 하면 연결이 안된다. 배포할때 주의

//저희 팀은 비밀번호는 비밀키라 따로 설정하지 않았습니다. 그래서 이번 과제에서 로그인 및 회원가입 과정에 비밀번호 입력은 일부러 안넣었습니다. 
// 이 점 참고해서 봐주시면 정말 감사하겠습니다.

void loadmysql(char mysqlip[], MYSQL* cons)//MYSQL 서버 불러오는 메소드
{
    if (cons == NULL) //cons가 초기화를 못했으면
    {
        fprintf(stderr, "%s\n", mysql_error(cons));//에러 프린트, printf("%s")와 같음
        Sleep(1000);
        exit(1);
    }

    if (!(mysql_real_connect(cons, mysqlip, MYSQLUSER, MYSQLPASSWORD, NULL, 0, NULL, 0) == NULL)) //mysql서버로 연결 성공시
    {
        mysql_set_character_set(cons, "euckr");//MySQL 문자를 지정한다. 만약 안하면 한글이 짤림.
    }

    else //mysql 연결 실패시
    {
        fprintf(stderr, "연결 오류 : %s\n", mysql_error(cons));
        getchar();
    }
    return;
}

void finish_with_error(MYSQL* conn) //에러 처리 함수
{
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int main(void)
{

    MYSQL* conn = mysql_init(NULL);//MYSQL 연결 초기화.
    loadmysql(MYSQLIP, conn);

    //we used DB Coupang1

    char* qry_check; //id 체크용 변수
    char qry[200]; // sprint 저장값id,휴대폰 번호,이메일,이름 값 저장
    char* qry_storage;  ///

    char id[20];//sql문에서 varchar(20)으로 설정했기에

    char check_id[20];//sql문에서 varchar(20)으로 설정했기에

    int field;

    int correct = 0;

    MYSQL_RES* res;
    MYSQL_ROW row;



    if (mysql_query(conn, "USE Coupang1"))
    {

        printf("%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }    
    printf("\n\n");
    printf("\t\t ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("\t\t|                COUPANG               |\n");
    printf("\t\t ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

    printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-\n");

    printf("\t\t|\t\t");
    printf("1.회원가입");
    printf("\t\t|\n");

    printf("\t\t|\t\t");
    printf("2.로그인");
    printf("\t\t|\n");


    printf("\t\t|\t\t");
    printf("3.웹페이지 종료");
    printf("\t\t|\n");
    printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-\n");


    int selecting;
   
    printf("\t\t Select the number what you want :");
    scanf("%d", &selecting);

        if (selecting == 1) //회원가입 창
        {
            system("cls");
            same_id:
         
            char phone_number[20]; //sql문에서 varchar(20)으로 설정했기에
            char email[80]; //sql문에서 varchar(80)으로 설정했기에
            char name[20]; //sql문에서 varchar(20)으로 설정했기에

            char* qry_check; //id 체크용 변수
            char qry[200]; // sprint 저장값id,휴대폰 번호,이메일,이름 값 저장
            char* qry_storage;  ///

            char id[20];//sql문에서 varchar(20)으로 설정했기에

            char check_id[20];//sql문에서 varchar(20)으로 설정했기에

            int field;

            int correct = 0;

            MYSQL_RES* res;
            MYSQL_ROW row;


                printf("\n\n");
                printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
                printf("\t\t|                COUPANG                   |\n");
                printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
                printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
                printf("\t\t| Please enter your membership information |\n");
                printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

            
                    printf("\t\tID를 입력하십시오: ");
                    scanf("%s", &id);

                    qry_check = "select ID from User1;"; //회원가입시 ID(쿼리)가 중복인지 확인

                    mysql_real_query(conn, qry_check, strlen(qry_check));
                    res = mysql_store_result(conn);
                    field = mysql_num_fields(res);

                    while (row = mysql_fetch_row(res)) // 입력한 ID와 비교
                    {
                        for (int i = 0; i < field; i++)
                        {
                            sprintf(check_id, "%s", row[i]);
                            if (strcmp(id, check_id) == 0)
                            {
                                correct = 1;
                            }
                        }
                    }

                    mysql_free_result(res);

                    // 입력한 ID가 중복시, 다시 입력하게 하기 위함.
                    if (correct == 1)
                    {
                        printf("\n\n");
                        system("cls");
                        printf("\n\n\t\t이미 사용중인 아이디입니다. 다시 입력하십시오.");
                       
                        goto same_id;
                      
                    }
                    else //입력한 ID가 중복이 아닐 시,
                    {
                        printf("\t\t핸드폰번호를 입력하십시오: ");
                        scanf("%s", phone_number);

                        printf("\t\t이메일을 입력하십시오: ");
                        scanf("%s", email);

                        printf("\t\t이름을 입력하십시오: ");
                        scanf("%s", name);
                            
                        qry_storage = "insert into User1 values";
                        sprintf(qry, "\t\tinsert into User1 values ('%s', '%s','%s', '%s' );", id, phone_number, email, name); //입력받은 값들을 qry에 저장
                        printf("\n");
                        printf(qry); // 입력받은 값들을 출력


                        /* 값 입력 */
                        mysql_query(conn, qry);
                        mysql_store_result(conn);
                       

                        printf("\n\t\t회원가입을 완료하였습니다.\n");
                        Sleep(3000); //딜레이 3초 windows.h 내장함수.s는 대문자로 써야함.
                        goto login;
                    }

        }
        

        else if (selecting == 2) //로그인 창 
        {
            login:


            system("cls");
         

            // 로그인 실패시 goto 문을 통하여 다시 로그인 실행시키기 위한 변수
            login_fail:
            printf("\n\n\t\t로그인을 하십시오");


            char* qry_check; //id 체크용 변수
            char*qry; // 저장값id,휴대폰 번호,이메일,이름 값 저장
            char* qry_storage;  ///

            char id[20];//sql문에서 varchar(20)으로 설정했기에

            char check_id[20];//sql문에서 varchar(20)으로 설정했기에

            int field;

            int correct = 0;

            MYSQL_RES* res;
            MYSQL_ROW row;



            printf("\n\n");
            printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-\n");
            printf("\t\t|                                       |\n");
            printf("\t\t|               COUPANG                 |\n");
            printf("\t\t|                                       |\n");
            printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-\n");
            printf("\n");
            printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ- \n");
            printf("\t\t|           please login the ID         | \n");
            printf("\t\t-ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-\n");


            //저희 팀은 비밀번호는 비밀키라 따로 설정하지 않았습니다! 그래서 이번 과제에서 로그인 및 회원가입 과정에 비밀키 입력은 없습니다.

            printf("\n\t\t아이디를 입력하십시오:");
            scanf("%s", &id);

            qry = "select ID from User1;"; //ID(쿼리)가 중복인지 확인 :위의 1번 과 같은 과정으로 id가 맞으면 로그인 후 상품 주문선택으로 가기

            mysql_real_query(conn, qry, strlen(qry));
            res = mysql_store_result(conn);
            field = mysql_num_fields(res);

            while (row = mysql_fetch_row(res)) // 입력한 ID와 비교
            {
                for (int i = 0; i < field; i++)
                {
                    sprintf(check_id, "%s", row[i]);
                    if (strcmp(id, check_id) == 0)
                    {
                        correct = 1;
                    }
                }
            }

            mysql_free_result(res);
       
            if (correct == 1)
            {
                system("cls");
                printf("\n\n");
                printf("\t\t로그인에 성공하셨습니다. \n");

                productinfromation:


                printf("\n\n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t|                             COUPANG                                   |\n");
                printf("\t\t|                                                                       | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\n");
         
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t|                        Choose the product!                            | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t|                      <Product imformation>                            | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t| NO.| Number  | Unitprice | Classification | Quantity | Business number| \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t| 1.| 0000001 |   1,200   |     식품       |   100    |   0123456789    | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t| 2.| 0000100 |   30,000  |    의류        |   35     |   0123456710    | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t| 3.| 0010000 |  100,000  |  가전제품      |   15     |   0123453892    | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\n");
                printf("\n");

                int no=0;
                char product_number[10];//sql문에서 varchar(10)으로 설정했기에

                char resident_number[20]; //sql문에서 varchar(20)으로 설정했기에
                char address1[80]; //sql문에서 varchar(80)으로 설정했기에
                char address2[80];

                printf("\t\t원하는 상품을 선택하십시오:");
                scanf("%d", &no);

                if (no == 1)
                {
                    system("cls");

                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|우편번호를 입력하십시오: ");
                    scanf("%s", resident_number);
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|주소를 입력하십시오(ex:서울시 강남구): ");
                    scanf("%s %s", address1, address2);
                    printf("\t\t|-----------------------------------------| \n");
                    //카드결제 방식 잘못 입력시 돌아옴
                    paymentmethod1:
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t| 1.계좌이체 | 2.신용카드 | 3. 무통장입금 |\n");
                    printf("\t\t|-----------------------------------------| \n");
                    int payment_method = 0;
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|결제 방식을 선택하십시오: ");
                    scanf("%d", &payment_method);
                    printf("|\n");
                    printf("\t\t|-----------------------------------------| \n");
                    if (payment_method == 1)
                    {
                        
                        int bankcode;
                        printf("\n\t\t계좌번호를 입력하십시오:");
                        scanf("%d", &bankcode);



                        //판매 완료후 -1 하기
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000001';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //상품개수에서 -1 한 값 보여주기
   
                        printf("\n\t\t해당 상품은 ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000001'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result 값이 널이면 오류 검출용 코드
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result의 문자열 개수
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //프린트 내용
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }
                     
                        }
                        //result 값 초기화
                        mysql_free_result(result);

                        printf("개 남았습니다. \n");
                   

                        printf("\n\t\t|--------------------------|");
                        printf("\n\t\t|  구매가 완료되었습니다.  |");
                        printf("\n\t\t|<구매자 정보>");

                        printf("\n\t\t|우편번호: %s \n", resident_number);
                        printf("\n\t\t|주소: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t감사합니다! 배송이 시작됩니다. 배송일은 약 7일 정도 소요됩니다.\n\n");

                    }

                    else if (payment_method == 2)
                    {
                      

                        int card_number;
                        char card_company[30];
                        printf("\n\t\t카드사를 입력하십시오:");
                        scanf("%s", card_company);

                        printf("\n\t\t카드번호를 입력하십시오:");
                        scanf("%d", &card_number);


                        //판매 완료후 -1 하기
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000001';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //상품개수에서 -1 한 값 보여주기

                        printf("\n\t\t해당 상품은 ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000001'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result 값이 널이면 오류 검출용 코드
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result의 문자열 개수
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //프린트 내용
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }

                        }
                        //result 값 초기화
                        mysql_free_result(result);

                        printf("개 남았습니다. \n");

                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|  구매가 완료되었습니다.  |");
                        printf("\n\t\t|<구매자 정보>");
                        printf("\n\t\t|우편번호: %s \n", resident_number);
                        printf("\n\t\t|주소: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t감사합니다! 배송이 시작됩니다.배송일은 약 7일 정도 소요됩니다.\n\n");


                    }

                    else if (payment_method == 3)
                    {
                        
                        char bank_name[10];
                        printf("\n\t\t입금할 은행을 입력십시오: ");
                        scanf("%s", bank_name);
                        printf("\n\t\t입금할 은행 및 해당 은행의 판매자 계좌번호:");
                        printf("\n\t\t%s",bank_name);

                        // 입금할 판매자의 계좌번호를 불러오는 코드
                        mysql_query(conn, "select Account_number from  Manufacturer as m,product as p \
                        where p.Business_number = M.Business_number and p.product_number = '0000001'; ");

                        MYSQL_RES* result = mysql_store_result(conn);

                        //result 값이 널이면 오류 검출용 코드
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result의 문자열 개수
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //프린트 내용
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf("%10s   ", row[i] ? row[i] : "NULL");
                            }
                            printf("\n");
                        }
                        //result 값 초기화
                        mysql_free_result(result);

                        //판매 완료후 -1 하기
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000001';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        printf("\n\n\t\t구매일자 3일 이내로 입금해주세요.\n");
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|<구매자 정보>");
                        printf("\n");
                        printf("\n\t\t|우편번호: %s \n", resident_number);
                        printf("\n\t\t|주소: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\t\t");
                        printf("\n\t\t감사합니다! 배송일은 무통장 입금내역 확인 후 약 7일 정도 소요됩니다.\n\n");

                    }
                    //지불 방식이 잘못된 경우 다시 지불 방식 선택
                    else
                    {
                        system("cls");
                        printf("\n\t\t구매방식을 다시 입력하십시오 :");
                        goto paymentmethod1;

                    }
                }

                else if (no == 2)
                {
                    system("cls");

                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|우편번호를 입력하십시오: ");
                    scanf("%s", resident_number);
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|주소를 입력하십시오(ex:서울시 강남구): ");
                    scanf("%s %s", address1, address2);
                    printf("\t\t|-----------------------------------------| \n");

                     paymentmethod2:
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t| 1.계좌이체 | 2.신용카드 | 3. 무통장입금 |\n");
                    printf("\t\t|-----------------------------------------| \n");
                    int payment_method = 0;
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|결제 방식을 선택하십시오: ");
                    scanf("%d", &payment_method);
                    printf("|\n");
                    printf("\t\t|-----------------------------------------| \n");
                    if (payment_method == 1)
                    {

                        int bankcode;
                        printf("\n\t\t계좌번호를 입력하십시오:");
                        scanf("%d", &bankcode);

                        //판매 완료후 -1 하기
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000100';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //상품개수에서 -1 한 값 보여주기

                        printf("\n\t\t해당 상품은 ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000100'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result 값이 널이면 오류 검출용 코드
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result의 문자열 개수
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //프린트 내용
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }

                        }
                        //result 값 초기화
                        mysql_free_result(result);


                        printf("개 남았습니다. \n");

                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|  구매가 완료되었습니다.  |");
                        printf("\n\t\t|<구매자 정보>");
                        printf("\n\t\t|우편번호: %s \n", resident_number);
                        printf("\n\t\t|주소: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");

                        printf("\n\t\t감사합니다! 배송이 시작됩니다. 배송일은 약 7일 정도 소요됩니다.\n\n");


                    }

                    else if (payment_method == 2)
                    {

                        int card_number;
                        char card_company[30];
                        printf("\n\t\t카드사를 입력하십시오:");
                        scanf("%s", card_company);

                        printf("\n\t\t카드번호를 입력하십시오:");
                        scanf("%d", &card_number);


                        //판매 완료후 -1 하기
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000100';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //상품개수에서 -1 한 값 보여주기

                        printf("\n\t\t해당 상품은 ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000100'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result 값이 널이면 오류 검출용 코드
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result의 문자열 개수
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //프린트 내용
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }

                        }
                        //result 값 초기화
                        mysql_free_result(result);
                        printf("개 남았습니다. \n");
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|  구매가 완료되었습니다.  |");
                        printf("\n\t\t|<구매자 정보>");
                        printf("\n\t\t|우편번호: %s \n", resident_number);
                        printf("\n\t\t|주소: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");


                        printf("\n\t\t감사합니다! 배송이 시작됩니다.배송일은 약 7일 정도 소요됩니다.\n\n");


                    }

                    else if (payment_method == 3)
                    {

                        char bank_name[10];
                        printf("\n\t\t입금할 은행을 입력십시오: ");
                        scanf("%s", bank_name);
                        printf("\n\t\t입금할 은행 및 해당 은행의 판매자 계좌번호:");
                        printf("\n\t\t%s", bank_name);

                        // 입금할 판매자의 계좌번호를 불러오는 코드

                        mysql_query(conn, "select Account_number from  Manufacturer as m,product as p \
                        where p.Business_number = M.Business_number and p.product_number = '0000100'; ");

                        MYSQL_RES* result = mysql_store_result(conn);

                        //result 값이 널이면 오류 검출용 코드
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result의 문자열 개수
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //프린트 내용
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf("%10s   ", row[i] ? row[i] : "NULL");
                            }
                            printf("\n");
                        }
                        //result 값 초기화
                        mysql_free_result(result);

                        printf("\n\n\t\t구매일자 3일 이내로 입금해주세요.\n");
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|<구매자 정보>");
                        printf("\n");
                        printf("\n\t\t|우편번호: %s \n", resident_number);
                        printf("\n\t\t|주소: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\t\t");



                        printf("\n\t\t감사합니다! 배송일은 무통장 입금내역 확인 후 약 7일 정도 소요됩니다.\n\n");

                    }
                    //지불 방식이 잘못 된 경우 다시 지불 방식 선택
                    else
                    {
                        system("cls");
                        printf("\n\t\t구매방식을 다시 입력하십시오 :");
                        goto paymentmethod2;

                    }
 

                }
       

                else if (no == 3)
                {
                system("cls");

                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t|우편번호를 입력하십시오: ");
                scanf("%s", resident_number);
                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t|주소를 입력하십시오(ex:서울시 강남구): ");
                scanf("%s %s", address1, address2);
                printf("\t\t|-----------------------------------------| \n");

                paymentmethod3:
                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t| 1.계좌이체 | 2.신용카드 | 3. 무통장입금 |\n");
                printf("\t\t|-----------------------------------------| \n");
                int payment_method = 0;
                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t|결제 방식을 선택하십시오: ");
                scanf("%d", &payment_method);
                printf("|\n");
                printf("\t\t|-----------------------------------------| \n");
                if (payment_method == 1)
                {

                    int bankcode;
                    printf("\n\t\t계좌번호를 입력하십시오:");
                    scanf("%d", &bankcode);

                    //판매 완료후 -1 하기
                    qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0010000';";
                    mysql_real_query(conn, qry, strlen(qry));
                    res = mysql_store_result(conn);


                    //상품개수에서 -1 한 값 보여주기

                    printf("\n\t\t해당 상품은 ");
                    mysql_query(conn, "select Product_quantity from Product where Product_number='0010000'; ");
                    MYSQL_RES* result = mysql_store_result(conn);

                    //result 값이 널이면 오류 검출용 코드
                    if (result == NULL)
                    {
                        finish_with_error(conn);
                    }
                    // result의 문자열 개수
                    int num_fields = mysql_num_fields(result);

                    MYSQL_ROW row;
                    //프린트 내용
                    while (row = mysql_fetch_row(result))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf(" %s", row[i] ? row[i] : "NULL");
                        }

                    }
                    //result 값 초기화
                    mysql_free_result(result);


                    printf("개 남았습니다. \n");

                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t|  구매가 완료되었습니다.  |");
                    printf("\n\t\t|<구매자 정보>");
                    printf("\n\t\t|우편번호: %s \n", resident_number);
                    printf("\n\t\t|주소: %s %s  ", address1, address2);
                    printf("\n\t\t|--------------------------| \n");

                    printf("\n\t\t감사합니다! 배송이 시작됩니다. 배송일은 약 7일 정도 소요됩니다.\n\n");


                }

                else if (payment_method == 2)
                {

                    int card_number;
                    char card_company[30];
                    printf("\n\t\t카드사를 입력하십시오:");
                    scanf("%s", card_company);

                    printf("\n\t\t카드번호를 입력하십시오:");
                    scanf("%d", &card_number);

                    //판매 완료후 -1 하기
                    qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0010000';";
                    mysql_real_query(conn, qry, strlen(qry));
                    res = mysql_store_result(conn);


                    //상품개수에서 -1 한 값 보여주기

                    printf("\n\t\t해당 상품은 ");
                    mysql_query(conn, "select Product_quantity from Product where Product_number='0010000'; ");
                    MYSQL_RES* result = mysql_store_result(conn);

                    //result 값이 널이면 오류 검출용 코드
                    if (result == NULL)
                    {
                        finish_with_error(conn);
                    }
                    // result의 문자열 개수
                    int num_fields = mysql_num_fields(result);

                    MYSQL_ROW row;
                    //프린트 내용
                    while (row = mysql_fetch_row(result))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf(" %s", row[i] ? row[i] : "NULL");
                        }

                    }
                    //result 값 초기화
                    mysql_free_result(result);


                    printf("개 남았습니다. \n");

                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t|  구매가 완료되었습니다.  |");
                    printf("\n\t\t|<구매자 정보>");
                    printf("\n\t\t|우편번호: %s \n", resident_number);
                    printf("\n\t\t|주소: %s %s  ", address1, address2);
                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t감사합니다! 배송이 시작됩니다.배송일은 약 7일 정도 소요됩니다.\n\n");


                }

                else if (payment_method == 3)
                {

                    char bank_name[10];
                    printf("\n\t\t입금할 은행을 입력십시오: ");
                    scanf("%s", bank_name);
                    printf("\n\t\t입금할 은행 및 해당 은행의 판매자 계좌번호:");
                    printf("\n\t\t%s", bank_name);

                    // 입금할 판매자의 계좌번호를 불러오는 코드

                    mysql_query(conn, "select Account_number from  Manufacturer as m,product as p \
                        where p.Business_number = M.Business_number and p.product_number = '0010000'; ");

                    MYSQL_RES* result = mysql_store_result(conn);

                    //result 값이 널이면 오류 검출용 코드
                    if (result == NULL)
                    {
                        finish_with_error(conn);
                    }
                    // result의 문자열 개수
                    int num_fields = mysql_num_fields(result);

                    MYSQL_ROW row;
                    //프린트 내용
                    while (row = mysql_fetch_row(result))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%10s   ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                    //result 값 초기화
                    mysql_free_result(result);

                    printf("\n\n\t\t구매일자 3일 이내로 입금해주세요.\n");
                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t|<구매자 정보>");
                    printf("\n");
                    printf("\n\t\t|우편번호: %s \n", resident_number);
                    printf("\n\t\t|주소: %s %s  ", address1, address2);
                    printf("\n\t\t|--------------------------| \n");
                    printf("\t\t");



                    printf("\n\t\t감사합니다! 배송일은 무통장 입금내역 확인 후 약 7일 정도 소요됩니다.\n\n");

                }
                //지불 방식이 잘못 된 경우 다시 지불 방식 선택
                else
                {
                    system("cls");
                    printf("\n\t\t구매방식을 다시 입력하십시오 :");
                    goto paymentmethod3;

                }

                }

                else 
                {
                    system("cls");
                    printf("\n\t\t상품 선택을 다시 입력하십시오 :");
                    goto productinfromation;
                }

            }
        
            else
            {
                system("cls");
                printf("\t\t로그인에 실패하셨습니다.\n");
                printf("\t\t다시 시도 해주십시오.\n");
                printf("\n\n");
                goto login_fail;
            }
           
        }

         else if (selecting == 3)
        {
            printf("\t\t웹페이지를 종료합니다.\n\n");
            exit(1);

        }
  
     mysql_close(conn);

    return 0;

}
