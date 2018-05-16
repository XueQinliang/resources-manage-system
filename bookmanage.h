#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h>
#include <string.h>
#include <vector>  
#include <fstream>  
#include <sstream>
#include <io.h>  
#include <windows.h>
using namespace std;
#define MAX_BOOK_AMOUNT 100
#define MAX_LENDBOOK_AMOUNT 10
#define WAIT_NUMBER 50
struct bookinfo{
	char name[40];//书名 
	char arthor[40];//作者 
	char sear[40];//ISBN号码 
	char publish[40];//出版社 
	int amount;//某本书总数 
	int lamount;//某本书可借出的总数（剩下一部分是各个用户已借走的） 
}info[MAX_BOOK_AMOUNT];//一个存放书籍信息的结构体数组 
int if_continue_use=1;//主函数中提到的全局变量，用来决定用户是否继续使用 
class book_manage{//书籍管理类，用来提取文件中存放的书籍信息、展示书籍目录、管理员管理书籍目录等功能 
    public: 
    book_manage(int k){//自动调用的构造函数，通过菜单让用户输入不同的数字来决定调用哪一功能 
    	if(k==0) book_read();//这个函数是用来将文件中的信息读入到数组中的 
    	if(k==1) show();//展示现有书籍目录 
    	if(k==2) realdatabase();//管理员管理书籍目录 
	}
	int bisearch(char a[],int left,int right){//二分查找，用来按照ISBN号码快速找书 
	int m,c=0;    
    m=(left+right)/2;    
    if(strcmp(info[m].sear,a)==0){    
        c=1;    
        return m;}    
    if(left-right>0&&c==0)
    return -1;    
    if(strcmp(info[m].sear,a)<0){    
    return bisearch( a,left, m-1 );    
    }    
    if(strcmp(info[m].sear,a)>0){    
    return bisearch( a, m+1, right);    
    }
}
private:
    void book_read(){  
	FILE *fp;
	if ((fp = fopen("F:\\图书管理系统\\书籍信息库.csv", "r")) == NULL) {
		cout<<"************************\n"; 
		cout<<"*  现在书库中还没有书  *\n";
		cout<<"************************\n";
		return ;
	}
	int k,k1,k2,k3;
	for(int i=0;i<MAX_BOOK_AMOUNT;i++){//读取csv文件中的信息 
		char mmm[200]; 
		for(int l=0;l<200;l++)
		mmm[l]='\0'; 
	    fgets(mmm,200,fp); 
	    for(k=0;k<40;k++){
	    	if(mmm[k]==','){
	    		strncpy(info[i].name,mmm,k);
	    		info[i].name[k]='\0';
				break; 
			}
		}
		char nu[40];
		for(k1=k+1;k1<k+41;k1++){
			if(mmm[k1]==','){
				strncpy(nu,mmm+k+1,k1-k-1);
				if(atoi(nu)!=0)
				info[i].amount=atoi(nu);
				break;
			}
		} 
		int k11;
		char nu1[40];
		for(k11=k1+1;k11<k1+41;k11++){
			if(mmm[k11]==','){
				strncpy(nu1,mmm+k1+1,k11-k1-1);
				if(atoi(nu1)!=0)
				info[i].lamount=atoi(nu1);
				break;
			}
		}
		for(k2=k11+1;k2<k11+41;k2++){
			if(mmm[k2]==','){
	    		strncpy(info[i].sear,mmm+k11+1,k2-k11-1);
	    		info[i].sear[k2-k11-1]='\0';
				break; 
			}
		}
		for(k3=k2+1;k3<k2+41;k3++){
			if(mmm[k3]==','){
	    		strncpy(info[i].arthor,mmm+k2+1,k3-k2-1);
	    		info[i].arthor[k3-k2-1]='\0';
				break; 
			}
		}
		int k4;
		for(k4=k3+1;k4<k3+41;k4++){ 
	    	strncpy(info[i].publish,mmm+k3+1,k4-k3-1);
		}
		} 		
    }
        void show(){
		int i=0; 
		cout<<"***********************\n";
		cout<<"*   实体书单列表如下  *\n";
		cout<<"***********************\n";
        while(i<MAX_BOOK_AMOUNT) {//刚刚读到数组中的文件的信息现在可以以数组中的数据形式来展示出来 
        	if(info[i].name[0]!='\0')
		    cout<<i+1<<"、书名:"<<info[i].name<<"  总数量:"<<info[i].amount<<" 在馆数量:"<<info[i].lamount<<"  ISBN号码:"<<info[i].sear<<"  作者:"<<info[i].arthor<<" 出版社:"<<info[i].publish;
		    else break;
			i++;
		}
	} 
void realdatabase(){
		char a[40]; 
		mmp:
		cout<<"*********************************************\n";
		cout<<"* 如果添加书籍，请输1 * 如果减少书籍，请输2 *\n";
		cout<<"*********************************************\n";
		cin>>a;
		if (strcmp(a,"1")==0){
			cout<<"**************************\n";
			cout<<"*       请输入书名       *\n";
			cout<<"**************************\n";
			char na[40],ar[40],sr[40],pb[40];
			cin>>na;
			cout<<"**************************\n";
			cout<<"*    请输入出版社名称    *\n";
			cout<<"**************************\n";
			cin>>pb;
			cout<<"**************************\n";
			cout<<"*     请输入ISBN号码     *\n";
			cout<<"**************************\n";
			cin>>sr;
			cout<<"**************************\n";
			cout<<"*   请输入要增加的数量   *\n";
			cout<<"**************************\n";
			int num;
			cin>>num;//管理员输入书籍的各种信息 
			int n=bisearch(sr,0,MAX_BOOK_AMOUNT-1);
				if(n!=-1){//如果已经有相同ISBN号码的书，则视为添加的为同一本书 
					cout<<"*********************************************\n";
					cout<<"库藏中已有该书\n";
					cout<<"原有"<<info[n].amount<<"本，"; 
					info[n].amount+=num; 
					info[n].lamount+=num; 
					cout<<"现有"<<info[n].amount<<"本\n";
					cout<<"********************************************\n";
					goto haha; 
				}else{
				cout<<"**************************\n";
				cout<<"*     库藏中还没有该书   *\n";
				cout<<"**************************\n";
				cout<<"*       请输入作者名     *\n";
				cout<<"**************************\n";
				cin>>ar;
				for(int i=0;i<MAX_BOOK_AMOUNT;i++){
					if(strcmp(info[i].sear,sr)<0){//这里确保建立书籍目录时即为按ISBN号码有序建立，便于二分查找并避免排序 
						for(int j=MAX_BOOK_AMOUNT-1;j>i;j--){
							info[j]=info[j-1];
						}
						strcpy(info[i].name,na);
						strcpy(info[i].arthor,ar);
						strcpy(info[i].sear,sr);
						strcpy(info[i].publish,pb);
						strcat(info[i].publish,"\n");
						info[i].amount=num;
						info[i].lamount=num;
						int i=0;
						while(i<MAX_BOOK_AMOUNT) {
        	                if(info[i].name[0]!='\0')
		                        cout<<i+1<<"、书名:"<<info[i].name<<"  总数量:"<<info[i].amount<<" 在馆数量:"<<info[i].lamount<<"  ISBN号码:"<<info[i].sear<<"  作者:"<<info[i].arthor<<" 出版社:"<<info[i].publish;
		                        i++;
		                    }
						goto haha; 
					}
				}
			} 
			haha:
			cout<<"\n************\n";
			cout<<"* 录入完成 *\n";
			cout<<"************\n"; 
	        ofstream outFile;  
            outFile.open("F:\\图书管理系统\\书籍信息库.csv", ios::out); 
	        for(int i=0;i<MAX_BOOK_AMOUNT;i++){//这里需要拿数组信息来更新文件中的信息 
	        	if(info[i].name[0]=='\0') break;
		        outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
			}  
	}else if(strcmp(a,"2")==0){
		char sar[40];
		f: 
		cout<<"******************************************\n";
		cout<<"*   请输入正确的要减少的书籍的ISBN号码   *\n";
		cout<<"******************************************\n";
		cin>>sar;
		int r=bisearch(sar,0,MAX_BOOK_AMOUNT-1);
		if(r==-1)
		goto f;
		cout<<"******************************************\n";
		cout<<"*           输入要减少的数量             *\n";
		cout<<"******************************************\n";
		int numb;
		cin>>numb;
		if(info[r].amount>numb){ 
		    info[r].amount-=numb;
            info[r].lamount-=numb;//如果书籍总数减少，那么可借数量也相应减少 
		}
		else if(info[r].amount==numb){
		    for(int j=r;j<MAX_BOOK_AMOUNT-1;j++){
			    info[j]=info[j+1];//如果减少的本书直接等于此书总数，则删除该书的名录 
		    }
		} 
		ofstream outFile;  
        outFile.open("F:\\图书管理系统\\书籍信息库.csv", ios::out); 
	    for(int i=0;i<MAX_BOOK_AMOUNT;i++){//更新文件 
		    outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
	    } 
		cout<<"\n************\n";
			cout<<"* 减少完成 *\n";
			cout<<"************\n"; 
		 
	}else{
		goto mmp;
	}	
}
public:
~book_manage(){ 
	if(if_continue_use==2)
	cout<<"************************************\n";
}
}book(0); //这里先生成一个对象，初值为0，即将文件中的信息先读到数组中来，这些数据之后会用到 
class boro_lend{//这个类是借书还书类 ，主要是用户借书和还书操作使用 
	public: 
	        struct userbook{//存放用户借书信息的结构体，这里相比书籍管理类的结构体少了数量，因为用户不需要记录库藏书籍数量 
	            char name[40];
	            char arthor[40]; 
	            char sear[40];
	            char publish[40]; 
            }ldbk[MAX_LENDBOOK_AMOUNT];
            int lendbooknum=0;//一个的借书数量，初值设为0 
		    boro_lend(char *username){//这个构造函数的参数为用户名，确定借书还书的对象 
		    	cout<<"************************\n"; 
		        cout<<"*       我借的书       *\n";
		        cout<<"************************\n";
		    for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){
		    	ldbk[i].arthor[0]='\0';
		    	ldbk[i].sear[0]='\0';
		    	ldbk[i].name[0]='\0';
		    	ldbk[i].publish[0]='\0';//结构体初始化 
			}
			char filename[50];//路径+文件名，之后打开 
	        strcpy(filename,"F:\\图书管理系统\\用户信息库\\");
	        strcat(filename,username);
	        strcat(filename,".csv");      
	        FILE *f;
	        if ((f = fopen(filename, "r")) == NULL) {
	        	cout<<"************************\n";
			    cout<<"*   你现在还没有借书   *\n"; 
			    cout<<"************************\n";
		        goto down;
	        }
	        int k,k1,k2,k3;
	        for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){//从文件中读取用户现在的借书信息 
		        char mmm[200]; 
		        for(int l=0;l<200;l++)
		        mmm[l]='\0'; 
	            fgets(mmm,200,f);
	        for(k=0;k<40;k++){
	    	    if(mmm[k]==','){
	    		    strncpy(ldbk[i].name,mmm,k);
	    		    ldbk[i].name[k]='\0';
				    break; 
			    }
		    }
		    for(k1=k+1;k1<k+41;k1++){
			    if(mmm[k1]==','){
				    strncpy(ldbk[i].sear,mmm+k+1,k1-k-1);
				    ldbk[i].sear[k1-k-1]='\0';
				    break;
			    }
		    }  
		    for(k3=k1+1;k3<k1+41;k3++){
			    if(mmm[k3]==','){
				    strncpy(ldbk[i].arthor,mmm+k1+1,k3-k1-1);
				    ldbk[i].arthor[k3-k1-1]='\0';
				    break;
			    }
		    }
		    for(k2=k3+1;k2<k3+41;k2++){ 
	    	    strncpy(ldbk[i].publish,mmm+k3+1,k2-k3-1);
		    }
		    if(ldbk[i].name[0]!='\0'){ 
		        cout<<i+1<<"、书名:"<<ldbk[i].name<<" ISBN号码:"<<ldbk[i].sear<<" 作者:"<<ldbk[i].arthor<<" 出版社:"<<ldbk[i].publish;
		        lendbooknum=i+1;//算出借书总数 
		    } 
			} 
            down:
			    cout<<"*************************************************************\n";	
			    cout<<"*  输入1，按ISBN号码查找借书  *  输入2，按ISBN号码查找还书  *\n"; 
			    cout<<"*************************************************************\n";
        	int n;
			mpm:    cout<<"********************\n";
			        cout<<"*  请输入一个数字  *\n"; 
			        cout<<"********************\n";
			cin>>n;
			if(n==1) {//借书操作 
				    cout<<"********************\n";
				    cout<<"*  请输入ISBN号码  *\n";
				    cout<<"********************\n";
				char bkser[40];
				cin>>bkser;
				int nur=book.bisearch(bkser,0,MAX_BOOK_AMOUNT-1);
				if(nur==-1) {
					cout<<"********************\n";
					cout<<"* 书库中没有这本书 *\n";
					cout<<"********************\n";
					return;
				}
				if(info[nur].lamount==0){
					cout<<"********************\n";
					cout<<"*  该书已全部借出  *\n";
					cout<<"********************\n";
					return;
				}
				if(lendbooknum==MAX_LENDBOOK_AMOUNT){
					cout<<"********************\n";
					cout<<"* 你借的书已达上限 *\n";
					cout<<"********************\n";
					return; 
				} //如果上面所有的条件都不满足，才可以正常借书 
				for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){
					if(strcmp(ldbk[i].sear,bkser)<0){
						for(int j=MAX_LENDBOOK_AMOUNT-1;j>i;j--){
							ldbk[j]=ldbk[j-1];
						}
						strcpy(ldbk[i].name,info[nur].name);
						strcpy(ldbk[i].arthor,info[nur].arthor);
						strcpy(ldbk[i].sear,info[nur].sear);
						strcpy(ldbk[i].publish,info[nur].publish);
						cout<<info[nur].name<<" "<<info[nur].arthor<<" "<<info[nur].sear<<ends<<info[nur].publish<<ends;
						goto mp; 
					}
				}
				mp:{
					info[nur].lamount--;
					ofstream outFile;  
                    outFile.open("F:\\图书管理系统\\书籍信息库.csv", ios::out); 
	                for(int i=0;i<MAX_BOOK_AMOUNT;i++){
	                	if(strcmp(info[i].name,"\0")==0) break;
		                outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
	                }
	                cout<<"********************\n";
				    cout<<"*     借出成功     *\n"; 
				    cout<<"********************\n";
					}
        	    ofstream outFile;
			    outFile.open(filename, ios::out);
                for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){
                	if(strcmp(ldbk[i].name,"\0")!=0){ 
		            outFile << ldbk[i].name<< ',' << ldbk[i].sear << ',' << ldbk[i].arthor<<','<<ldbk[i].publish;} 
					else break; 
	            } 
		    }else if(n==2){//还书操作 
		    	cout<<"****************************\n";
		    	cout<<"* 请输入要还的书的ISBN号码 *\n";
		    	cout<<"****************************\n";
		    	char ser[40];
				cin>>ser;
				int b=0; 
				for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){
					if(strcmp(ldbk[i].sear,ser)==0){
						b=1;
						cout<<ldbk[i].name<<ends<<ldbk[i].arthor<<ends<<ldbk[i].sear<<ends<<ldbk[i].publish; 
						for(int j=i;j<MAX_LENDBOOK_AMOUNT;j++){
							ldbk[j]=ldbk[j+1];
						}
			            ofstream outFile;
			            outFile.open(filename, ios::out);
                        for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){
                        	if(strcmp(ldbk[i].name,"\0")!=0)
		                    outFile << ldbk[i].name<< ',' << ldbk[i].sear << ',' << ldbk[i].arthor<<','<<ldbk[i].publish;
					        else break; 
	                    }  
						goto hhh;
					}
				}
				if(b==0) {
					cout<<"****************************\n";
				    cout<<"*     你并没有借这本书     *\n";
				    cout<<"****************************\n";
				    return; 
				}    
				hhh:{
					int nur=book.bisearch(ser,0,MAX_BOOK_AMOUNT-1);//查找该书在书库中的位置 
					info[nur].lamount++;//可借数量++，代表此书已经还入书库 
					ofstream outFile;  
                    outFile.open("F:\\图书管理系统\\书籍信息库.csv", ios::out); 
	                for(int i=0;i<100;i++){//更新文件 
		                outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
	                }
	                cout<<"****************************\n";
				    cout<<"*         归还成功         *\n";
				    cout<<"****************************\n";
					}
			} else goto mpm; 
	    }
	    ~boro_lend(){//析构函数，在借还书籍行为结束之际打出一句话给用户 
	    	if(if_continue_use==2)
	    	cout<<"*******************\n";
	    	cout<<"*  欢迎下次借书   *\n";
	    	cout<<"*******************\n";
		}
};  
class readonl_download{//在线阅读电子书 
	public: readonl_download(int k){//k决定用户是在线阅读还是下载书籍 
		    FILE*fp;
		    if((fp=fopen("F:\\图书管理系统\\电子书信息库\\电子书目列表.csv","r"))==NULL){
		    	cout<<"**************************\n";
				cout<<"*   电子书库现在无库存   *\n";
				cout<<"**************************\n"; 
			}else {
				while(!feof(fp)){//展示现有电子书目录 
					char m;
					m=fgetc(fp);
					cout<<m;
				}
			}
			if(k==1)
			readon();//在线阅读函数 
			if(k==2)
			download(); //下载文件函数 
	        }
	        readonl_download(){//重载的构造函数，调用管理员录入电子书的函数 
	        	FILE*fp;
		        if((fp=fopen("F:\\图书管理系统\\电子书信息库\\电子书目列表.csv","r"))==NULL){
		    	    cout<<"**************************\n";
				    cout<<"*   电子书库现在无库存   *\n";
				    cout<<"**************************\n";  
			    }else {
			    	cout<<"******************\n";
			    	cout<<"*  电子书单如下  *\n";
			    	cout<<"******************\n";
				    while(!feof(fp)){//展示现有电子书目录 ，便于用户选择阅读、下载和管理员录入 
					    char m;
					    m=fgetc(fp);
					    cout<<m;
				    }
			    }
	        	managerinput();//管理员录入电子书的函数
			}
    private:void readon(){//在线阅读函数 
            char bookname[40];
            cout<<"**********************\n";
            cout<<"*  请输入要查找的书  *\n";
            cout<<"**********************\n";
            cin>>bookname;//用户通过输入书名，来找到书籍的电子文件，从而打开阅读 
	        strcpy(filename,"F:\\图书管理系统\\电子书信息库\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt");      
			FILE *fl;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"**********************\n";
				cout<<"* 查找的电子书不存在 *\n";
				cout<<"**********************\n";
				return ;
			}else { 
			cout<<"**********************\n";
			cout<<"*    图书全文如下    *\n";
			cout<<"**********************\n";
			while (!feof(fl)) {//一个一个字符将电子版书籍打到屏幕上在线阅读 
                char c;
                c=fgetc(fl);
                cout<<c; 
		    }} 
		    fclose(fl);
	    }
	    void download(){//下载函数，用户可以将书籍的电子版文件从后台下载到自己的电脑中，在本程序中即下载到程序所在的文件夹中 
	    	char bookname[40];
	    	cout<<"*********************************\n";
            cout<<"*  请输入要下载的电子书的书名   *\n";
            cout<<"*********************************\n";
            cin>>bookname;
	        strcpy(filename,"F:\\图书管理系统\\电子书信息库\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt"); 
			strcat(bookname,".txt");     
			FILE *fl;
			FILE *out;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"*********************************\n";
				cout<<"*       查找的电子书不存在      *\n";
				cout<<"*********************************\n";
				return ;
			}
			out=fopen(bookname,"w");
			while (!feof(fl)) {//从一个文件读出来写入另一个文件中实现文件的复制和下载 
                char c;
                c=fgetc(fl);
                fputc(c,out); 
		    }
		    cout<<"*********************************\n";
			cout<<"*           下载完成            *\n";
			cout<<"*********************************\n"; 
		    fclose(fl);
	    	fclose(out);
		} 
	    void managerinput(){//管理员在线录入电子书的函数 
	    	FILE*rite;
	    	cout<<"******************************\n";
	    	cout<<"*     请输入要录入的书名     *\n";
	    	cout<<"******************************\n";
	    	char booknam[40];
			cin>>booknam;
			cout<<"*      请输入书的作者名      *\n"; 
			cout<<"******************************\n";
			char arthorname[40];
			cin>>arthorname;
			cout<<"*        请输入出版社        *\n";
			cout<<"******************************\n";
			char pubclub[40];
			cin>>pubclub;
			strcpy(filename,"F:\\图书管理系统\\电子书信息库\\");
	        strcat(filename,booknam);
	        strcat(filename,".txt"); //路径+书名，可以将以书名为名字的文本文件保存到指定的路径中 
			if((rite=fopen(filename,"w"))==NULL){
				cout<<"******************************\n";
				cout<<"*     无法正常录入电子书     *\n";
				cout<<"******************************\n";
	            return ;
			}
			getchar();
			char m;
			cout<<"**************************************************\n";
			cout<<"*  请录入书籍正文(最后加上一个“#”表示录入结束) *\n";
			cout<<"**************************************************\n";
	    	while((m=getchar())!='#'){
	    		fputc(m,rite);//录入书籍全文的过程，我采用一个一个字符写入文件中的方法 
			}
			fclose(rite);
			cout<<"*************************\n";
			cout<<"*      全文录入成功     *\n";
			cout<<"*************************\n";
			FILE*c;
			c=fopen("F:\\图书管理系统\\电子书信息库\\电子书目列表.csv","a");//这里是生成一个电子书的目录，便于用户查找电子书 
			fputs("书名:",c);
			fputs(booknam,c);
			fputc(',',c);
			fputs("作者:",c);
			fputs(arthorname,c);
			fputc(',',c);
			fputs("出版社:",c);
			fputs(pubclub,c);
			fputc(',',c);
			fputs("存储路径:",c);
			fputs(filename,c);
			fputc(',',c);
			fputc('\n',c); 
			fclose(c);
		} 
	    char filename[50];
        public:~readonl_download(){
        	if(if_continue_use==2)
        	cout<<endl;
        	cout<<"********************************\n";
	    	cout<<"*   欢迎下次使用此电子书系统   *\n";
	    	cout<<"********************************\n"; 
		}
}; 
class electric_article{//这个是管理和阅读电子论文的类，基本原理和电子图书类相同，但论文和书籍的要素不同，所以单独列类 
	public: electric_article(int k){//用户接口 
		    FILE*fp;
		    if((fp=fopen("F:\\图书管理系统\\电子论文信息库\\电子论文列表.csv","r"))==NULL){
		    	cout<<"********************************\n"; 
				cout<<"*     电子论文库现在无库存     *\n";
				cout<<"********************************\n";  
			}else {
				while(!feof(fp)){
					char m;
					m=fgetc(fp);
					cout<<m;
				}
			}
			if(k==1)
			readonarticle();//在线阅读论文 
			if(k==2)
			downloadarticle();//下载论文 
	        }
	        electric_article(){//管理员接口 
	        	FILE*fp;
		        if((fp=fopen("F:\\图书管理系统\\电子论文信息库\\电子论文列表.csv","r"))==NULL){
		    	    cout<<"********************************\n"; 
				    cout<<"*     电子论文库现在无库存     *\n";
				    cout<<"********************************\n";
			    }else {
			    	cout<<"********************************\n";
			    	cout<<"*       电子论文名录如下       *\n";
			    	cout<<"********************************\n";
				    while(!feof(fp)){
					    char m;
					    m=fgetc(fp);
					    cout<<m;
				    }
			    }
	        	managerinputarticle();//调用管理员管理电子论文的函数 
			}
	private:char filename[100];
	    void readonarticle(){
            char bookname[40];
            cout<<"********************************\n";
            cout<<"*     请输入要查找的论文标题   *\n";
            cout<<"********************************\n";
            cin>>bookname;
	        strcpy(filename,"F:\\图书管理系统\\电子论文信息库\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt");      
			FILE *fl;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"********************************\n";
				cout<<"*      查找的论文不存在        *\n";
				cout<<"********************************\n";
				return ;
			}else { 
			cout<<"********************************\n";
			cout<<"*         论文全文如下         *\n";
			cout<<"********************************\n";
			while (!feof(fl)) {
                char c;
                c=fgetc(fl);
                cout<<c; 
		    }} 
		    fclose(fl);
	    }
	    void downloadarticle(){
	    	char bookname[40];
	    	cout<<"********************************\n";
            cout<<"*    请输入要下载的论文标题    *\n";
            cout<<"********************************\n";
            cin>>bookname;
	        strcpy(filename,"F:\\图书管理系统\\电子论文信息库\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt"); 
			strcat(bookname,".txt");     
			FILE *fl;
			FILE *out;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"********************************\n";
				cout<<"*       查找的论文不存在       *\n";
				cout<<"********************************\n";
				return ;
			}
			out=fopen(bookname,"w");
			while (!feof(fl)) {
                char c;
                c=fgetc(fl);
                fputc(c,out); 
		    }
		    cout<<"********************\n";
			cout<<"*    下载完成      *\n";
			cout<<"********************\n"; 
		    fclose(fl);
	    	fclose(out);
		} 
		void managerinputarticle(){
	    	FILE*rite;
	    	cout<<"**********************************************\n";
	    	cout<<"*          请输入要录入的论文标题            *\n";
	    	cout<<"**********************************************\n";
	    	char booknam[40];
			cin>>booknam;
			getchar();
			cout<<"**********************************************\n";
			cout<<"*  请输入论文的作者名(请输入#以代表输入结束) *\n"; 
			cout<<"**********************************************\n";
			char arthorname[100];
			cin.getline(arthorname,100,'#');
			cout<<"**********************************************\n";
			cout<<"*                 请输入刊物                 *\n";
			cout<<"**********************************************\n";
			char pubclub[40];
			cin>>pubclub;
			cout<<"**********************************************\n";
			cout<<"*              请输入论文编号                *\n";
			cout<<"**********************************************\n";
			char anumber[40];
			cin>>anumber; 
			char time[40];
			cout<<"**********************************************\n";
			cout<<"*              请输入发表时间                *\n";
			cout<<"**********************************************\n";
			cin>>time; 
			strcpy(filename,"F:\\图书管理系统\\电子论文信息库\\");
	        strcat(filename,booknam);
	        strcat(filename,".txt"); 
			if((rite=fopen(filename,"w"))==NULL){
				cout<<"**********************************************\n";
				cout<<"*          无法正常录入电子论文              *\n";
				cout<<"**********************************************\n";
	            return ;
			}
			getchar();
			char m;
			cout<<"**********************************************\n";
			cout<<"*请录入论文全文(最后加一个“#”表示录入结束) *\n";
			cout<<"**********************************************\n";
	    	while((m=getchar())!='#'){
	    		fputc(m,rite);
			}
			fclose(rite);
			cout<<"**********************************************\n";
			cout<<"*               全文录入成功                 *\n";
			cout<<"**********************************************\n"; 
			FILE*c;
			c=fopen("F:\\图书管理系统\\电子论文信息库\\电子论文列表.csv","a");
			fputs("标题:",c);
			fputs(booknam,c);
			fputc(',',c);
			fputs("作者:",c);
			fputs(arthorname,c);
			fputc(',',c);
			fputs("刊物:",c);
			fputs(pubclub,c);
			fputc(',',c);
			fputs("编号:",c);
			fputs(anumber,c);
			fputc(',',c);
			fputs("时间",c);
			fputs(time,c);
			fputc(',',c); 
			fputs("存储路径:",c); 
			fputs(filename,c);
			fputc(',',c);
			fputc('\n',c); 
			fclose(c);
		}
		public:~electric_article(){
			if(if_continue_use==2)
			cout<<"**********************************************\n";
			cout<<"*     欢迎下次继续使用此电子论文操作系统     *\n";
			cout<<"**********************************************\n";
		}
}; 
class usermanage{//最主要的一个类，用户管理类，掌管着用户注册、用户登录、注销账号、修改密码等与用户相关的所有功能， 
	public:      //并且会在用户登录中使用上面实现的所有功能 
		usermanage(int Num){//一个共有的构造函数，负责把一个参数传进来，调用其它功能 
			No=Num;
			all_fouctions();
	    }
	private:void modify_num(int num){//用户在指导下修改参数，来调用其他功能 
	    	No=num;
		}
		void all_fouctions(){//本类的主要功能函数 
			if(No==0) screen();//将操作界面打到屏幕上指导用户操作，这个也是主函数声明对象时最终默认首先调用的功能函数 
			else if(No==1) user_register();//用户注册函数，分管理员注册和普通用户注册，需要经过审核才能成功 
	        else if(No==2) log_on();//登录函数，连接着其余四个类 
	        else if(No==3) user_delect();//用户注销 
	        else if(No==4) modify_password();//修改密码 
		}
		void screen(){
			cout<<"**********************************\n";
			cout<<"*********请选择你的操作***********\n";
			cout<<"**********************************\n";
			cout<<"*  1、用户注册  *  2、用户登录   *\n";
			cout<<"**********************************\n";
			cout<<"*  3、用户注销  *  4、修改密码   *\n";
			cout<<"**********************************\n";
			int n;
			cin>>n;
			modify_num(n);
			all_fouctions();
	    }
	    void user_register();
	    void manage_register();//管理员可以直接添加用户 
	    void log_on();
	    void user_delect();
	    void manage_delect();//管理员可以直接注销掉任意用户的账号 
	    void modify_password();
	    void authorize();//管理员专用审核函数 
        char username[40];
	    char password[40];
	    int sf; //表示用户身份是管理员还是普通用户 
		int scces_log=0;//成功登录的标志，在登录函数中使用，只有这个值发生改变才能算登录成功，进行其他功能的操作 
		int No;//传参中间用的一个值 
		int if_re_sus=1;//表示注册成功 
		struct authorize_users{//管理员审核用户时需要得到用户名和注册身份信息 
			char username[40];
			char identity[10];
		}wait[WAIT_NUMBER];
		void fwrit(){//注册时调用 
			ofstream outFile;
	        char filename[50],anotherflnm[50];
	        strcpy(filename,"F:\\图书管理系统\\用户待审核信息库\\");//用户自行注册后先进入待审核信息库中 
	        strcat(filename,username);
	        strcat(filename,".txt");
	        strcpy(anotherflnm,"F:\\图书管理系统\\用户信息库\\");
	        strcat(anotherflnm,username);
	        strcat(anotherflnm,".txt");
	        FILE *fp;
	        FILE *fl;
	        int p1=0,p2=0;
	        if((fp = fopen(filename, "r"))==NULL)
	            p1=1;
			if((fl=fopen(anotherflnm,"r"))==NULL)
			    p2=1;
			if (p1==1&&p2==1) {//判断用户名有无重复 ，如果不重复，才允许设定密码，否则注册失败 
				ofstream outFile;
				outFile.open(filename, ios::out);
	            outFile<<password<<sf<<endl;//将密码和身份信息输入文件中保存 
	            outFile.close();
				FILE*csv;
				csv=fopen("F:\\图书管理系统\\用户待审核信息库\\用户待审核信息表.csv","a");//建立待审核用户名单，便于管理员审核 
				fputs(username,csv);
				fputc(',',csv);
				if(sf==1)
				fputs("普通用户\n",csv);
				else if(sf==2)
				fputs("管理员\n",csv);
				fclose(csv);
	        }else {
	        	cout<<"********************\n";
	        	cout<<"* 此用户名已被注册 *\n";
	        	cout<<"********************\n"; 
				fclose(fp);
				fclose(fl);
				if_re_sus=0; //标志 
			} 
		}
		void derect_fwrit(){//管理员添加的用户直接通过审核进入用户信息库 
			ofstream outFile;
	        char filename[50],anotherflnm[50];
	        strcpy(filename,"F:\\图书管理系统\\用户待审核信息库\\");
	        strcat(filename,username);
	        strcat(filename,".txt");
	        strcpy(anotherflnm,"F:\\图书管理系统\\用户信息库\\");
	        strcat(anotherflnm,username);
	        strcat(anotherflnm,".txt");
	        int if_multiple1=1,if_multiple2=1;
	        FILE *fp;
			if((fp = fopen(filename, "r")) != NULL){
				if_multiple1=0;
			}
			fclose(fp);
	        FILE *fl;
			if ((fl=fopen(anotherflnm,"r"))!=NULL){
			    if_multiple2=0;
			}
			fclose(fl);
			if(if_multiple1==1&&if_multiple2==1){//判断用户名是否已经被注册 
				outFile.open(anotherflnm, ios::out);
	            outFile<<password<<sf<<endl; 
	        }else {
	        	cout<<"********************\n";
	        	cout<<"* 此用户名已被注册 *\n";
	        	cout<<"********************\n"; 
				if_re_sus=0; 
			} 
		}
		int if_name_exist=1;  //用户名是否存在的标志，登录时用到 
		void match(){
			FILE *fp;
			char filename[50];
			strcpy(filename,"F:\\图书管理系统\\用户信息库\\");
	        strcat(filename,username);
	        strcat(filename,".txt");  
	        if ((fp = fopen(filename, "r")) == NULL) {
	        	cout<<"********************\n";
	        	cout<<"*    用户不存在    *\n";
	        	cout<<"********************\n"; 
	        	if_name_exist=0;
				return; 
	        }
            char pswrd[40];
            fgets(pswrd,40,fp);
            int pswrd_len=strlen(pswrd);
			sf=pswrd[pswrd_len-2]-'0';
            pswrd[pswrd_len-2]='\0';  //从文件中解析出密码和身份信息 
            if(strcmp(pswrd,password)==0){
            	scces_log=1;//成功登录的标志 
			}
			fclose(fp); 
		};
		public:~usermanage(){
			if(if_continue_use==2){ 
			cout<<"************************************\n";
			cout<<"*欢迎下次使用此综合管理系统o(^▽^)o*\n";} 
		}
};
void usermanage::user_register(){
	cout<<"********************\n"; 
	cout<<"*   请设定用户名   *\n";
	cout<<"********************\n"; 
	cin>>username;
	cout<<"********************\n"; 
	cout<<"*    请设定密码    *\n";
	cout<<"********************\n"; 
	cin>>password;
	up:
	cout<<"***************************************\n";
	cout<<"*  请选择身份，1、普通用户,2、管理员  *\n";
	cout<<"***************************************\n";
	char c[10];
	cin>>c;
	if(strcmp(c,"1")==0)sf=1;
	else if(strcmp(c,"2")==0)sf=2;
	else goto up;
	fwrit();
	sf=0;
	if(if_re_sus==1){ 
	cout<<"**************************************\n";
	cout<<"*   注册成功，请等待管理员审核通过   *\n";
	cout<<"**************************************\n";} 
	else {
	cout<<"***************\n";
	cout<<"*   注册失败  *\n";
	cout<<"***************\n";} 
}
void usermanage::manage_register(){
	cout<<"********************\n"; 
	cout<<"*请设定添加的用户名*\n";
	cout<<"********************\n"; 
	cin>>username;
	cout<<"********************\n"; 
	cout<<"*    请设定密码    *\n";
	cout<<"********************\n"; 
	cin>>password;
	up:
	cout<<"***************************************\n";
	cout<<"*  请选择身份，1、普通用户,2、管理员  *\n";
	cout<<"***************************************\n";
	char c[10];
	cin>>c;
	if(strcmp(c,"1")==0)sf=1;
	else if(strcmp(c,"2")==0)sf=2;
	else goto up;
	derect_fwrit();
	sf=0;
	if(if_re_sus==1){
	cout<<"**************************************\n";
	cout<<"*   注册成功，请等待管理员审核通过   *\n";
	cout<<"**************************************\n";}
	else {
	cout<<"***************\n";
	cout<<"*   注册失败  *\n";
	cout<<"***************\n";}
}

void usermanage::user_delect(){
	cout<<"************************\n"; 
	cout<<"*请输入你要注销的用户名*\n";
	cout<<"************************\n"; 
	cin>>username;
	cout<<"************************\n"; 
	cout<<"* 请输入此用户名的密码 *\n";
	cout<<"************************\n"; 
	cin>>password;//用户注销前必须先验证密码 
	match();
	if(scces_log==1){
		char txtfilename[50],csvfilename[50];
	strcpy(txtfilename,"F:\\图书管理系统\\用户信息库\\");
    strcat(txtfilename,username);
    strcat(txtfilename,".txt");  
    strcpy(csvfilename,"F:\\图书管理系统\\用户信息库\\");
    strcat(csvfilename,username);
    strcat(csvfilename,".csv");  
    if(remove(txtfilename)==0){
    	if(remove(csvfilename)==0)
    	    cout<<"************\n"; 
	    	cout<<"* 注销成功 *\n";
	    	cout<<"************\n";
		}else {
		cout<<"************\n";
		cout<<"* 注销失败 *\n";
		cout<<"************\n";}
	}else {
	cout<<"************\n";
	cout<<"* 密码错误 *\n";
	cout<<"************\n";} 
	scces_log==0;
} 
void usermanage::manage_delect(){
	cout<<"****************************\n";
	cout<<"*  请输入你要删除的用户名  *\n";
	cout<<"****************************\n";
	cin>>username;
	char txtfilename[50],csvfilename[50];
	strcpy(txtfilename,"F:\\图书管理系统\\用户信息库\\");
    strcat(txtfilename,username);
    strcat(txtfilename,".txt");  
    strcpy(csvfilename,"F:\\图书管理系统\\用户信息库\\");
    strcat(csvfilename,username);
    strcat(csvfilename,".csv");  
    if(remove(txtfilename)==0){
        remove(csvfilename);//管理员直接删除掉用户的身份信息和借书信息 
        cout<<"************\n";
	    cout<<"* 删除成功 *\n";
	    cout<<"************\n";
	}else {
	    cout<<"****************************\n"; 
	    cout<<"* 删除失败，该用户并不存在 *\n";
	    cout<<"****************************\n";
    }
} 
void usermanage::modify_password(){
	cout<<"****************\n";
	cout<<"* 请输入用户名 *\n";
	cout<<"****************\n";
	cin>>username;
	cout<<"****************\n";
	cout<<"* 请输入原密码 *\n";
	cout<<"****************\n";
	cin>>password;
	match();//修改密码前也要先验证是否正确以确保本人操作 
	if(scces_log==1){
		cout<<"****************\n";
		cout<<"* 请输入新密码 *\n";
		cout<<"****************\n";
		char new_password[40]; 
		cin>>new_password;
		ofstream outFile;
		char filename[50];
	    strcpy(filename,"F:\\图书管理系统\\用户信息库\\");
	    strcat(filename,username);
	    strcat(filename,".txt");  
		FILE*fp;  
		if ((fp = fopen(filename, "r")) != NULL) {
				outFile.open(filename, ios::out);
	            outFile<<new_password<<sf<<endl; //更新密码 
	        }else {
			cout<<"************\n"; 
			cout<<"* 修改失败 *\n"; 
			cout<<"************\n";} 
	} else {
	cout<<"************\n";
	cout<<"* 密码错误 *\n"; 
	cout<<"************\n";}
}
void usermanage::authorize(){//审核函数 
	for(int i=0;i<WAIT_NUMBER;i++){
		wait[i].username[0]=wait[i].identity[0]='\0';
	}
	FILE*csv;
	if((csv=fopen("F:\\图书管理系统\\用户待审核信息库\\用户待审核信息表.csv","r"))==NULL){
		cout<<"******************\n";
		cout<<"*  审核系统异常  *\n";
		cout<<"******************\n";
		return;
	}else{
		int number=0;
		while(!feof(csv)){
			char info[50];
			fgets(info,50,csv);
			for(int i=0;i<WAIT_NUMBER;i++){//把待审核用户的名单存入数组便于操作 
				if(info[i]==','){
					strncpy(wait[number].username,info,i);
					strcpy(wait[number].identity,info+i+1);
					break;
				}
			}
			number++; //在记录用户数量 
		} 
		wait[number-1].username[0]=wait[number-1].identity[0]='\0';
		for(int i=0;i<number-1;i++){
			cout<<i+1<<"、用户名："<<wait[i].username<<" 注册身份："<<wait[i].identity; 
		}
		if(number<=1){ 
		    cout<<"**********************\n";
		    cout<<"*  没有待审核的用户  *\n";
		    cout<<"**********************\n";
		    return;
		}
		cout<<"**************************************\n";
		cout<<"*   请选择你允许审核通过的用户序号   *\n";
		cout<<"**************************************\n"; 
		int permit_number;
		cin>>permit_number;//通过选择编号来选择通过审核的用户，然后将其信息移到用户信息库中，删除其在待审核信息库中的信息 
		char sOriPathName[50];
		char sNewPathName[50];
		strcpy(sOriPathName,"F:\\图书管理系统\\用户待审核信息库\\");
	    strcat(sOriPathName,wait[permit_number-1].username);
	    strcat(sOriPathName,".txt");  
	    strcpy(sNewPathName,"F:\\图书管理系统\\用户信息库\\");
	    strcat(sNewPathName,wait[permit_number-1].username);
	    strcat(sNewPathName,".txt");
		FILE*Ori;
		if((Ori=fopen(sOriPathName,"r"))==NULL){
			cout<<"**************************************\n";
			cout<<"*        此待审核用户不存在          *\n";
			cout<<"**************************************\n";
			return;
		}
		char pswd_sf[20];
		fgets(pswd_sf,20,Ori);
		fclose(Ori);
		
		FILE*Try;
		if((Try=fopen(sNewPathName,"r"))!=NULL){
			cout<<"**************************************\n";
			cout<<"*          此用户名已被注册          *\n";
			cout<<"**************************************\n";
			return;
		}
		fclose(Try);
		FILE*New;
		New=fopen(sNewPathName,"w");
		fputs(pswd_sf,New);
		fclose(New);
		cout<<"**************************************\n";
		cout<<"*              审核完成              *\n";
		cout<<"**************************************\n";
		remove(sOriPathName);
		for(int n=permit_number;n<=number;n++){
			wait[n-1]=wait[n];
		}
		wait[number-1].username[0]=wait[number-1].identity[0]='\0';
		ofstream outFile;
		outFile.open("F:\\图书管理系统\\用户待审核信息库\\用户待审核信息表.csv", ios::out);
		for(int n=0;n<number-1;n++){//更新待审核列表 
			outFile<<wait[n].username<<','<<wait[n].identity; 
		}
	}	
}
void usermanage::log_on(){//登陆函数，普通用户和管理员都通过这个函数操作 
	cout<<"******************\n";
	cout<<"*  请输入用户名  *\n";
	cout<<"******************\n";
	cin>>username;
	cout<<"******************\n";
	re:
	cout<<"*   请输入密码   *\n";
	cout<<"******************\n";
	cin>>password;
	match(); //身份验证 
	if(if_name_exist==0){
		return;
	}
	if(scces_log==1){
		cout<<"**************\n";
		cout<<"*  登录成功  *\n";
		cout<<"**************\n";
		cout<<"************************************************************\n";
		cout<<"亲爱的"<<username<<",你好＼（＾ｏ＾）／～\n";
		cout<<"************************************************************\n";
		cout<<"*********************\n";
		cout<<"*   欢迎使用本系统  *\n";
		cout<<"*********************\n"; 
	}else {
		cout<<"***************\n";
	    cout<<"*   密码错误  *\n";
	    cout<<"***************\n";
	    goto re;
		}
	if(sf==2){ //管理员可以选择自己使用普通用户模式还是管理员模式 
	cout<<"*******************************************\n";
	cout<<"*     请选择进入用户模式或者管理员模式    *\n";
	cout<<"*******************************************\n"; 
	cout<<"*     用户模式请输1  *  管理员模式请输2   *\n";
	cout<<"*******************************************\n";
	cin>>sf; //确定模式 
	} 
	scces_log=0;
	if(sf==1){//普通用户权限 
		int k;
		while(1){ 
		cout<<"\n";
		cout<<"**************************************************\n";
		cout<<"*   操作实体书,请输入1  *   操作电子书,请输入2   *\n";
		cout<<"**************************************************\n";
		cout<<"*  操作电子论文,请输入3 *    退出登录,请输入0    *\n"; 
		cout<<"**************************************************\n";
		cin>>k;
		if(k==1){
		book_manage(0);//把书籍目录的信息读到数组中 
		book_manage(1);//展示书籍目录 
		boro_lend brld(username);//可以借书和还书 
		}
		else if(k==2){
			cout<<"*********************************************\n";
			cout<<"*  在线阅读请输入1  *  下载电子文档请输入2  *\n";
			cout<<"*********************************************\n";
			cin>>k;
		    readonl_download read(k);//在线阅读或者下载文档 
		}
		else if(k==3){
			cout<<"*********************************************\n";
			cout<<"*  在线阅读请输入1  *  下载电子论文请输入2  *\n";
			cout<<"*********************************************\n";
			cin>>k;
		    electric_article elc(k);
		} 
		else if(k==0)//退出登录 
		break; 
		} 
	}else if(sf==2){//管理员权限 
		int k;
		while(1){ 
		cout<<"\n";
		cout<<"**************************************************\n";
		cout<<"*   操作实体书,请输入1  *   操作电子书,请输入2   *\n";
		cout<<"**************************************************\n";
		cout<<"*  操作电子论文,请输入3 *    用户管理，请输入4   *\n"; 
		cout<<"**************************************************\n"; 
		cout<<"*              退出登录，请输入0                 *\n";
		cout<<"**************************************************\n"; 
		cin>>k;
		if(k==1){
		book_manage(0);//把书籍目录的信息读到数组中  
		book_manage(1);//展示书籍目录 
		book_manage(2);//添加或者减少存书 
		} 
		else if(k==2)
		readonl_download read;//管理员录入电子书 
		else if(k==3)
		electric_article elc;//管理员录入电子论文 
		else if(k==4){//用户管理功能，管理员可以管理用户 
			int choice;
			cout<<"*****************************************************************\n";
			cout<<"*   添加用户请输1   *   删除用户请输2   *   审核用户注册请输3   *\n";
			cout<<"*****************************************************************\n"; 
			cin>>choice;
			if(choice==1){
				manage_register();//添加用户 
			} 
			if(choice==2){
				manage_delect();//删除用户 
			} 
			if(choice==3){
				authorize();//审核用户 
			} 
		} 
		else if(k==0)//退出登录 
		break;} 
	}
}   
