//factorial code

#include<stdio.h>

int facto(int n){
	if (n==0){
		return 1;
	}
	return n*facto(n-1);
}


int main (){
    int n,i,fact=1;
    printf("enter number...\n");
    scanf("%d",&n);

    for(i = n;i >= 1; i--)
    {
        fact = fact * i;
        
    }
    
	int ans= facto(n);
    printf("%d",ans);

    return 0; 

}


