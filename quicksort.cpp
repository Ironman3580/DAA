#include<iostream>
using namespace std;

int swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}

int part(int* arr, int low , int  high){
	int pivot= arr[low];
	int i=low ,j=high;
	while (i<j){
		while(arr[i] <= pivot && i <= high-1){
			i++;
		}
		while(arr[j]>pivot && j>=low+1){
			j--;
		}
		if(i<j){
			swap(arr[i],arr[j]);
		}
		swap(arr[low],arr[j]);
	}
		return j; 
	
}

int qs(int* arr,int low ,int  high){
	
	if(low<high){
		int p = part(arr,low,high);
		qs(arr,low,p-1);
		qs(arr,p+1,high);
	}
}

int main(){
	int n,l,h ,pt;
	cout<<"enter no elements of array "<<endl;
	cin>>n;
	int arr[n];
	cout<<"now enter elements"<<endl;
	for(int i =0;i<n;i++){
		cin>>arr[i];
	}
	l=0;
	h=n-1;
	qs(arr,l,h); 
	cout<<"sorted array elements are "<<endl;
	cout<<"[";for(int i =0;i<n;i++){cout<<arr[i]<<" ";}cout<<"]";
	return 0;
}
