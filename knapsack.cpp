#include <iostream>
using namespace std;

struct Item {
    int weight;
    int value;
};

void sortItems(Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            double r1 = (double)items[j].value / items[j].weight;
            double r2 = (double)items[j + 1].value / items[j + 1].weight;
            if (r1 < r2) {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}


double fractionalKnapsack(int capacity, Item items[], int n) {

    sortItems(items, n);

    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight){
                capacity -= items[i].weight;
                totalValue += items[i].value;
        } 
        else{
                totalValue += items[i].value * ((double)capacity / items[i].weight);
                break; 
        }
    }

    return totalValue;
}

int main() {
    int capacity = 50;
    int n = 3;
    Item items[3] = { {10, 60}, {20, 100}, {30, 120} };

    double maxVal = fractionalKnapsack(capacity, items, n);
    cout << "Maximum value in Fractional Knapsack: " << maxVal << "\n";

    return 0;
}