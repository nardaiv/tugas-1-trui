#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define ELSA_BASE_HP 200
#define BASE_ELSA_DAMAGE 20
#define MAX_TURNS 10
#define MAX_HP 100

struct LoopReport 
{
    int damageSurvived;
    int damageDealt;
    int turnCount;
    int learningPoints;
};

void attack(int *userHP, float attackMultiplier, int *elsaHp, float damageMultiplier, int *damageDealt, int *damageSurvived, bool *winningState, bool *reset, int turnCount){
    //get attack input from user
    int attackPower;
    printf("Masukkan kekuatan serangan (0-100): ");
    scanf("%d", &attackPower);

    //user attacks elsa
    int actualDamage = (int)(attackPower * attackMultiplier);
    printf("Subaru menyerang! Base: %d, Actual: %d (x%0.2f)\n", attackPower, actualDamage, attackMultiplier);
    *elsaHp -= actualDamage;
    *damageDealt += actualDamage;

    // elsa attacks user
    int elsaDamage = (int)((BASE_ELSA_DAMAGE + (turnCount * 5)) * damageMultiplier);
    printf("Elsa menyerang! Damage: %d (x%0.2f multiplier)\n", elsaDamage, damageMultiplier);
    *userHP -= elsaDamage;
    *damageSurvived += elsaDamage;

    if (*elsaHp < 0 ){
        *winningState = true;
        *reset = true;
    }

}

void dodge(){

}

void retreat(){

}


void battle(
    float *currentLearningPoints, int *damageDealt, int *damageSurvived, bool *reset, bool *winningState, int turnCount,

    //User
    int *userHP, float attackMultiplier,
    
    //Elsa
    int *elsaHP, float damageMultiplier
){
    
    char choice;

    printf("\nSubaru HP: %d | Elsa HP: %d\n", *userHP, *elsaHP);
    printf("Pilih aksi:\nA: Serang\nD: Menghindar\nR: Kabur (Reset ke checkpoint)\n");
    printf("Pilihan: ");
    scanf(" %c", &choice);

    if( choice == 'A'){
        attack(userHP, attackMultiplier, elsaHP, damageMultiplier, damageDealt, damageSurvived, winningState, reset, turnCount);

    }else if(choice =='D'){
        dodge();

    }else if(choice=='R'){
        retreat();

    }else{
        //error handling
        printf("\nERROR : INVALID INPUT");
        //exit(1);
    }

}

int calculateLearningPoint(int damageDealt,int turnSurvived,int damageSurvived ){
    float damageScore = damageDealt * 100 / ELSA_BASE_HP;
    float surivalScore = turnSurvived * 100 / MAX_TURNS ;
    float healtScore = (1.0f - ((float)damageSurvived / (MAX_HP * turnSurvived))) * 100;
    //printf("%f %f %f \n",damageScore, surivalScore, healtScore);
    
    return (int)(0.4*damageScore + 0.3*surivalScore + 0.3*healtScore);;
}

void deathLoop(int *deathCount, float *currentLearningPoints, bool *winningState, struct LoopReport *reports, int *reportCounter){

    int turnCount =0 ,damageDealt = 0 , damageSurvived = 0;
    bool reset = false;    

    // UserProperty
    int userHP = 100;
    float attackMultiplier = 0.5f + (*currentLearningPoints / 100.0f);

    // Elsa Property
    float damageMultiplier = damageMultiplier = 1.5f - (*currentLearningPoints / 200.0f);
    float hpMultiplier = 2.0f - (*currentLearningPoints / 100.0f);
    int elsaHP = (int)(ELSA_BASE_HP * hpMultiplier);;

    printf("\n[Death Loop #%d]\n", *deathCount);
    printf("Elsa's HP Multiplier: %0.2fx (Learning Points: %1.0f)\n", hpMultiplier, *currentLearningPoints);

    while(userHP > 0 && !reset ){
        battle(
            currentLearningPoints, &damageDealt, &damageSurvived, &reset, winningState, turnCount,
            
            //User 
            &userHP, attackMultiplier,  
            
            //Elsa
            &elsaHP, damageMultiplier
        );
        turnCount++;
    }

    //printf("%d %d %d \n",damageDealt, turnCount, damageSurvived);
    // calculate learning point received from last battle
    int learningPoint = calculateLearningPoint(damageDealt, turnCount, damageSurvived);
    
    // add learning point received from last battle
    *currentLearningPoints = learningPoint;

    struct LoopReport newReport = {damageSurvived, damageDealt, turnCount, (int)learningPoint};
    reports[*reportCounter] = newReport;
    //printf("%d %d %d %d", newReport.damageSurvived, newReport.damageDealt, newReport.turnCount, newReport.learningPoints);
    *reportCounter+= 1;
}

float average(struct LoopReport reports[], int choice, int lenght){
    int sum = 0 ;
    for( int i= 0; i < lenght; i++){
        int num = (choice == 1) ? reports[i].learningPoints : reports[i].damageSurvived;
        sum += num;
    }
    return (float) sum / lenght;
}

char* learningPointsCategory(float learningPoint){
    if (learningPoint >= 85){
        return "SEMPURNA (Memahami semua pola serangan)";
    }else if(learningPoint >= 70){
        return "TINGGI (Memahami sebagian besar pola)";
    }else if(learningPoint >= 55){
        return "SEDANG (Mulai memahami pola dasar)";
    }else if(learningPoint >= 40){
        return "RENDAH (Masih banyak yang belum dipahami)";
    }else {
        return "MINIMAL (Belum memahami pola)";
    }
}

void deathData(int index,struct LoopReport report){
    printf("\nLoop #%d:\n", index+1);
    printf("Damage ke Elsa: %d \n", report.damageDealt);
    printf("Damage Diterima: %d \n", report.damageSurvived);
    printf("Bertahan selama: %d turn\n", report.turnCount);
    printf("Penyebab Kematian: Sayatan Normal\n");
    printf("Learning Points: %d\n", report.learningPoints);


}

void analysis(struct LoopReport *reports, int reportCounter){
    printf("\n=== Analisis Return by Death ===\n"); 

    printf("Total Loop Kematian: %d\n", reportCounter);
    float averageLearningPoints = average(reports, 1, reportCounter);
    printf("Rata-rata Learning Points: %0.2f\n", averageLearningPoints);
    printf("\nPemahaman Subaru tentang Elsa: %s\n", learningPointsCategory(averageLearningPoints));
    printf("Detail Setiap Loop:\n");
    for(int i = 0; i < reportCounter; i++){
        deathData(i, reports[i]);
    }

}

int main() {
  float currentLearningPoints = 10;
  bool winningState = false;
  struct LoopReport reports[10];
  int reportCounter = 0;

  printf("=== Return by Death Battle Simulator ===\n");
  printf("Subaru vs Elsa Granhiert\n");

  int deathCount = 1;
  while(deathCount<=10 && !winningState){
    deathLoop(&deathCount, &currentLearningPoints, &winningState, reports, &reportCounter);
    deathCount++;
  }

  if(winningState){
    printf("\nSUBARU BERHASIL MENGALAHKAN ELSA!\n");
  }else{
    printf("\nSUBARU TIDAK BERHASIL MENGALAHKAN ELSA!\n");
  }

    
  analysis(reports, reportCounter);

  return 0;
}