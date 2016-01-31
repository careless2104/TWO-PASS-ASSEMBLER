#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 25
int symbolmatch(char *s){
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
                    break;
            }
    }
        fclose(l);
       return kk;
}
int findopcode(char *s,int gf){
    char *p=(char *)malloc(sizeof(char)*max);
    int w=0,kk=0;
    FILE *q=fopen("opcode.txt","r");
    while(fgets(p,max,q)!=NULL){
            int j=0;
            w=0;
            int k;
            if(p[j]==s[0]&&gf==1)
                printf("%s \n",p);
            while(p[j]!=' '){
                if(s[j]!=p[j]){
                    w=1;
                    break;
                }
                j++;
            }
            if(w!=1 && j==strlen(s)){
                    kk=1;
                    break;
        }
    }
            fclose(q);
            return kk;
}
void main()
{
 	FILE *fr,*fw;
 	int cx,bx,lin=0;
	fr = fopen("isa.txt","r");
	fw = fopen ("symboltable.txt","w");
	char a[50];
	char ch;
	int line=1,i=0,ll=0;
	while(1){
        ch=fgetc(fr);
		if(ch==EOF){
                if(ll==0){
                    printf("Error!!! Empty File\n");
                }
			break;
		}
		else
		{   ll=1;
		    if(ch==10)
            {
                line++;
                i=0;
            }
            a[i]=ch;
            i++;
			if(ch==':')
			{
				a[i-1]='\0';
				i=0;
				fprintf(fw,"%s %d\n",a,2*(line-1));
			}
		}
	}
	fclose(fr);
	fclose(fw);
	fr = fopen("isa.txt","r");
	line=1;
	i=0;
	int zz=0,h=0;
	while(1)
	{
		ch=fgetc(fr);
		if(ch==EOF)
			break;
		else
		{
		    if(i==0 && ch>=48&&ch<=57){
                h=0;
                zz=1;
            }
			if(ch==':')
			{
			    h=0;
				a[i]='\0';
				i=0;
				cx=findopcode(a,0);
				if(cx==1){
                    printf("error %d opcode use as label!!\n",line);
                    char ee;
                printf("press H or h for help and N for not\n");
                scanf(" %c",&ee);
                if(ee=='H'||ee=='h'){
                    printf("Don't Use opcodes as Label\n");
                }
				}
			}
			else if(ch!=' '&&ch!='\n'&&ch!=','){
                    h=0;
                a[i]=ch;
                i++;
			}
			else if(ch==' ' || ch=='\n' || ch==','){
                    h++;
                a[i]='\0';
                cx=findopcode(a,0);
              bx=symbolmatch(a);
              if(h>1){
                    FILE *sx=fopen("binary.txt","w");
                    fclose(sx);
                printf("error!!! extra space in line %d\n",line);
              }
              if(cx!=1&&bx!=1&&zz==0){
                    FILE *sx;
                    sx=fopen("binary.txt","w");
                    fclose(sx);
                if(strlen(a)!=0&&a[i-1]!='h'){
                        if(a[0]!='R'){
                printf("error in %d line(%s is not valid opcode)\n",line,a);
                char ee;
                printf("press H or h for help and N for not\n");
                scanf(" %c",&ee);
                if(ee=='H'||ee=='h'){
                    printf("use following instruction\nuse opcodes \n");
                    char ff[2];
                    ff[0]=a[0];
                    ff[1]='\0';
                    int l=findopcode(ff,1);
                }
                        }
                else{
                        char ee;
                printf("error in %d line(%s is not valid register)\n",line,a);
                printf("press H or h for help and N for not\n");
                scanf(" %c",&ee);
                if(ee=='H'||ee=='h'){
                    printf("use following instruction\nuse registers b/w R0 to R15\n");
                }
                }
                }
              }
              if(ch=='\n')
                    line++;
            i=0;
            if(zz==1)
                zz=0;
			}
		}
	}
	fclose(fr);
	fclose(fw);
}
