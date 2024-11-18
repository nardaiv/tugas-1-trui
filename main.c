#include <stdio.h>
#include <stdbool.h>


#define ELSA_BASE_HP 200
#define MAX_TURNS 5
#define MAX_HP 100

struct loopReport
{
    int damageSurvived;
    int damageDealt;
    int turnCount;
    char *deathCause;
    int learningPoints;
};

void attack(){

}

void dodge(){

}

void retreat(){

}


void battle(
    float *currentLearningPoints, int *damageDealt, int *damageSurvived, bool *reset, bool *winningState, int turnCount,

    //User
    int *userHP, float *attackMultiplier,
    
    //Elsa
    int *elsaHP, float *hpMultiplier
){
    
    char choice;

    printf("\nSubaru HP: %d | Elsa HP: %d\n", *userHP, *elsaHP);
    printf("Pilih aksi:\nA: Serang\nD: Menghindar\nR: Kabur (Reset ke checkpoint)\n");
    printf("Pilihan: ");
    scanf("%c", &choice);

    if(choice == "A"){
        attack();

    }else if(choice =="D"){
        dodge();

    }else if(choice=="R"){
        retreat();

    }else{
        //error handling
        printf("\nERROR : INVALID INPUT");
        exit(1);
    }

}

int calculateLearningPoint(int damageDealt,int turnSurvived,int damageSurvived ){
    int damageScore = damageDealt * 100 / ELSA_BASE_HP;
    int surivalScore = turnSurvived * 100 / MAX_TURNS ;
    int healtScore = (1 - (damageSurvived / (MAX_HP * turnSurvived)))*100;
    
    return 0.4*damageScore + 0.3*surivalScore + 0.3*healtScore;
}

void deathLoop(int *deathCount, float *currentLearningPoints, bool *winningState){

    int turnCount,damageDealt, damageSurvived = 0;
    bool reset = false;    

    // UserProperty
    int userHP = 100;
    float attackMultiplier = 0.5f + (*currentLearningPoints / 100.0f);

    // Elsa Property
    float damageMultiplier = damageMultiplier = 1.5f - (*currentLearningPoints / 200.0f);
    float hpMultiplier = 2.0f - (*currentLearningPoints / 100.0f);
    int elsaHP = (int)(ELSA_BASE_HP * hpMultiplier);;

    printf("[Death Loop #%d]\n", *deathCount);
    printf("Elsa's HP Multiplier: %0.2fx (Learning Points: %d)\n", hpMultiplier, *currentLearningPoints);

    while(userHP > 0 && !reset ){
        battle(
            currentLearningPoints, &damageDealt, &damageSurvived, &reset, &winningState, &turnCount,
            
            //User 
            &userHP, &damageMultiplier,  
            
            //Elsa
            &elsaHP, &hpMultiplier
        );
        turnCount++;
    }

    // calculate learning point received from last battle
    int learningPoint = calculateLearningPoint(damageDealt, turnCount, damageSurvived);
    
    // add learning point received from last battle
    *currentLearningPoints += learningPoint;

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
  while(deathCount<=10 && !winningState){
    deathLoop(&deathCount, &currentLearningPoints, &winningState);
    deathCount++;
  }

  return 0;
}