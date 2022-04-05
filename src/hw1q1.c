#include <stdio.h>

int main() {
  double weight = 0, ingredient_sum = 0;
  int ingredient_amount = 0;
  printf("Welcome, please enter the weights of each ingredient:\n");

  while (scanf("%lf", &weight) == 1) {
    if (weight < 0) {
      // reached end of input, time to conditionally print outputs
      if (ingredient_amount < 3) {
        printf("Not enough ingredients.");
      } else if (ingredient_amount > 10) {
        printf("Too many ingredients.");
      } else {
        printf("The final product weighs %.3f pounds and is %d percent pure.\n",
        ingredient_sum / ingredient_amount,
        ingredient_amount * 10);
      }
      return 0;
    }

    ingredient_sum += weight;
    ingredient_amount++;
  }
  // illegal input was entered, exit gracefully (assumingly).
  return 0;
}
