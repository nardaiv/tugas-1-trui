#include <stdio.h>

#define ELSA_BASE_HP 200

struct elsa
{
    /* data */
};


void deathLoop(int *loop){
    float currentLearningPoints = 10;
    float hpMultiplier = 2.0f - (currentLearningPoints / 100.0f);
    float elsaHP = (int)(ELSA_BASE_HP * hpMultiplier);;
    float userHP = 100;

}

void analysis(){
    printf("=== Analisis Return by Death ===");
}

int main() {
  printf("=== Return by Death Battle Simulator ===\n\n");
  printf("Subaru vs Elsa Granhiert\n");


  int deathCount = 1;
  deathLoop(&deathCount);

  return 0;
}