// linear search
#include <iostream>
using namespace std;
 
void linearSearch(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            cout << "Element found at index: " << i << endl;
            return;
        }
    }
    cout << "Element not found in the array." << endl;
}


int main()
{

    int n , key;
    cin >> n;
    int arr[n];
    cin >> key;
    
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    linearSearch(arr, n, key);

    return 0;
}