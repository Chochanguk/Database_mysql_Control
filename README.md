# Database_mysql_Control
```cpp
#include<stdio.h>

int main()
{
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_real_query(conn, qry_check, strlen(qry_check));
    res = mysql_store_result(conn);
    field = mysql_num_fields(res);
}


```
