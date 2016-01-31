#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define max 25
int count=0;
int tempo=0;
void hexadecimal(FILE *r,char *s,int i){
    int j;
    for(j=i-2;j>=0;j--){
                        if(s[j]=='0'){
                            fputs("0000",r);
                    }
                        else if(s[j]=='1'){
                            fputs("0001",r);
                    }
                        else if(s[j]=='2'){
                            fputs("0010",r);
                    }
                        else if(s[j]=='3'){
                            fputs("0011",r);
                    }
                        else if(s[j]=='4'){
                            fputs("0100",r);
                    }
                        else if(s[j]=='5'){
                            fputs("0101",r);
                    }
                        else if(s[j]=='6'){
                            fputs("0110",r);
                    }
                        else if(s[j]=='7'){
                            fputs("0111",r);
                            }
                        else if(s[j]=='8'){
                            fputs("1000",r);
                    }
                        else if(s[j]=='9'){
                            fputs("1001",r);
                    }
                        else if(s[j]=='A'){
                            fputs("1010",r);
                    }
                        else if(s[j]=='B'){
                            fputs("1011",r);
                    }
                        else if(s[j]=='C'){
                           fputs("1100",r);
                    }
                        else if(s[j]=='D'){
                            fputs("1101",r);
                    }
                        else if(s[j]=='E'){
                            fputs("1110",r);
                    }
                        else if(s[j]=='F'){
                            fputs("1111",r);
                    }
                }
                fputc('\n',r);
                count=0;
}
void binary(FILE *r,char *s){
                int k=0,j;
                for(j=0;s[j]!='\0';j++)
                    if(s[j]>=48&&s[j]<=57)
                        k=k*10+(int)s[j]-48;
                int z=0;
                int *a=(int *)malloc(sizeof(int )*4);
                for(j=0;j<4;j++)
                    a[j]=0;
                while(k!=0){
                    a[z]=k%2;
                    k=k/2;
                    z++;
                }
                for(z=3;z>=0;z--){
                    if(a[z]==0)
                        fputc('0',r);
                    else
                        fputc('1',r);
                }
                count=0;
                fputc('\n',r);
}
int symbolmatch(FILE *r,char *s){
    char *a=(char *)malloc(sizeof(char)*max);
    int w=0,kk=0;
    FILE *l=fopen("symboltable.txt","r");
    while(fgets(a,max,l)!=NULL){
            int j=0;
            w=0;
            int k;
            while(a[j]!=' '){
                if(s[j]!=a[j]){
                    w=1;
                    break;
                }
                j++;
            }
            if(w!=1&&j==strlen(s)){
                    kk=1;
                binary(r,a);
                count=0;
                //kk=1;
                fclose(l);
                break;
            }
    }
        fclose(l);
       return kk;
}
int findopcode(FILE *r,char *s){
    char *a=(char *)malloc(sizeof(char)*max);
    int w=0,kk=0;
    FILE *q=fopen("opcode.txt","r");
    while(fgets(a,max,q)!=NULL){
            int j=0;
            w=0;
            int k;
            while(a[j]!=' '){
                if(s[j]!=a[j]){
                    w=1;
                    break;
                }
                j++;
            }
            if(w!=1 && j==strlen(s)){
                    kk=1;
                for(k=j+1;a[k]!='\0';k++){
                        if(a[k]=='1' || a[k]=='0')
                            count++;
                        if(a[k]!='\n')
                            fputc(a[k],r);
                        if(count==16){
                            fputc('\n',r);
                            count=0;
                        }
                       // kk=1;
                }
                fclose(q);
                break;
        }
    }
            fclose(q);
            return kk;
}
int main(){
    FILE *p,*r;
    p=fopen("isa.txt","r");
    r=fopen("binary.txt","w");
    char c;
    int i=0,zz=0,k,mm=0,cx,bx,cn=0;
    char *s=(char *)malloc(sizeof(char)*max);
    while((c=fgetc(p))!=EOF){
            if(i==0 && c>=48&&c<=57){
                s[i]=c;
                i++;
                zz=1;
            }
            else if(c==':'){
                i=0;
            }
            else if(c!=' ' && c!='\n' && c!=','){
                s[i]=c;
                i++;
            }
            else if((c==' ' || c=='\n' || c==',')&&i!=0&&cn==0){
                int j;

                s[i]='\0';
                if(s[i-1]=='h'){
                hexadecimal(r,s,i);
            }
            else if(zz==1){
                binary(r,s);
            }
            else{
            cx=findopcode(r,s);
              bx=symbolmatch(r,s);
            }
            i=0;
            zz=0;
            }
            if(c=='\n')
                cn=0;
    }
    fclose(p);
    fclose(r);
return 0;
}
