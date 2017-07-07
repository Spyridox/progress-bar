// Aron Fiechter
// 2017-03-01

// Simulates 100 coin tosses where a winnin value (initially 0) is increased by
// 1 when the fair coin gives heads, and decreased by 1 when the fair coin gives
// tails.
// This experiment is repeated <trials> times, and at the end gives information
// on how many times the result was <number>.
// Execution: ./2_coins <trials:int> <number:int(even)>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int sim_coin();
void build_progress(char* progress, unsigned int n);

int main(int argc, char const *argv[]) {

  srand(time(NULL));

  if (argc != 3) {
    printf("Please enter a number of trials and a number to test.\n");
    return 0;
  }

  // read input arguments
  double trials;
  sscanf(argv[1],"%lf", &trials);
  int number = atoi(argv[2]);
  double current_trial = trials;

  // fancy progress bar
  char progress[51];

  // counting occurrences of number
  float occurrences = 0.0; // if not initialised randomly becomes high number
  float percent = 0.0;

  printf("Starting %d trials\n", (int) trials);
  while (current_trial-- > 0) {

    // count occurrences of number at each cycle
    int result = sim_coin();
    occurrences += (result == number) ? 1.0 : 0.0;

    // show nice progress bar for long experiments (high number of trials)
    printf("%c", '\r');
    fflush(stdout);
    double progress_percent = 100 - 100*current_trial/trials;
    unsigned int n = progress_percent/2;
    build_progress(progress, n);
    printf("Progress:[%s] %lf %c", progress, progress_percent, 37);
  }

  // compute percentage of occurrences on the total number of trials
  percent = 100 * (occurrences/trials);

  // print final experiment results
  printf("\nOccurrence of outcome [%d]: %f %c\n\n", number, percent, 37);

  return 0;
}

int sim_coin() {
  int result = 0;

  // make 100 coin tosses
  for (size_t i = 0; i < 100; i++) {
    result += (rand() % 2) == 0 ? -1 : 1;
  }

  return result;
}

void build_progress(char* progress, unsigned int n) {
  for (int i = 0; i < 50; i++) {
    progress[i] = i < n ? 35 : 32;
  }
  progress[50] = '\0';
}
