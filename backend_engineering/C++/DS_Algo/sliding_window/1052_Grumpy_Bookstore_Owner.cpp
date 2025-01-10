#include <vector>

using namespace std;

int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
    // As per the question, our ultimate goal is to ensure the highest number of customers can be
    // satisfied after applying the secret technique, thereby enhancing their overall experience.
    // Now, to maximize the number of customers who can be satisfied using the secret technique, we
    // need to find a window of time that is maximum for the number of customers who can be
    // unsatisfied. To calculate this, we need to keep track of the number of customers who are
    // unsatisfied with each window and update the count while moving the window. After moving the
    // window, if the number of unsatisfied customers exceeds the last tracked maximum, we will
    // update the maximum number of unsatisfied customers.

    int current_customer_unsatisfied = 0;

    // Base case
    for(int i = 0; i < minutes; i++)
        if(grumpy[i] == 1) current_customer_unsatisfied += customers[i];

    int max_customer_unsatisfied = current_customer_unsatisfied;

    for(int i = minutes; i < size(customers); i++)
    {
        // Update the number of unsatisfied customers based on the customers going out of the window.
        if(grumpy[i - minutes] == 1) current_customer_unsatisfied -= customers[i - minutes];
        // Update the number of unsatisfied customers based on the customers entering this window.
        if(grumpy[i] == 1) current_customer_unsatisfied += customers[i];
        // Update the maximum number of unsatisfied customers.
        max_customer_unsatisfied = max(max_customer_unsatisfied, current_customer_unsatisfied);
    }

    // Find the total number of customers that can be satisfied without using the secret technique
    int total_customer_satisfied = 0;
    for(int i = 0; i < size(customers); i++)
        if(grumpy[i] == 0) total_customer_satisfied += customers[i];

    // Add the maximum number of unsatisfied customers, but they can be satisfied using the secret technique.
    total_customer_satisfied += max_customer_unsatisfied;

    return total_customer_satisfied;
}
