#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

char** getInput() {
  printf("prompt: ");
  char input[2000];
  fgets(input, 2000, stdin);

  char *word = strtok(input, " ");
  char **words = malloc(sizeof(char*));

  int i = 0;
  while (word != NULL) {
    if (strlen(word) != 0) {
      words[i] = malloc(strlen(word) + 1);
      strcpy(words[i++], word);
      words = realloc(words, (i + 1) * sizeof(char*));
    }
    word = strtok(NULL, " ");
  }

  words[i] = NULL;

  return words;
}

void printInputs(char **inputs) {
  for (int i = 0; i < getSArraySize(inputs); i++) {
    printf("%d: %s\n", i, inputs[i]);
  }
}

int getSArraySize(char **inputs) {
  int size = 0;
  while (inputs[size]) size++;
  return size;
}

void freeInputs(char **inputs) {
  for (int i = 0; i < getSArraySize(inputs); i++) {
    free(inputs[i]);  // libère chaque mot
  }
  free(inputs);  // libère le tableau de pointeurs
}