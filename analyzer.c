#include <stdio.h>
#include <string.h>
#include "analyzer.h"
#include "input.h"
#include <ctype.h>


char *happy_words[] = {"heureux", "joyeux", "super", "cool", "content"};
char *sad_words[] = {"triste", "snif", "deprime", "mal", "pleure"};
char *angry_words[] = {"rage", "enerve", "marre", "colère", "agressif"};

char* cleanWord(const char *input) {
  if (input == NULL) {
    printf("word is null\n");
    return NULL;
  }

  char *word = strdup(input);

  if (word == NULL) {
    printf("strdup failed\n");
    return NULL;
  }

  int len = strlen(word);

  // remove non alpha char at the end
  while (len > 0 && !isalpha(word[len - 1])) {
    word[--len] = '\0';
  }

  // convert to lowercase
  for (int i = 0; word[i]; i++) {
    word[i] = tolower(word[i]);
  }

  return word;
}

// function to add key -> value
Word* addTarget(Word **words, const char *word, int feeling) {
  Word *key = NULL;

  // find if word already exists
  HASH_FIND_STR(*words, word, key);

  if ( NULL == key )  {
    // if the word doesn't exist yet, create a new one
    key = (Word *)malloc(sizeof(Word));
    key->word = strdup(word);
    key->feeling = feeling;
    HASH_ADD_STR(*words, word, key);
  }

  return key;
}


// get value by key
Word *getTarget(Word *words, const char *word) {
  Word *w = NULL;
  HASH_FIND_STR(words, word, w);
  return w;
}

Word* loadTargets() {
  Word *words = NULL;
  for (int i = 0; i < 5; i++) {
    addTarget(&words, happy_words[i], HAPPY);
    addTarget(&words, sad_words[i], SAD);
    addTarget(&words, angry_words[i], ANGRY);
  }

  return words;
}

void printTargets(Word *words) {
  Word *current_word, *tmp;

  HASH_ITER(hh, words, current_word, tmp) {
    printf("%s\t ------ \t %d\n", current_word->word, current_word->feeling);
  }
}


void freeTargets(Word *words) {
  Word *current_word, *tmp;
  HASH_ITER(hh, words, current_word, tmp) {
    HASH_DEL(words, current_word); // delete the hashes
    free(current_word->word); // free up memory for the word
    free(current_word);
  }
}


enum Feeling detectFeeling(Word *targets, char **words) {
  int happy = 0, sad = 0, angry = 0;

  for (int i = 0; i < getSArraySize(words); i++) {
    char *key = cleanWord(words[i]);
    if (key == NULL) {
      printf("key is null\n");
      continue;
    }; // skip null words
    Word *target = getTarget(targets, key);

    if (target != NULL) {
      if (target->feeling == HAPPY) happy++;
      else if (target->feeling == SAD) sad++;
      else if (target->feeling == ANGRY) angry++;
      
    } 

    free(key);
  }

  int max = happy;
  if (max < sad ) max = sad;
  if (max < angry) max = angry;

  int isNeutral = (happy == 0 && sad == 0 && angry == 0) || (happy == sad && happy == angry);

  if (isNeutral) 
    return NEUTRAL; 

  if (happy == max) return HAPPY;
  if (sad == max) return SAD;
  if (angry == max) return ANGRY;
  
}

void printFeeling(enum Feeling feeling) {
  switch (feeling) {
    case HAPPY: {printf("you are happy\n"); break;};
    case SAD: {printf("you are sad \n"); break;};
    case ANGRY: {printf("you are angry\n"); break;};
    case NEUTRAL:  {printf("you are neutral\n"); break;};
  }
}