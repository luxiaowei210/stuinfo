#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * teacher="teacher.html";

int cgiMain()
{
	char tid[32] = "\0";
  char tpassword[32] = "\0";
	int status = 0;

	FILE * fd;
  char ch;
  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	status = cgiFormString("tid",  tid, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tid error!\n");
		return 1;
	}

	status = cgiFormString("tpassword",  tpassword, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tpassword error!\n");
		return 1;
	}

	int ret;
	MYSQL *db;
	char sql[128] = "\0";

  sprintf(sql, "select * from teacher where tid= '%s' and tpassword ='%s'",tid,tpassword);

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

     if(!(fd = fopen(teacher,"r"))){
      fprintf(cgiOut,"can not open file%s\n",teacher);
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
