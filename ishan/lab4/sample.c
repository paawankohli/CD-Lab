#include<stdio.h>
#include<stdlib.h>

 

/*This is a multiline
comment*/
//Sum function
int sum(int a,int b){
    int s=a+b;
    return s;

 

}

 


bool search(int arr[20],int key){
    int i;
    for(i=0;i<10;i++){
        if(arr[i]==key)
            return true;
        else
            return false;
    }
}

 

void main(){
    int a[20],i,res;
    bool status;
    printf("Enter array elements: ");
    for(i=0;i<10;++i){
        scanf("%d",&a[i]);
        res=sum(a[0],a[4]);
        status=search(a,res);
        printf("%d",status);
    }
}