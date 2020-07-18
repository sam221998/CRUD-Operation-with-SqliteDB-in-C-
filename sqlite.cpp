#include<iostream>
#include<sqlite3.h>
using namespace std;

int callback(void*, int argc, char** argv, char** col_names)
{
    for (int i = 0; i < argc; ++i)
        cout << col_names[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
    cout << endl;
    return 0;
}
int main(int argc,char *argv[])
{
sqlite3 *db;

char *select1;
char *select2;
char *select3;
char *insert;
char *update;
char *del;

const char* d="Callback Function Called";
char *err_msg = 0;
int rc = sqlite3_open("Student.db", &db);
if (rc != SQLITE_OK) 
{
cout<< "Can not open the database:"<<sqlite3_errmsg(db)<<endl;
sqlite3_close(db);
return 1;
}
else 
{
   cout<<"\n";
   cout<<"Database Opened successfully";
}
select1="select * from stud;" \
	 "select * from subject;" \
	 "select * from marks;";
//select2="select * from subject";
//select3="select * from marks";
insert="INSERT INTO stud (srno,name) "  \
         "VALUES (18120, 'Rohit Nale'); " \
         "INSERT INTO marks (sid,subid,mark) "  \
         "VALUES (18120,102,75); "\
	 "select * from stud;" \
	 "select * from marks;";     
update="update marks set mark=79 where sid=18226 and subid=102;"\
	"select * from marks;";
del="DELETE from stud where srno=18120; " \
         "SELECT * from stud";

cout<<"\n";
cout<<"Selecting All Tables in Database";
rc=sqlite3_exec(db,select1,callback,(void*)d,&err_msg);
//rc=sqlite3_exec(db,select2,callback,(void*)d,&err_msg);
//rc=sqlite3_exec(db,select3,callback,(void*)d,&err_msg);
cout<<"\n";
cout<<"Inserting the values in stud and marks table";
rc=sqlite3_exec(db,insert,callback,(void*)d,&err_msg);

cout<<"\n";
cout<<"Update the marks of studentid=18226 and subid=102";
rc=sqlite3_exec(db,update,callback,(void*)d,&err_msg);

cout<<"\n";
cout<<"Delete from stud table where rollno=18120 and display table after display";
rc=sqlite3_exec(db,del,callback,(void*)d,&err_msg);
if( rc != SQLITE_OK ) 
{
      cout<<"SQL error:"<< err_msg<<endl;
      sqlite3_free(err_msg);
}
else 
{
cout<<"\n";
cout<<"Operation done successfully";
}
   sqlite3_close(db);
   return 0;

}
