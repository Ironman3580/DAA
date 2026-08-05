//binary search
#include <iostream>
using namespace std;
int binarySearch(int arr[], int left, int right, int key)
{
    if (right >= left)
    {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] > key)
            return binarySearch(arr, left, mid - 1, key);
        return binarySearch(arr, mid + 1, right, key);
    }
    return -1;
}   


int main()
{
    int n, key;
    cin >> n;
    int arr[n];
    cin >> key;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int result = binarySearch(arr, 0, n - 1, key);
    if (result != -1)
        cout << "Element found at index: " << result << endl;
    else
        cout << "Element not found in the array." << endl;

    return 0;
}