#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * student="student.html";

int cgiMain()
{
    char id[32] = "\0";
    char spassword[32] = "\0";

    int status = 0;

  FILE * fd;
  char ch;

  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

    status = cgiFormString("id", id, 32);
    if (status != cgiFormSuccess)
    {
        fprintf(cgiOut, "get id error!\n");
        return 1;
    }
    status = cgiFormString("spassword", spassword, 32);
    if (status != cgiFormSuccess)
    {
        fprintf(cgiOut, "get spassword error!\n");
return 1;
    }


  int ret;
    MYSQL *db;
    char sql[128] = "\0";

  sprintf(sql, "select * from student where id= '%s' and spassword ='%s'",id,spassword);

    //初始化
    db = mysql_init(NULL);
    if (db == NULL)
    {
        fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
        return -1;
    }

    //连接数据库
    db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
    if (db == NULL)
    {
        fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
        mysql_close(db);
        return -1;
    }

    if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
    {
        fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
        mysql_close(db);
        return -1;
    }

    MYSQL_RES *res;
    res = mysql_store_result(db);
    if (res == NULL)
    {
        fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
        return -1;
    }

    int num = (int)res->row_count;
    if(num){

    if(!(fd = fopen(student,"r"))){
     fprintf(cgiOut,"can not open file%s\n",student);
    return -1;
    }
   ch = fgetc(fd);

     while(ch !=EOF){
     fprintf(cgiOut, "%c" ,ch);
     ch = fgetc(fd);
        }
    }




    mysql_close(db);
    return 0;
}
