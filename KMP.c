#include<stdio.h>
#include<string.h>

int vary(char targ[20],int n);
int* matchtable(char targ[20],int n);
void kmp(char sour[100],char targ[20],int n,int m);

int main(){
	char source[100];
	char target[20];
	int len,lens;
	puts("Enter source:");
	gets(source);
	puts("Enter target:");
	gets(target);
	len=strlen(target);
	lens=strlen(source);
	
	//TEST
	int *ptr;
	int i;
	ptr=matchtable(target,len);
	for(i=0;i<len;i++)
	printf("%d\t",*(ptr+i));
	
	//test kmp
	kmp(source,target,lens,len);
	
	return 0;
}

int vary(char targ[20],int n){
	int i,j,cnt=1,flag=0;
	for(i=1;i<n;i++){
		flag=0;
		for(j=0;j<i;j++){
			
			if(targ[i]==targ[j]){
				flag=1;
				break;
			}
			
		}
		if(flag==0)
			cnt++;
	}
	printf("Number is got\n");
	return cnt;
}

int* matchtable(char targ[],int n){
	static int table[20]={};
	int max=n-vary(targ,n);
	
	int i,j,k,flag;
	int cnt=0;
	table[0]=0;
	
	for(i=1;i<n;i++){
		if(i<max)
			j=i;
		else
			j=max;
		for(;j>=1;j--){
			flag=0;
			for(k=0;k<j;k++){
				if(targ[k]!=targ[i-j+1+k]){
					flag=1;
					break;
				}
			}
			if(flag==0){
				table[i]=j;
				break;
			}
		}
	}
	printf("Table is made\n");
	return table;
}

void kmp(char sour[100],char targ[20],int lens,int len){
	int i,j,k=0;
	int out[100]={};
	int flag=0,count=0;
	int *ptable=matchtable(targ,len);
	
		
	for(j=0;j<len;j++){
		
		while(k<lens&&targ[j]!=sour[k]){
			
			j=count-*(ptable+count);
			count=*(ptable+count);//
			k++;
			
		}
		if(k<lens&&targ[j]==sour[k]){
			
			count++;
			k++;
		}
		
		if(count==len){
			out[flag]=k;
			flag++;
			j=-1;
			//k--;//???
			count=0;
		}
		
		if(k>=lens)
			break;
		
	}
	for(i=0;i<lens;i++)
		if(out[i]==0){
			break;
		}else{
			printf("%d\t",out[i]-len+1);
		}
		printf("\nkmp over!\n");
}
