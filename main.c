#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyzer.h"
#include "input.h"


int main() {

  char **words = getInput();

  Word *targets = loadTargets();

  enum Feeling current_feeling = detectFeeling(targets, words);



  printFeeling(current_feeling);

  freeInputs(words);
  freeTargets(targets);

  return 0;
}