#include <stdio.h>
#include <stdbool.h>


#define ELSA_BASE_HP 200

struct loopReport
{
    int damageReceive;
    int damageDealt;
    int turnCount;
    char *deathCause;
    int learningPoints;
};


void battle(float *currentLearningPoints, int *userHP){
    int hpMultiplier = 2.0f - (*currentLearningPoints / 100.0f);
    int elsaHP = (int)(ELSA_BASE_HP * hpMultiplier);;
    
    char choice;

    printf("Subaru HP: %d | Elsa HP: %d", *userHP, elsaHP);
    printf("Pilih aksi:\nA: Serang\nD: Menghindar\nR: Kabur (Reset ke checkpoint)\n");
    printf("Pilihan: ");
    scanf("%c \n", &choice);

}


void deathLoop(int *deathCount, float *currentLearningPoints, bool *winningState){
    
    int userHP = 100;
    int turnCount = 0;
    bool reset = false;

    printf("[Death Loop #%d]", *deathCount);

    while(userHP > 0 || !winningState ){
        battle(currentLearningPoints, &userHP);
        turnCount++;
    }



}

void analysis(){
    printf("=== Analisis Return by Death ===");
}

int main() {
  float currentLearningPoints = 10;
  bool winningState = false;
  printf("=== Return by Death Battle Simulator ===\n");
  printf("Subaru vs Elsa Granhiert\n\n");


  int deathCount = 1;
  while(deathCount<=10 || !winningState){
    deathLoop(&deathCount, &currentLearningPoints, &winningState);
    deathCount++;
  }

  return 0;
}