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
	char name[40];//���� 
	char arthor[40];//���� 
	char sear[40];//ISBN���� 
	char publish[40];//������ 
	int amount;//ĳ�������� 
	int lamount;//ĳ����ɽ����������ʣ��һ�����Ǹ����û��ѽ��ߵģ� 
}info[MAX_BOOK_AMOUNT];//һ������鼮��Ϣ�Ľṹ������ 
int if_continue_use=1;//���������ᵽ��ȫ�ֱ��������������û��Ƿ����ʹ�� 
class book_manage{//�鼮�����࣬������ȡ�ļ��д�ŵ��鼮��Ϣ��չʾ�鼮Ŀ¼������Ա�����鼮Ŀ¼�ȹ��� 
    public: 
    book_manage(int k){//�Զ����õĹ��캯����ͨ���˵����û����벻ͬ������������������һ���� 
    	if(k==0) book_read();//����������������ļ��е���Ϣ���뵽�����е� 
    	if(k==1) show();//չʾ�����鼮Ŀ¼ 
    	if(k==2) realdatabase();//����Ա�����鼮Ŀ¼ 
	}
	int bisearch(char a[],int left,int right){//���ֲ��ң���������ISBN����������� 
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
	if ((fp = fopen("F:\\ͼ�����ϵͳ\\�鼮��Ϣ��.csv", "r")) == NULL) {
		cout<<"************************\n"; 
		cout<<"*  ��������л�û����  *\n";
		cout<<"************************\n";
		return ;
	}
	int k,k1,k2,k3;
	for(int i=0;i<MAX_BOOK_AMOUNT;i++){//��ȡcsv�ļ��е���Ϣ 
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
		cout<<"*   ʵ���鵥�б�����  *\n";
		cout<<"***********************\n";
        while(i<MAX_BOOK_AMOUNT) {//�ոն��������е��ļ�����Ϣ���ڿ����������е�������ʽ��չʾ���� 
        	if(info[i].name[0]!='\0')
		    cout<<i+1<<"������:"<<info[i].name<<"  ������:"<<info[i].amount<<" �ڹ�����:"<<info[i].lamount<<"  ISBN����:"<<info[i].sear<<"  ����:"<<info[i].arthor<<" ������:"<<info[i].publish;
		    else break;
			i++;
		}
	} 
void realdatabase(){
		char a[40]; 
		mmp:
		cout<<"*********************************************\n";
		cout<<"* �������鼮������1 * ��������鼮������2 *\n";
		cout<<"*********************************************\n";
		cin>>a;
		if (strcmp(a,"1")==0){
			cout<<"**************************\n";
			cout<<"*       ����������       *\n";
			cout<<"**************************\n";
			char na[40],ar[40],sr[40],pb[40];
			cin>>na;
			cout<<"**************************\n";
			cout<<"*    ���������������    *\n";
			cout<<"**************************\n";
			cin>>pb;
			cout<<"**************************\n";
			cout<<"*     ������ISBN����     *\n";
			cout<<"**************************\n";
			cin>>sr;
			cout<<"**************************\n";
			cout<<"*   ������Ҫ���ӵ�����   *\n";
			cout<<"**************************\n";
			int num;
			cin>>num;//����Ա�����鼮�ĸ�����Ϣ 
			int n=bisearch(sr,0,MAX_BOOK_AMOUNT-1);
				if(n!=-1){//����Ѿ�����ͬISBN������飬����Ϊ��ӵ�Ϊͬһ���� 
					cout<<"*********************************************\n";
					cout<<"��������и���\n";
					cout<<"ԭ��"<<info[n].amount<<"����"; 
					info[n].amount+=num; 
					info[n].lamount+=num; 
					cout<<"����"<<info[n].amount<<"��\n";
					cout<<"********************************************\n";
					goto haha; 
				}else{
				cout<<"**************************\n";
				cout<<"*     ����л�û�и���   *\n";
				cout<<"**************************\n";
				cout<<"*       ������������     *\n";
				cout<<"**************************\n";
				cin>>ar;
				for(int i=0;i<MAX_BOOK_AMOUNT;i++){
					if(strcmp(info[i].sear,sr)<0){//����ȷ�������鼮Ŀ¼ʱ��Ϊ��ISBN���������������ڶ��ֲ��Ҳ��������� 
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
		                        cout<<i+1<<"������:"<<info[i].name<<"  ������:"<<info[i].amount<<" �ڹ�����:"<<info[i].lamount<<"  ISBN����:"<<info[i].sear<<"  ����:"<<info[i].arthor<<" ������:"<<info[i].publish;
		                        i++;
		                    }
						goto haha; 
					}
				}
			} 
			haha:
			cout<<"\n************\n";
			cout<<"* ¼����� *\n";
			cout<<"************\n"; 
	        ofstream outFile;  
            outFile.open("F:\\ͼ�����ϵͳ\\�鼮��Ϣ��.csv", ios::out); 
	        for(int i=0;i<MAX_BOOK_AMOUNT;i++){//������Ҫ��������Ϣ�������ļ��е���Ϣ 
	        	if(info[i].name[0]=='\0') break;
		        outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
			}  
	}else if(strcmp(a,"2")==0){
		char sar[40];
		f: 
		cout<<"******************************************\n";
		cout<<"*   ��������ȷ��Ҫ���ٵ��鼮��ISBN����   *\n";
		cout<<"******************************************\n";
		cin>>sar;
		int r=bisearch(sar,0,MAX_BOOK_AMOUNT-1);
		if(r==-1)
		goto f;
		cout<<"******************************************\n";
		cout<<"*           ����Ҫ���ٵ�����             *\n";
		cout<<"******************************************\n";
		int numb;
		cin>>numb;
		if(info[r].amount>numb){ 
		    info[r].amount-=numb;
            info[r].lamount-=numb;//����鼮�������٣���ô�ɽ�����Ҳ��Ӧ���� 
		}
		else if(info[r].amount==numb){
		    for(int j=r;j<MAX_BOOK_AMOUNT-1;j++){
			    info[j]=info[j+1];//������ٵı���ֱ�ӵ��ڴ�����������ɾ���������¼ 
		    }
		} 
		ofstream outFile;  
        outFile.open("F:\\ͼ�����ϵͳ\\�鼮��Ϣ��.csv", ios::out); 
	    for(int i=0;i<MAX_BOOK_AMOUNT;i++){//�����ļ� 
		    outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
	    } 
		cout<<"\n************\n";
			cout<<"* ������� *\n";
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
}book(0); //����������һ�����󣬳�ֵΪ0�������ļ��е���Ϣ�ȶ���������������Щ����֮����õ� 
class boro_lend{//������ǽ��黹���� ����Ҫ���û�����ͻ������ʹ�� 
	public: 
	        struct userbook{//����û�������Ϣ�Ľṹ�壬��������鼮������Ľṹ��������������Ϊ�û�����Ҫ��¼����鼮���� 
	            char name[40];
	            char arthor[40]; 
	            char sear[40];
	            char publish[40]; 
            }ldbk[MAX_LENDBOOK_AMOUNT];
            int lendbooknum=0;//һ���Ľ�����������ֵ��Ϊ0 
		    boro_lend(char *username){//������캯���Ĳ���Ϊ�û�����ȷ�����黹��Ķ��� 
		    	cout<<"************************\n"; 
		        cout<<"*       �ҽ����       *\n";
		        cout<<"************************\n";
		    for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){
		    	ldbk[i].arthor[0]='\0';
		    	ldbk[i].sear[0]='\0';
		    	ldbk[i].name[0]='\0';
		    	ldbk[i].publish[0]='\0';//�ṹ���ʼ�� 
			}
			char filename[50];//·��+�ļ�����֮��� 
	        strcpy(filename,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
	        strcat(filename,username);
	        strcat(filename,".csv");      
	        FILE *f;
	        if ((f = fopen(filename, "r")) == NULL) {
	        	cout<<"************************\n";
			    cout<<"*   �����ڻ�û�н���   *\n"; 
			    cout<<"************************\n";
		        goto down;
	        }
	        int k,k1,k2,k3;
	        for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){//���ļ��ж�ȡ�û����ڵĽ�����Ϣ 
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
		        cout<<i+1<<"������:"<<ldbk[i].name<<" ISBN����:"<<ldbk[i].sear<<" ����:"<<ldbk[i].arthor<<" ������:"<<ldbk[i].publish;
		        lendbooknum=i+1;//����������� 
		    } 
			} 
            down:
			    cout<<"*************************************************************\n";	
			    cout<<"*  ����1����ISBN������ҽ���  *  ����2����ISBN������һ���  *\n"; 
			    cout<<"*************************************************************\n";
        	int n;
			mpm:    cout<<"********************\n";
			        cout<<"*  ������һ������  *\n"; 
			        cout<<"********************\n";
			cin>>n;
			if(n==1) {//������� 
				    cout<<"********************\n";
				    cout<<"*  ������ISBN����  *\n";
				    cout<<"********************\n";
				char bkser[40];
				cin>>bkser;
				int nur=book.bisearch(bkser,0,MAX_BOOK_AMOUNT-1);
				if(nur==-1) {
					cout<<"********************\n";
					cout<<"* �����û���Ȿ�� *\n";
					cout<<"********************\n";
					return;
				}
				if(info[nur].lamount==0){
					cout<<"********************\n";
					cout<<"*  ������ȫ�����  *\n";
					cout<<"********************\n";
					return;
				}
				if(lendbooknum==MAX_LENDBOOK_AMOUNT){
					cout<<"********************\n";
					cout<<"* �������Ѵ����� *\n";
					cout<<"********************\n";
					return; 
				} //����������е������������㣬�ſ����������� 
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
                    outFile.open("F:\\ͼ�����ϵͳ\\�鼮��Ϣ��.csv", ios::out); 
	                for(int i=0;i<MAX_BOOK_AMOUNT;i++){
	                	if(strcmp(info[i].name,"\0")==0) break;
		                outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
	                }
	                cout<<"********************\n";
				    cout<<"*     ����ɹ�     *\n"; 
				    cout<<"********************\n";
					}
        	    ofstream outFile;
			    outFile.open(filename, ios::out);
                for(int i=0;i<MAX_LENDBOOK_AMOUNT;i++){
                	if(strcmp(ldbk[i].name,"\0")!=0){ 
		            outFile << ldbk[i].name<< ',' << ldbk[i].sear << ',' << ldbk[i].arthor<<','<<ldbk[i].publish;} 
					else break; 
	            } 
		    }else if(n==2){//������� 
		    	cout<<"****************************\n";
		    	cout<<"* ������Ҫ�������ISBN���� *\n";
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
				    cout<<"*     �㲢û�н��Ȿ��     *\n";
				    cout<<"****************************\n";
				    return; 
				}    
				hhh:{
					int nur=book.bisearch(ser,0,MAX_BOOK_AMOUNT-1);//���Ҹ���������е�λ�� 
					info[nur].lamount++;//�ɽ�����++����������Ѿ�������� 
					ofstream outFile;  
                    outFile.open("F:\\ͼ�����ϵͳ\\�鼮��Ϣ��.csv", ios::out); 
	                for(int i=0;i<100;i++){//�����ļ� 
		                outFile << info[i].name<<','<<info[i].amount <<','<<info[i].lamount <<',' << info[i].sear << ',' << info[i].arthor<<','<<info[i].publish; 
	                }
	                cout<<"****************************\n";
				    cout<<"*         �黹�ɹ�         *\n";
				    cout<<"****************************\n";
					}
			} else goto mpm; 
	    }
	    ~boro_lend(){//�����������ڽ軹�鼮��Ϊ����֮�ʴ��һ�仰���û� 
	    	if(if_continue_use==2)
	    	cout<<"*******************\n";
	    	cout<<"*  ��ӭ�´ν���   *\n";
	    	cout<<"*******************\n";
		}
};  
class readonl_download{//�����Ķ������� 
	public: readonl_download(int k){//k�����û��������Ķ����������鼮 
		    FILE*fp;
		    if((fp=fopen("F:\\ͼ�����ϵͳ\\��������Ϣ��\\������Ŀ�б�.csv","r"))==NULL){
		    	cout<<"**************************\n";
				cout<<"*   ������������޿��   *\n";
				cout<<"**************************\n"; 
			}else {
				while(!feof(fp)){//չʾ���е�����Ŀ¼ 
					char m;
					m=fgetc(fp);
					cout<<m;
				}
			}
			if(k==1)
			readon();//�����Ķ����� 
			if(k==2)
			download(); //�����ļ����� 
	        }
	        readonl_download(){//���صĹ��캯�������ù���Ա¼�������ĺ��� 
	        	FILE*fp;
		        if((fp=fopen("F:\\ͼ�����ϵͳ\\��������Ϣ��\\������Ŀ�б�.csv","r"))==NULL){
		    	    cout<<"**************************\n";
				    cout<<"*   ������������޿��   *\n";
				    cout<<"**************************\n";  
			    }else {
			    	cout<<"******************\n";
			    	cout<<"*  �����鵥����  *\n";
			    	cout<<"******************\n";
				    while(!feof(fp)){//չʾ���е�����Ŀ¼ �������û�ѡ���Ķ������غ͹���Ա¼�� 
					    char m;
					    m=fgetc(fp);
					    cout<<m;
				    }
			    }
	        	managerinput();//����Ա¼�������ĺ���
			}
    private:void readon(){//�����Ķ����� 
            char bookname[40];
            cout<<"**********************\n";
            cout<<"*  ������Ҫ���ҵ���  *\n";
            cout<<"**********************\n";
            cin>>bookname;//�û�ͨ���������������ҵ��鼮�ĵ����ļ����Ӷ����Ķ� 
	        strcpy(filename,"F:\\ͼ�����ϵͳ\\��������Ϣ��\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt");      
			FILE *fl;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"**********************\n";
				cout<<"* ���ҵĵ����鲻���� *\n";
				cout<<"**********************\n";
				return ;
			}else { 
			cout<<"**********************\n";
			cout<<"*    ͼ��ȫ������    *\n";
			cout<<"**********************\n";
			while (!feof(fl)) {//һ��һ���ַ������Ӱ��鼮����Ļ�������Ķ� 
                char c;
                c=fgetc(fl);
                cout<<c; 
		    }} 
		    fclose(fl);
	    }
	    void download(){//���غ������û����Խ��鼮�ĵ��Ӱ��ļ��Ӻ�̨���ص��Լ��ĵ����У��ڱ������м����ص��������ڵ��ļ����� 
	    	char bookname[40];
	    	cout<<"*********************************\n";
            cout<<"*  ������Ҫ���صĵ����������   *\n";
            cout<<"*********************************\n";
            cin>>bookname;
	        strcpy(filename,"F:\\ͼ�����ϵͳ\\��������Ϣ��\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt"); 
			strcat(bookname,".txt");     
			FILE *fl;
			FILE *out;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"*********************************\n";
				cout<<"*       ���ҵĵ����鲻����      *\n";
				cout<<"*********************************\n";
				return ;
			}
			out=fopen(bookname,"w");
			while (!feof(fl)) {//��һ���ļ�������д����һ���ļ���ʵ���ļ��ĸ��ƺ����� 
                char c;
                c=fgetc(fl);
                fputc(c,out); 
		    }
		    cout<<"*********************************\n";
			cout<<"*           �������            *\n";
			cout<<"*********************************\n"; 
		    fclose(fl);
	    	fclose(out);
		} 
	    void managerinput(){//����Ա����¼�������ĺ��� 
	    	FILE*rite;
	    	cout<<"******************************\n";
	    	cout<<"*     ������Ҫ¼�������     *\n";
	    	cout<<"******************************\n";
	    	char booknam[40];
			cin>>booknam;
			cout<<"*      ���������������      *\n"; 
			cout<<"******************************\n";
			char arthorname[40];
			cin>>arthorname;
			cout<<"*        �����������        *\n";
			cout<<"******************************\n";
			char pubclub[40];
			cin>>pubclub;
			strcpy(filename,"F:\\ͼ�����ϵͳ\\��������Ϣ��\\");
	        strcat(filename,booknam);
	        strcat(filename,".txt"); //·��+���������Խ�������Ϊ���ֵ��ı��ļ����浽ָ����·���� 
			if((rite=fopen(filename,"w"))==NULL){
				cout<<"******************************\n";
				cout<<"*     �޷�����¼�������     *\n";
				cout<<"******************************\n";
	            return ;
			}
			getchar();
			char m;
			cout<<"**************************************************\n";
			cout<<"*  ��¼���鼮����(������һ����#����ʾ¼�����) *\n";
			cout<<"**************************************************\n";
	    	while((m=getchar())!='#'){
	    		fputc(m,rite);//¼���鼮ȫ�ĵĹ��̣��Ҳ���һ��һ���ַ�д���ļ��еķ��� 
			}
			fclose(rite);
			cout<<"*************************\n";
			cout<<"*      ȫ��¼��ɹ�     *\n";
			cout<<"*************************\n";
			FILE*c;
			c=fopen("F:\\ͼ�����ϵͳ\\��������Ϣ��\\������Ŀ�б�.csv","a");//����������һ���������Ŀ¼�������û����ҵ����� 
			fputs("����:",c);
			fputs(booknam,c);
			fputc(',',c);
			fputs("����:",c);
			fputs(arthorname,c);
			fputc(',',c);
			fputs("������:",c);
			fputs(pubclub,c);
			fputc(',',c);
			fputs("�洢·��:",c);
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
	    	cout<<"*   ��ӭ�´�ʹ�ô˵�����ϵͳ   *\n";
	    	cout<<"********************************\n"; 
		}
}; 
class electric_article{//����ǹ�����Ķ��������ĵ��࣬����ԭ��͵���ͼ������ͬ�������ĺ��鼮��Ҫ�ز�ͬ�����Ե������� 
	public: electric_article(int k){//�û��ӿ� 
		    FILE*fp;
		    if((fp=fopen("F:\\ͼ�����ϵͳ\\����������Ϣ��\\���������б�.csv","r"))==NULL){
		    	cout<<"********************************\n"; 
				cout<<"*     �������Ŀ������޿��     *\n";
				cout<<"********************************\n";  
			}else {
				while(!feof(fp)){
					char m;
					m=fgetc(fp);
					cout<<m;
				}
			}
			if(k==1)
			readonarticle();//�����Ķ����� 
			if(k==2)
			downloadarticle();//�������� 
	        }
	        electric_article(){//����Ա�ӿ� 
	        	FILE*fp;
		        if((fp=fopen("F:\\ͼ�����ϵͳ\\����������Ϣ��\\���������б�.csv","r"))==NULL){
		    	    cout<<"********************************\n"; 
				    cout<<"*     �������Ŀ������޿��     *\n";
				    cout<<"********************************\n";
			    }else {
			    	cout<<"********************************\n";
			    	cout<<"*       ����������¼����       *\n";
			    	cout<<"********************************\n";
				    while(!feof(fp)){
					    char m;
					    m=fgetc(fp);
					    cout<<m;
				    }
			    }
	        	managerinputarticle();//���ù���Ա����������ĵĺ��� 
			}
	private:char filename[100];
	    void readonarticle(){
            char bookname[40];
            cout<<"********************************\n";
            cout<<"*     ������Ҫ���ҵ����ı���   *\n";
            cout<<"********************************\n";
            cin>>bookname;
	        strcpy(filename,"F:\\ͼ�����ϵͳ\\����������Ϣ��\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt");      
			FILE *fl;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"********************************\n";
				cout<<"*      ���ҵ����Ĳ�����        *\n";
				cout<<"********************************\n";
				return ;
			}else { 
			cout<<"********************************\n";
			cout<<"*         ����ȫ������         *\n";
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
            cout<<"*    ������Ҫ���ص����ı���    *\n";
            cout<<"********************************\n";
            cin>>bookname;
	        strcpy(filename,"F:\\ͼ�����ϵͳ\\����������Ϣ��\\");
	        strcat(filename,bookname);
	        strcat(filename,".txt"); 
			strcat(bookname,".txt");     
			FILE *fl;
			FILE *out;
			if((fl=fopen(filename,"r"))==NULL){
				cout<<"********************************\n";
				cout<<"*       ���ҵ����Ĳ�����       *\n";
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
			cout<<"*    �������      *\n";
			cout<<"********************\n"; 
		    fclose(fl);
	    	fclose(out);
		} 
		void managerinputarticle(){
	    	FILE*rite;
	    	cout<<"**********************************************\n";
	    	cout<<"*          ������Ҫ¼������ı���            *\n";
	    	cout<<"**********************************************\n";
	    	char booknam[40];
			cin>>booknam;
			getchar();
			cout<<"**********************************************\n";
			cout<<"*  ���������ĵ�������(������#�Դ����������) *\n"; 
			cout<<"**********************************************\n";
			char arthorname[100];
			cin.getline(arthorname,100,'#');
			cout<<"**********************************************\n";
			cout<<"*                 �����뿯��                 *\n";
			cout<<"**********************************************\n";
			char pubclub[40];
			cin>>pubclub;
			cout<<"**********************************************\n";
			cout<<"*              ���������ı��                *\n";
			cout<<"**********************************************\n";
			char anumber[40];
			cin>>anumber; 
			char time[40];
			cout<<"**********************************************\n";
			cout<<"*              �����뷢��ʱ��                *\n";
			cout<<"**********************************************\n";
			cin>>time; 
			strcpy(filename,"F:\\ͼ�����ϵͳ\\����������Ϣ��\\");
	        strcat(filename,booknam);
	        strcat(filename,".txt"); 
			if((rite=fopen(filename,"w"))==NULL){
				cout<<"**********************************************\n";
				cout<<"*          �޷�����¼���������              *\n";
				cout<<"**********************************************\n";
	            return ;
			}
			getchar();
			char m;
			cout<<"**********************************************\n";
			cout<<"*��¼������ȫ��(����һ����#����ʾ¼�����) *\n";
			cout<<"**********************************************\n";
	    	while((m=getchar())!='#'){
	    		fputc(m,rite);
			}
			fclose(rite);
			cout<<"**********************************************\n";
			cout<<"*               ȫ��¼��ɹ�                 *\n";
			cout<<"**********************************************\n"; 
			FILE*c;
			c=fopen("F:\\ͼ�����ϵͳ\\����������Ϣ��\\���������б�.csv","a");
			fputs("����:",c);
			fputs(booknam,c);
			fputc(',',c);
			fputs("����:",c);
			fputs(arthorname,c);
			fputc(',',c);
			fputs("����:",c);
			fputs(pubclub,c);
			fputc(',',c);
			fputs("���:",c);
			fputs(anumber,c);
			fputc(',',c);
			fputs("ʱ��",c);
			fputs(time,c);
			fputc(',',c); 
			fputs("�洢·��:",c); 
			fputs(filename,c);
			fputc(',',c);
			fputc('\n',c); 
			fclose(c);
		}
		public:~electric_article(){
			if(if_continue_use==2)
			cout<<"**********************************************\n";
			cout<<"*     ��ӭ�´μ���ʹ�ô˵������Ĳ���ϵͳ     *\n";
			cout<<"**********************************************\n";
		}
}; 
class usermanage{//����Ҫ��һ���࣬�û������࣬�ƹ����û�ע�ᡢ�û���¼��ע���˺š��޸���������û���ص����й��ܣ� 
	public:      //���һ����û���¼��ʹ������ʵ�ֵ����й��� 
		usermanage(int Num){//һ�����еĹ��캯���������һ�������������������������� 
			No=Num;
			all_fouctions();
	    }
	private:void modify_num(int num){//�û���ָ�����޸Ĳ������������������� 
	    	No=num;
		}
		void all_fouctions(){//�������Ҫ���ܺ��� 
			if(No==0) screen();//�������������Ļ��ָ���û����������Ҳ����������������ʱ����Ĭ�����ȵ��õĹ��ܺ��� 
			else if(No==1) user_register();//�û�ע�ắ�����ֹ���Աע�����ͨ�û�ע�ᣬ��Ҫ������˲��ܳɹ� 
	        else if(No==2) log_on();//��¼�����������������ĸ��� 
	        else if(No==3) user_delect();//�û�ע�� 
	        else if(No==4) modify_password();//�޸����� 
		}
		void screen(){
			cout<<"**********************************\n";
			cout<<"*********��ѡ����Ĳ���***********\n";
			cout<<"**********************************\n";
			cout<<"*  1���û�ע��  *  2���û���¼   *\n";
			cout<<"**********************************\n";
			cout<<"*  3���û�ע��  *  4���޸�����   *\n";
			cout<<"**********************************\n";
			int n;
			cin>>n;
			modify_num(n);
			all_fouctions();
	    }
	    void user_register();
	    void manage_register();//����Ա����ֱ������û� 
	    void log_on();
	    void user_delect();
	    void manage_delect();//����Ա����ֱ��ע���������û����˺� 
	    void modify_password();
	    void authorize();//����Աר����˺��� 
        char username[40];
	    char password[40];
	    int sf; //��ʾ�û�����ǹ���Ա������ͨ�û� 
		int scces_log=0;//�ɹ���¼�ı�־���ڵ�¼������ʹ�ã�ֻ�����ֵ�����ı�������¼�ɹ��������������ܵĲ��� 
		int No;//�����м��õ�һ��ֵ 
		int if_re_sus=1;//��ʾע��ɹ� 
		struct authorize_users{//����Ա����û�ʱ��Ҫ�õ��û�����ע�������Ϣ 
			char username[40];
			char identity[10];
		}wait[WAIT_NUMBER];
		void fwrit(){//ע��ʱ���� 
			ofstream outFile;
	        char filename[50],anotherflnm[50];
	        strcpy(filename,"F:\\ͼ�����ϵͳ\\�û��������Ϣ��\\");//�û�����ע����Ƚ���������Ϣ���� 
	        strcat(filename,username);
	        strcat(filename,".txt");
	        strcpy(anotherflnm,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
	        strcat(anotherflnm,username);
	        strcat(anotherflnm,".txt");
	        FILE *fp;
	        FILE *fl;
	        int p1=0,p2=0;
	        if((fp = fopen(filename, "r"))==NULL)
	            p1=1;
			if((fl=fopen(anotherflnm,"r"))==NULL)
			    p2=1;
			if (p1==1&&p2==1) {//�ж��û��������ظ� ��������ظ����������趨���룬����ע��ʧ�� 
				ofstream outFile;
				outFile.open(filename, ios::out);
	            outFile<<password<<sf<<endl;//������������Ϣ�����ļ��б��� 
	            outFile.close();
				FILE*csv;
				csv=fopen("F:\\ͼ�����ϵͳ\\�û��������Ϣ��\\�û��������Ϣ��.csv","a");//����������û����������ڹ���Ա��� 
				fputs(username,csv);
				fputc(',',csv);
				if(sf==1)
				fputs("��ͨ�û�\n",csv);
				else if(sf==2)
				fputs("����Ա\n",csv);
				fclose(csv);
	        }else {
	        	cout<<"********************\n";
	        	cout<<"* ���û����ѱ�ע�� *\n";
	        	cout<<"********************\n"; 
				fclose(fp);
				fclose(fl);
				if_re_sus=0; //��־ 
			} 
		}
		void derect_fwrit(){//����Ա��ӵ��û�ֱ��ͨ����˽����û���Ϣ�� 
			ofstream outFile;
	        char filename[50],anotherflnm[50];
	        strcpy(filename,"F:\\ͼ�����ϵͳ\\�û��������Ϣ��\\");
	        strcat(filename,username);
	        strcat(filename,".txt");
	        strcpy(anotherflnm,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
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
			if(if_multiple1==1&&if_multiple2==1){//�ж��û����Ƿ��Ѿ���ע�� 
				outFile.open(anotherflnm, ios::out);
	            outFile<<password<<sf<<endl; 
	        }else {
	        	cout<<"********************\n";
	        	cout<<"* ���û����ѱ�ע�� *\n";
	        	cout<<"********************\n"; 
				if_re_sus=0; 
			} 
		}
		int if_name_exist=1;  //�û����Ƿ���ڵı�־����¼ʱ�õ� 
		void match(){
			FILE *fp;
			char filename[50];
			strcpy(filename,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
	        strcat(filename,username);
	        strcat(filename,".txt");  
	        if ((fp = fopen(filename, "r")) == NULL) {
	        	cout<<"********************\n";
	        	cout<<"*    �û�������    *\n";
	        	cout<<"********************\n"; 
	        	if_name_exist=0;
				return; 
	        }
            char pswrd[40];
            fgets(pswrd,40,fp);
            int pswrd_len=strlen(pswrd);
			sf=pswrd[pswrd_len-2]-'0';
            pswrd[pswrd_len-2]='\0';  //���ļ��н���������������Ϣ 
            if(strcmp(pswrd,password)==0){
            	scces_log=1;//�ɹ���¼�ı�־ 
			}
			fclose(fp); 
		};
		public:~usermanage(){
			if(if_continue_use==2){ 
			cout<<"************************************\n";
			cout<<"*��ӭ�´�ʹ�ô��ۺϹ���ϵͳo(^��^)o*\n";} 
		}
};
void usermanage::user_register(){
	cout<<"********************\n"; 
	cout<<"*   ���趨�û���   *\n";
	cout<<"********************\n"; 
	cin>>username;
	cout<<"********************\n"; 
	cout<<"*    ���趨����    *\n";
	cout<<"********************\n"; 
	cin>>password;
	up:
	cout<<"***************************************\n";
	cout<<"*  ��ѡ����ݣ�1����ͨ�û�,2������Ա  *\n";
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
	cout<<"*   ע��ɹ�����ȴ�����Ա���ͨ��   *\n";
	cout<<"**************************************\n";} 
	else {
	cout<<"***************\n";
	cout<<"*   ע��ʧ��  *\n";
	cout<<"***************\n";} 
}
void usermanage::manage_register(){
	cout<<"********************\n"; 
	cout<<"*���趨��ӵ��û���*\n";
	cout<<"********************\n"; 
	cin>>username;
	cout<<"********************\n"; 
	cout<<"*    ���趨����    *\n";
	cout<<"********************\n"; 
	cin>>password;
	up:
	cout<<"***************************************\n";
	cout<<"*  ��ѡ����ݣ�1����ͨ�û�,2������Ա  *\n";
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
	cout<<"*   ע��ɹ�����ȴ�����Ա���ͨ��   *\n";
	cout<<"**************************************\n";}
	else {
	cout<<"***************\n";
	cout<<"*   ע��ʧ��  *\n";
	cout<<"***************\n";}
}

void usermanage::user_delect(){
	cout<<"************************\n"; 
	cout<<"*��������Ҫע�����û���*\n";
	cout<<"************************\n"; 
	cin>>username;
	cout<<"************************\n"; 
	cout<<"* ��������û��������� *\n";
	cout<<"************************\n"; 
	cin>>password;//�û�ע��ǰ��������֤���� 
	match();
	if(scces_log==1){
		char txtfilename[50],csvfilename[50];
	strcpy(txtfilename,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
    strcat(txtfilename,username);
    strcat(txtfilename,".txt");  
    strcpy(csvfilename,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
    strcat(csvfilename,username);
    strcat(csvfilename,".csv");  
    if(remove(txtfilename)==0){
    	if(remove(csvfilename)==0)
    	    cout<<"************\n"; 
	    	cout<<"* ע���ɹ� *\n";
	    	cout<<"************\n";
		}else {
		cout<<"************\n";
		cout<<"* ע��ʧ�� *\n";
		cout<<"************\n";}
	}else {
	cout<<"************\n";
	cout<<"* ������� *\n";
	cout<<"************\n";} 
	scces_log==0;
} 
void usermanage::manage_delect(){
	cout<<"****************************\n";
	cout<<"*  ��������Ҫɾ�����û���  *\n";
	cout<<"****************************\n";
	cin>>username;
	char txtfilename[50],csvfilename[50];
	strcpy(txtfilename,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
    strcat(txtfilename,username);
    strcat(txtfilename,".txt");  
    strcpy(csvfilename,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
    strcat(csvfilename,username);
    strcat(csvfilename,".csv");  
    if(remove(txtfilename)==0){
        remove(csvfilename);//����Աֱ��ɾ�����û��������Ϣ�ͽ�����Ϣ 
        cout<<"************\n";
	    cout<<"* ɾ���ɹ� *\n";
	    cout<<"************\n";
	}else {
	    cout<<"****************************\n"; 
	    cout<<"* ɾ��ʧ�ܣ����û��������� *\n";
	    cout<<"****************************\n";
    }
} 
void usermanage::modify_password(){
	cout<<"****************\n";
	cout<<"* �������û��� *\n";
	cout<<"****************\n";
	cin>>username;
	cout<<"****************\n";
	cout<<"* ������ԭ���� *\n";
	cout<<"****************\n";
	cin>>password;
	match();//�޸�����ǰҲҪ����֤�Ƿ���ȷ��ȷ�����˲��� 
	if(scces_log==1){
		cout<<"****************\n";
		cout<<"* ������������ *\n";
		cout<<"****************\n";
		char new_password[40]; 
		cin>>new_password;
		ofstream outFile;
		char filename[50];
	    strcpy(filename,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
	    strcat(filename,username);
	    strcat(filename,".txt");  
		FILE*fp;  
		if ((fp = fopen(filename, "r")) != NULL) {
				outFile.open(filename, ios::out);
	            outFile<<new_password<<sf<<endl; //�������� 
	        }else {
			cout<<"************\n"; 
			cout<<"* �޸�ʧ�� *\n"; 
			cout<<"************\n";} 
	} else {
	cout<<"************\n";
	cout<<"* ������� *\n"; 
	cout<<"************\n";}
}
void usermanage::authorize(){//��˺��� 
	for(int i=0;i<WAIT_NUMBER;i++){
		wait[i].username[0]=wait[i].identity[0]='\0';
	}
	FILE*csv;
	if((csv=fopen("F:\\ͼ�����ϵͳ\\�û��������Ϣ��\\�û��������Ϣ��.csv","r"))==NULL){
		cout<<"******************\n";
		cout<<"*  ���ϵͳ�쳣  *\n";
		cout<<"******************\n";
		return;
	}else{
		int number=0;
		while(!feof(csv)){
			char info[50];
			fgets(info,50,csv);
			for(int i=0;i<WAIT_NUMBER;i++){//�Ѵ�����û�����������������ڲ��� 
				if(info[i]==','){
					strncpy(wait[number].username,info,i);
					strcpy(wait[number].identity,info+i+1);
					break;
				}
			}
			number++; //�ڼ�¼�û����� 
		} 
		wait[number-1].username[0]=wait[number-1].identity[0]='\0';
		for(int i=0;i<number-1;i++){
			cout<<i+1<<"���û�����"<<wait[i].username<<" ע����ݣ�"<<wait[i].identity; 
		}
		if(number<=1){ 
		    cout<<"**********************\n";
		    cout<<"*  û�д���˵��û�  *\n";
		    cout<<"**********************\n";
		    return;
		}
		cout<<"**************************************\n";
		cout<<"*   ��ѡ�����������ͨ�����û����   *\n";
		cout<<"**************************************\n"; 
		int permit_number;
		cin>>permit_number;//ͨ��ѡ������ѡ��ͨ����˵��û���Ȼ������Ϣ�Ƶ��û���Ϣ���У�ɾ�����ڴ������Ϣ���е���Ϣ 
		char sOriPathName[50];
		char sNewPathName[50];
		strcpy(sOriPathName,"F:\\ͼ�����ϵͳ\\�û��������Ϣ��\\");
	    strcat(sOriPathName,wait[permit_number-1].username);
	    strcat(sOriPathName,".txt");  
	    strcpy(sNewPathName,"F:\\ͼ�����ϵͳ\\�û���Ϣ��\\");
	    strcat(sNewPathName,wait[permit_number-1].username);
	    strcat(sNewPathName,".txt");
		FILE*Ori;
		if((Ori=fopen(sOriPathName,"r"))==NULL){
			cout<<"**************************************\n";
			cout<<"*        �˴�����û�������          *\n";
			cout<<"**************************************\n";
			return;
		}
		char pswd_sf[20];
		fgets(pswd_sf,20,Ori);
		fclose(Ori);
		
		FILE*Try;
		if((Try=fopen(sNewPathName,"r"))!=NULL){
			cout<<"**************************************\n";
			cout<<"*          ���û����ѱ�ע��          *\n";
			cout<<"**************************************\n";
			return;
		}
		fclose(Try);
		FILE*New;
		New=fopen(sNewPathName,"w");
		fputs(pswd_sf,New);
		fclose(New);
		cout<<"**************************************\n";
		cout<<"*              ������              *\n";
		cout<<"**************************************\n";
		remove(sOriPathName);
		for(int n=permit_number;n<=number;n++){
			wait[n-1]=wait[n];
		}
		wait[number-1].username[0]=wait[number-1].identity[0]='\0';
		ofstream outFile;
		outFile.open("F:\\ͼ�����ϵͳ\\�û��������Ϣ��\\�û��������Ϣ��.csv", ios::out);
		for(int n=0;n<number-1;n++){//���´�����б� 
			outFile<<wait[n].username<<','<<wait[n].identity; 
		}
	}	
}
void usermanage::log_on(){//��½��������ͨ�û��͹���Ա��ͨ������������� 
	cout<<"******************\n";
	cout<<"*  �������û���  *\n";
	cout<<"******************\n";
	cin>>username;
	cout<<"******************\n";
	re:
	cout<<"*   ����������   *\n";
	cout<<"******************\n";
	cin>>password;
	match(); //�����֤ 
	if(if_name_exist==0){
		return;
	}
	if(scces_log==1){
		cout<<"**************\n";
		cout<<"*  ��¼�ɹ�  *\n";
		cout<<"**************\n";
		cout<<"************************************************************\n";
		cout<<"�װ���"<<username<<",��ãܣ��ޣ�ޣ�����\n";
		cout<<"************************************************************\n";
		cout<<"*********************\n";
		cout<<"*   ��ӭʹ�ñ�ϵͳ  *\n";
		cout<<"*********************\n"; 
	}else {
		cout<<"***************\n";
	    cout<<"*   �������  *\n";
	    cout<<"***************\n";
	    goto re;
		}
	if(sf==2){ //����Ա����ѡ���Լ�ʹ����ͨ�û�ģʽ���ǹ���Աģʽ 
	cout<<"*******************************************\n";
	cout<<"*     ��ѡ������û�ģʽ���߹���Աģʽ    *\n";
	cout<<"*******************************************\n"; 
	cout<<"*     �û�ģʽ����1  *  ����Աģʽ����2   *\n";
	cout<<"*******************************************\n";
	cin>>sf; //ȷ��ģʽ 
	} 
	scces_log=0;
	if(sf==1){//��ͨ�û�Ȩ�� 
		int k;
		while(1){ 
		cout<<"\n";
		cout<<"**************************************************\n";
		cout<<"*   ����ʵ����,������1  *   ����������,������2   *\n";
		cout<<"**************************************************\n";
		cout<<"*  ������������,������3 *    �˳���¼,������0    *\n"; 
		cout<<"**************************************************\n";
		cin>>k;
		if(k==1){
		book_manage(0);//���鼮Ŀ¼����Ϣ���������� 
		book_manage(1);//չʾ�鼮Ŀ¼ 
		boro_lend brld(username);//���Խ���ͻ��� 
		}
		else if(k==2){
			cout<<"*********************************************\n";
			cout<<"*  �����Ķ�������1  *  ���ص����ĵ�������2  *\n";
			cout<<"*********************************************\n";
			cin>>k;
		    readonl_download read(k);//�����Ķ����������ĵ� 
		}
		else if(k==3){
			cout<<"*********************************************\n";
			cout<<"*  �����Ķ�������1  *  ���ص�������������2  *\n";
			cout<<"*********************************************\n";
			cin>>k;
		    electric_article elc(k);
		} 
		else if(k==0)//�˳���¼ 
		break; 
		} 
	}else if(sf==2){//����ԱȨ�� 
		int k;
		while(1){ 
		cout<<"\n";
		cout<<"**************************************************\n";
		cout<<"*   ����ʵ����,������1  *   ����������,������2   *\n";
		cout<<"**************************************************\n";
		cout<<"*  ������������,������3 *    �û�����������4   *\n"; 
		cout<<"**************************************************\n"; 
		cout<<"*              �˳���¼��������0                 *\n";
		cout<<"**************************************************\n"; 
		cin>>k;
		if(k==1){
		book_manage(0);//���鼮Ŀ¼����Ϣ����������  
		book_manage(1);//չʾ�鼮Ŀ¼ 
		book_manage(2);//��ӻ��߼��ٴ��� 
		} 
		else if(k==2)
		readonl_download read;//����Ա¼������� 
		else if(k==3)
		electric_article elc;//����Ա¼��������� 
		else if(k==4){//�û������ܣ�����Ա���Թ����û� 
			int choice;
			cout<<"*****************************************************************\n";
			cout<<"*   ����û�����1   *   ɾ���û�����2   *   ����û�ע������3   *\n";
			cout<<"*****************************************************************\n"; 
			cin>>choice;
			if(choice==1){
				manage_register();//����û� 
			} 
			if(choice==2){
				manage_delect();//ɾ���û� 
			} 
			if(choice==3){
				authorize();//����û� 
			} 
		} 
		else if(k==0)//�˳���¼ 
		break;} 
	}
}   
