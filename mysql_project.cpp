#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#pragma comment (lib, "libmysql.lib")


#define MYSQLUSER "root"//���� �̸�
#define MYSQLPASSWORD "dgu1234!"//��й�ȣ
#define MYSQLIP "localhost"//������ ip �ڱ��ڽ��� localhost �ƴϸ� ipconfig�� �ڽ��� ip�� ģ��.
//localhost�� �ٸ���ǻ�ͷ� �ϸ� ������ �ȵȴ�. �����Ҷ� ����

//���� ���� ��й�ȣ�� ���Ű�� ���� �������� �ʾҽ��ϴ�. �׷��� �̹� �������� �α��� �� ȸ������ ������ ��й�ȣ �Է��� �Ϻη� �ȳ־����ϴ�. 
// �� �� �����ؼ� ���ֽø� ���� �����ϰڽ��ϴ�.
//2019112174 ��â�� �� ������



void loadmysql(char mysqlip[], MYSQL* cons)//MYSQL ���� �ҷ�����
{
    if (cons == NULL) //cons�� �ʱ�ȭ�� ��������
    {
        fprintf(stderr, "%s\n", mysql_error(cons));//���� ����Ʈ, printf("%s")�� ����
        Sleep(1000);
        exit(1);
    }

    if (!(mysql_real_connect(cons, mysqlip, MYSQLUSER, MYSQLPASSWORD, NULL, 0, NULL, 0) == NULL)) //mysql������ ���� �����ϸ� 0 �ƴϸ� �ٸ��� ��ȯ
    {
        mysql_set_character_set(cons, "euckr");//MySQL ���ڸ� �����Ѵ�. ���� ���ϸ� �ѱ��� ©��.
    }

    else
    {
        fprintf(stderr, "���� ���� : %s\n", mysql_error(cons));
        getchar();
    }
    return;
}

void finish_with_error(MYSQL* conn)
{
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int main(void)
{

    MYSQL* conn = mysql_init(NULL);//MYSQL ���� �ʱ�ȭ.
    loadmysql(MYSQLIP, conn);

    //we used DB Coupang1

    char* qry_check; //id üũ�� ����
    char qry[200]; // sprint ���尪id,�޴��� ��ȣ,�̸���,�̸� �� ����
    char* qry_storage;  ///

    char id[20];//sql������ varchar(20)���� �����߱⿡

    char check_id[20];//sql������ varchar(20)���� �����߱⿡

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
    printf("\t\t �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("\t\t|                COUPANG               |\n");
    printf("\t\t �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");

    printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�-\n");

    printf("\t\t|\t\t");
    printf("1.ȸ������");
    printf("\t\t|\n");

    printf("\t\t|\t\t");
    printf("2.�α���");
    printf("\t\t|\n");


    printf("\t\t|\t\t");
    printf("3.�������� ����");
    printf("\t\t|\n");
    printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�-\n");


    int selecting;
   
    printf("\t\t Select the number what you want :");
    scanf("%d", &selecting);

        if (selecting == 1) //ȸ������ â
        {
            system("cls");
            same_id:
         
            char phone_number[20]; //sql������ varchar(20)���� �����߱⿡
            char email[80]; //sql������ varchar(80)���� �����߱⿡
            char name[20]; //sql������ varchar(20)���� �����߱⿡

            char* qry_check; //id üũ�� ����
            char qry[200]; // sprint ���尪id,�޴��� ��ȣ,�̸���,�̸� �� ����
            char* qry_storage;  ///

            char id[20];//sql������ varchar(20)���� �����߱⿡

            char check_id[20];//sql������ varchar(20)���� �����߱⿡

            int field;

            int correct = 0;

            MYSQL_RES* res;
            MYSQL_ROW row;


                printf("\n\n");
                printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
                printf("\t\t|                COUPANG                   |\n");
                printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
                printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
                printf("\t\t| Please enter your membership information |\n");
                printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");

            
                    printf("\t\tID�� �Է��Ͻʽÿ�: ");
                    scanf("%s", &id);

                    qry_check = "select ID from User1;"; //ȸ�����Խ� ID(����)�� �ߺ����� Ȯ��

                    mysql_real_query(conn, qry_check, strlen(qry_check));
                    res = mysql_store_result(conn);
                    field = mysql_num_fields(res);

                    while (row = mysql_fetch_row(res)) // �Է��� ID�� ��
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

                    // �Է��� ID�� �ߺ���, �ٽ� �Է��ϰ� �ϱ� ����.
                    if (correct == 1)
                    {
                        printf("\n\n");
                        system("cls");
                        printf("\n\n\t\t�̹� ������� ���̵��Դϴ�. �ٽ� �Է��Ͻʽÿ�.");
                       
                        goto same_id;
                      
                    }
                    else //�Է��� ID�� �ߺ��� �ƴ� ��,
                    {
                        printf("\t\t�ڵ�����ȣ�� �Է��Ͻʽÿ�: ");
                        scanf("%s", phone_number);

                        printf("\t\t�̸����� �Է��Ͻʽÿ�: ");
                        scanf("%s", email);

                        printf("\t\t�̸��� �Է��Ͻʽÿ�: ");
                        scanf("%s", name);
                            
                        qry_storage = "insert into User1 values";
                        sprintf(qry, "\t\tinsert into User1 values ('%s', '%s','%s', '%s' );", id, phone_number, email, name); //�Է¹��� ������ qry�� ����
                        printf("\n");
                        printf(qry); // �Է¹��� ������ ���


                        /* �� �Է� */
                        mysql_query(conn, qry);
                        mysql_store_result(conn);
                       

                        printf("\n\t\tȸ�������� �Ϸ��Ͽ����ϴ�.\n");
                        Sleep(3000); //������ 3�� windows.h �����Լ�.s�� �빮�ڷ� �����.
                        goto login;
                    }

        }
        

        else if (selecting == 2) //�α��� â 
        {
            login:


            system("cls");
         

            // �α��� ���н� goto ���� ���Ͽ� �ٽ� �α��� �����Ű�� ���� ����
            login_fail:
            printf("\n\n\t\t�α����� �Ͻʽÿ�");


            char* qry_check; //id üũ�� ����
            char*qry; // ���尪id,�޴��� ��ȣ,�̸���,�̸� �� ����
            char* qry_storage;  ///

            char id[20];//sql������ varchar(20)���� �����߱⿡

            char check_id[20];//sql������ varchar(20)���� �����߱⿡

            int field;

            int correct = 0;

            MYSQL_RES* res;
            MYSQL_ROW row;



            printf("\n\n");
            printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�-\n");
            printf("\t\t|                                       |\n");
            printf("\t\t|               COUPANG                 |\n");
            printf("\t\t|                                       |\n");
            printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�-\n");
            printf("\n");
            printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�- \n");
            printf("\t\t|           please login the ID         | \n");
            printf("\t\t-�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�-\n");


            //���� ���� ��й�ȣ�� ���Ű�� ���� �������� �ʾҽ��ϴ�! �׷��� �̹� �������� �α��� �� ȸ������ ������ ���Ű �Է��� �����ϴ�.

            printf("\n\t\t���̵� �Է��Ͻʽÿ�:");
            scanf("%s", &id);

            qry = "select ID from User1;"; //ID(����)�� �ߺ����� Ȯ�� :���� 1�� �� ���� �������� id�� ������ �α��� �� ��ǰ �ֹ��������� ����

            mysql_real_query(conn, qry, strlen(qry));
            res = mysql_store_result(conn);
            field = mysql_num_fields(res);

            while (row = mysql_fetch_row(res)) // �Է��� ID�� ��
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
                printf("\t\t�α��ο� �����ϼ̽��ϴ�. \n");

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
                printf("\t\t| 1.| 0000001 |   1,200   |     ��ǰ       |   100    |   0123456789    | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t| 2.| 0000100 |   30,000  |    �Ƿ�        |   35     |   0123456710    | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\t\t| 3.| 0010000 |  100,000  |  ������ǰ      |   15     |   0123453892    | \n");
                printf("\t\t|-----------------------------------------------------------------------| \n");
                printf("\n");
                printf("\n");

                int no=0;
                char product_number[10];//sql������ varchar(10)���� �����߱⿡

                char resident_number[20]; //sql������ varchar(20)���� �����߱⿡
                char address1[80]; //sql������ varchar(80)���� �����߱⿡
                char address2[80];

                printf("\t\t���ϴ� ��ǰ�� �����Ͻʽÿ�:");
                scanf("%d", &no);

                if (no == 1)
                {
                    system("cls");

                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|�����ȣ�� �Է��Ͻʽÿ�: ");
                    scanf("%s", resident_number);
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|�ּҸ� �Է��Ͻʽÿ�(ex:����� ������): ");
                    scanf("%s %s", address1, address2);
                    printf("\t\t|-----------------------------------------| \n");
                    //ī����� ��� �߸� �Է½� ���ƿ�
                    paymentmethod1:
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t| 1.������ü | 2.�ſ�ī�� | 3. �������Ա� |\n");
                    printf("\t\t|-----------------------------------------| \n");
                    int payment_method = 0;
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|���� ����� �����Ͻʽÿ�: ");
                    scanf("%d", &payment_method);
                    printf("|\n");
                    printf("\t\t|-----------------------------------------| \n");
                    if (payment_method == 1)
                    {
                        
                        int bankcode;
                        printf("\n\t\t���¹�ȣ�� �Է��Ͻʽÿ�:");
                        scanf("%d", &bankcode);



                        //�Ǹ� �Ϸ��� -1 �ϱ�
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000001';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //��ǰ�������� -1 �� �� �����ֱ�
   
                        printf("\n\t\t�ش� ��ǰ�� ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000001'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result ���� ���̸� ���� ����� �ڵ�
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result�� ���ڿ� ����
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //����Ʈ ����
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }
                     
                        }
                        //result �� �ʱ�ȭ
                        mysql_free_result(result);

                        printf("�� ���ҽ��ϴ�. \n");
                   

                        printf("\n\t\t|--------------------------|");
                        printf("\n\t\t|  ���Ű� �Ϸ�Ǿ����ϴ�.  |");
                        printf("\n\t\t|<������ ����>");

                        printf("\n\t\t|�����ȣ: %s \n", resident_number);
                        printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t�����մϴ�! ����� ���۵˴ϴ�. ������� �� 7�� ���� �ҿ�˴ϴ�.\n\n");

                    }

                    else if (payment_method == 2)
                    {
                      

                        int card_number;
                        char card_company[30];
                        printf("\n\t\tī��縦 �Է��Ͻʽÿ�:");
                        scanf("%s", card_company);

                        printf("\n\t\tī���ȣ�� �Է��Ͻʽÿ�:");
                        scanf("%d", &card_number);


                        //�Ǹ� �Ϸ��� -1 �ϱ�
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000001';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //��ǰ�������� -1 �� �� �����ֱ�

                        printf("\n\t\t�ش� ��ǰ�� ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000001'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result ���� ���̸� ���� ����� �ڵ�
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result�� ���ڿ� ����
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //����Ʈ ����
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }

                        }
                        //result �� �ʱ�ȭ
                        mysql_free_result(result);

                        printf("�� ���ҽ��ϴ�. \n");

                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|  ���Ű� �Ϸ�Ǿ����ϴ�.  |");
                        printf("\n\t\t|<������ ����>");
                        printf("\n\t\t|�����ȣ: %s \n", resident_number);
                        printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t�����մϴ�! ����� ���۵˴ϴ�.������� �� 7�� ���� �ҿ�˴ϴ�.\n\n");


                    }

                    else if (payment_method == 3)
                    {
                        
                        char bank_name[10];
                        printf("\n\t\t�Ա��� ������ �Է½ʽÿ�: ");
                        scanf("%s", bank_name);
                        printf("\n\t\t�Ա��� ���� �� �ش� ������ �Ǹ��� ���¹�ȣ:");
                        printf("\n\t\t%s",bank_name);

                        // �Ա��� �Ǹ����� ���¹�ȣ�� �ҷ����� �ڵ�
                        mysql_query(conn, "select Account_number from  Manufacturer as m,product as p \
                        where p.Business_number = M.Business_number and p.product_number = '0000001'; ");

                        MYSQL_RES* result = mysql_store_result(conn);

                        //result ���� ���̸� ���� ����� �ڵ�
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result�� ���ڿ� ����
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //����Ʈ ����
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf("%10s   ", row[i] ? row[i] : "NULL");
                            }
                            printf("\n");
                        }
                        //result �� �ʱ�ȭ
                        mysql_free_result(result);

                        //�Ǹ� �Ϸ��� -1 �ϱ�
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000001';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        printf("\n\n\t\t�������� 3�� �̳��� �Ա����ּ���.\n");
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|<������ ����>");
                        printf("\n");
                        printf("\n\t\t|�����ȣ: %s \n", resident_number);
                        printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\t\t");
                        printf("\n\t\t�����մϴ�! ������� ������ �Աݳ��� Ȯ�� �� �� 7�� ���� �ҿ�˴ϴ�.\n\n");

                    }
                    //���� ����� �߸��� ��� �ٽ� ���� ��� ����
                    else
                    {
                        system("cls");
                        printf("\n\t\t���Ź���� �ٽ� �Է��Ͻʽÿ� :");
                        goto paymentmethod1;

                    }
                }

                else if (no == 2)
                {
                    system("cls");

                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|�����ȣ�� �Է��Ͻʽÿ�: ");
                    scanf("%s", resident_number);
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|�ּҸ� �Է��Ͻʽÿ�(ex:����� ������): ");
                    scanf("%s %s", address1, address2);
                    printf("\t\t|-----------------------------------------| \n");

                     paymentmethod2:
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t| 1.������ü | 2.�ſ�ī�� | 3. �������Ա� |\n");
                    printf("\t\t|-----------------------------------------| \n");
                    int payment_method = 0;
                    printf("\t\t|-----------------------------------------| \n");
                    printf("\t\t|���� ����� �����Ͻʽÿ�: ");
                    scanf("%d", &payment_method);
                    printf("|\n");
                    printf("\t\t|-----------------------------------------| \n");
                    if (payment_method == 1)
                    {

                        int bankcode;
                        printf("\n\t\t���¹�ȣ�� �Է��Ͻʽÿ�:");
                        scanf("%d", &bankcode);

                        //�Ǹ� �Ϸ��� -1 �ϱ�
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000100';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //��ǰ�������� -1 �� �� �����ֱ�

                        printf("\n\t\t�ش� ��ǰ�� ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000100'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result ���� ���̸� ���� ����� �ڵ�
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result�� ���ڿ� ����
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //����Ʈ ����
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }

                        }
                        //result �� �ʱ�ȭ
                        mysql_free_result(result);


                        printf("�� ���ҽ��ϴ�. \n");

                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|  ���Ű� �Ϸ�Ǿ����ϴ�.  |");
                        printf("\n\t\t|<������ ����>");
                        printf("\n\t\t|�����ȣ: %s \n", resident_number);
                        printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");

                        printf("\n\t\t�����մϴ�! ����� ���۵˴ϴ�. ������� �� 7�� ���� �ҿ�˴ϴ�.\n\n");


                    }

                    else if (payment_method == 2)
                    {

                        int card_number;
                        char card_company[30];
                        printf("\n\t\tī��縦 �Է��Ͻʽÿ�:");
                        scanf("%s", card_company);

                        printf("\n\t\tī���ȣ�� �Է��Ͻʽÿ�:");
                        scanf("%d", &card_number);


                        //�Ǹ� �Ϸ��� -1 �ϱ�
                        qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0000100';";
                        mysql_real_query(conn, qry, strlen(qry));
                        res = mysql_store_result(conn);

                        //��ǰ�������� -1 �� �� �����ֱ�

                        printf("\n\t\t�ش� ��ǰ�� ");
                        mysql_query(conn, "select Product_quantity from Product where Product_number='0000100'; ");
                        MYSQL_RES* result = mysql_store_result(conn);

                        //result ���� ���̸� ���� ����� �ڵ�
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result�� ���ڿ� ����
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //����Ʈ ����
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf(" %s", row[i] ? row[i] : "NULL");
                            }

                        }
                        //result �� �ʱ�ȭ
                        mysql_free_result(result);
                        printf("�� ���ҽ��ϴ�. \n");
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|  ���Ű� �Ϸ�Ǿ����ϴ�.  |");
                        printf("\n\t\t|<������ ����>");
                        printf("\n\t\t|�����ȣ: %s \n", resident_number);
                        printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");


                        printf("\n\t\t�����մϴ�! ����� ���۵˴ϴ�.������� �� 7�� ���� �ҿ�˴ϴ�.\n\n");


                    }

                    else if (payment_method == 3)
                    {

                        char bank_name[10];
                        printf("\n\t\t�Ա��� ������ �Է½ʽÿ�: ");
                        scanf("%s", bank_name);
                        printf("\n\t\t�Ա��� ���� �� �ش� ������ �Ǹ��� ���¹�ȣ:");
                        printf("\n\t\t%s", bank_name);

                        // �Ա��� �Ǹ����� ���¹�ȣ�� �ҷ����� �ڵ�

                        mysql_query(conn, "select Account_number from  Manufacturer as m,product as p \
                        where p.Business_number = M.Business_number and p.product_number = '0000100'; ");

                        MYSQL_RES* result = mysql_store_result(conn);

                        //result ���� ���̸� ���� ����� �ڵ�
                        if (result == NULL)
                        {
                            finish_with_error(conn);
                        }
                        // result�� ���ڿ� ����
                        int num_fields = mysql_num_fields(result);

                        MYSQL_ROW row;
                        //����Ʈ ����
                        while (row = mysql_fetch_row(result))
                        {
                            for (int i = 0; i < num_fields; i++)
                            {
                                printf("%10s   ", row[i] ? row[i] : "NULL");
                            }
                            printf("\n");
                        }
                        //result �� �ʱ�ȭ
                        mysql_free_result(result);

                        printf("\n\n\t\t�������� 3�� �̳��� �Ա����ּ���.\n");
                        printf("\n\t\t|--------------------------| \n");
                        printf("\n\t\t|<������ ����>");
                        printf("\n");
                        printf("\n\t\t|�����ȣ: %s \n", resident_number);
                        printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                        printf("\n\t\t|--------------------------| \n");
                        printf("\t\t");



                        printf("\n\t\t�����մϴ�! ������� ������ �Աݳ��� Ȯ�� �� �� 7�� ���� �ҿ�˴ϴ�.\n\n");

                    }
                    //���� ����� �߸� �� ��� �ٽ� ���� ��� ����
                    else
                    {
                        system("cls");
                        printf("\n\t\t���Ź���� �ٽ� �Է��Ͻʽÿ� :");
                        goto paymentmethod2;

                    }
 

                }
       

                else if (no == 3)
                {
                system("cls");

                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t|�����ȣ�� �Է��Ͻʽÿ�: ");
                scanf("%s", resident_number);
                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t|�ּҸ� �Է��Ͻʽÿ�(ex:����� ������): ");
                scanf("%s %s", address1, address2);
                printf("\t\t|-----------------------------------------| \n");

                paymentmethod3:
                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t| 1.������ü | 2.�ſ�ī�� | 3. �������Ա� |\n");
                printf("\t\t|-----------------------------------------| \n");
                int payment_method = 0;
                printf("\t\t|-----------------------------------------| \n");
                printf("\t\t|���� ����� �����Ͻʽÿ�: ");
                scanf("%d", &payment_method);
                printf("|\n");
                printf("\t\t|-----------------------------------------| \n");
                if (payment_method == 1)
                {

                    int bankcode;
                    printf("\n\t\t���¹�ȣ�� �Է��Ͻʽÿ�:");
                    scanf("%d", &bankcode);

                    //�Ǹ� �Ϸ��� -1 �ϱ�
                    qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0010000';";
                    mysql_real_query(conn, qry, strlen(qry));
                    res = mysql_store_result(conn);


                    //��ǰ�������� -1 �� �� �����ֱ�

                    printf("\n\t\t�ش� ��ǰ�� ");
                    mysql_query(conn, "select Product_quantity from Product where Product_number='0010000'; ");
                    MYSQL_RES* result = mysql_store_result(conn);

                    //result ���� ���̸� ���� ����� �ڵ�
                    if (result == NULL)
                    {
                        finish_with_error(conn);
                    }
                    // result�� ���ڿ� ����
                    int num_fields = mysql_num_fields(result);

                    MYSQL_ROW row;
                    //����Ʈ ����
                    while (row = mysql_fetch_row(result))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf(" %s", row[i] ? row[i] : "NULL");
                        }

                    }
                    //result �� �ʱ�ȭ
                    mysql_free_result(result);


                    printf("�� ���ҽ��ϴ�. \n");

                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t|  ���Ű� �Ϸ�Ǿ����ϴ�.  |");
                    printf("\n\t\t|<������ ����>");
                    printf("\n\t\t|�����ȣ: %s \n", resident_number);
                    printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                    printf("\n\t\t|--------------------------| \n");

                    printf("\n\t\t�����մϴ�! ����� ���۵˴ϴ�. ������� �� 7�� ���� �ҿ�˴ϴ�.\n\n");


                }

                else if (payment_method == 2)
                {

                    int card_number;
                    char card_company[30];
                    printf("\n\t\tī��縦 �Է��Ͻʽÿ�:");
                    scanf("%s", card_company);

                    printf("\n\t\tī���ȣ�� �Է��Ͻʽÿ�:");
                    scanf("%d", &card_number);

                    //�Ǹ� �Ϸ��� -1 �ϱ�
                    qry = "update Product set Product_quantity=product_quantity-1 \
                        where Product_number = '0010000';";
                    mysql_real_query(conn, qry, strlen(qry));
                    res = mysql_store_result(conn);


                    //��ǰ�������� -1 �� �� �����ֱ�

                    printf("\n\t\t�ش� ��ǰ�� ");
                    mysql_query(conn, "select Product_quantity from Product where Product_number='0010000'; ");
                    MYSQL_RES* result = mysql_store_result(conn);

                    //result ���� ���̸� ���� ����� �ڵ�
                    if (result == NULL)
                    {
                        finish_with_error(conn);
                    }
                    // result�� ���ڿ� ����
                    int num_fields = mysql_num_fields(result);

                    MYSQL_ROW row;
                    //����Ʈ ����
                    while (row = mysql_fetch_row(result))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf(" %s", row[i] ? row[i] : "NULL");
                        }

                    }
                    //result �� �ʱ�ȭ
                    mysql_free_result(result);


                    printf("�� ���ҽ��ϴ�. \n");

                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t|  ���Ű� �Ϸ�Ǿ����ϴ�.  |");
                    printf("\n\t\t|<������ ����>");
                    printf("\n\t\t|�����ȣ: %s \n", resident_number);
                    printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t�����մϴ�! ����� ���۵˴ϴ�.������� �� 7�� ���� �ҿ�˴ϴ�.\n\n");


                }

                else if (payment_method == 3)
                {

                    char bank_name[10];
                    printf("\n\t\t�Ա��� ������ �Է½ʽÿ�: ");
                    scanf("%s", bank_name);
                    printf("\n\t\t�Ա��� ���� �� �ش� ������ �Ǹ��� ���¹�ȣ:");
                    printf("\n\t\t%s", bank_name);

                    // �Ա��� �Ǹ����� ���¹�ȣ�� �ҷ����� �ڵ�

                    mysql_query(conn, "select Account_number from  Manufacturer as m,product as p \
                        where p.Business_number = M.Business_number and p.product_number = '0010000'; ");

                    MYSQL_RES* result = mysql_store_result(conn);

                    //result ���� ���̸� ���� ����� �ڵ�
                    if (result == NULL)
                    {
                        finish_with_error(conn);
                    }
                    // result�� ���ڿ� ����
                    int num_fields = mysql_num_fields(result);

                    MYSQL_ROW row;
                    //����Ʈ ����
                    while (row = mysql_fetch_row(result))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%10s   ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                    //result �� �ʱ�ȭ
                    mysql_free_result(result);

                    printf("\n\n\t\t�������� 3�� �̳��� �Ա����ּ���.\n");
                    printf("\n\t\t|--------------------------| \n");
                    printf("\n\t\t|<������ ����>");
                    printf("\n");
                    printf("\n\t\t|�����ȣ: %s \n", resident_number);
                    printf("\n\t\t|�ּ�: %s %s  ", address1, address2);
                    printf("\n\t\t|--------------------------| \n");
                    printf("\t\t");



                    printf("\n\t\t�����մϴ�! ������� ������ �Աݳ��� Ȯ�� �� �� 7�� ���� �ҿ�˴ϴ�.\n\n");

                }
                //���� ����� �߸� �� ��� �ٽ� ���� ��� ����
                else
                {
                    system("cls");
                    printf("\n\t\t���Ź���� �ٽ� �Է��Ͻʽÿ� :");
                    goto paymentmethod3;

                }

                }

                else 
                {
                    system("cls");
                    printf("\n\t\t��ǰ ������ �ٽ� �Է��Ͻʽÿ� :");
                    goto productinfromation;
                }

            }
        
            else
            {
                system("cls");
                printf("\t\t�α��ο� �����ϼ̽��ϴ�.\n");
                printf("\t\t�ٽ� �õ� ���ֽʽÿ�.\n");
                printf("\n\n");
                goto login_fail;
            }
           
        }

         else if (selecting == 3)
        {
            printf("\t\t���������� �����մϴ�.\n\n");
            exit(1);

        }
  
     mysql_close(conn);

    return 0;

}
