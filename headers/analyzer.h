#ifndef ANALYZER_H
#define ANALYZER_H

#include "uthash.h"

typedef struct {
  char *word; // key
  int feeling; // value
  UT_hash_handle hh; // hashing function handlers
} Word;

enum Feeling {
  HAPPY = 0,
  SAD = 1,
  ANGRY = 2,
  NEUTRAL = 3
};

Word* addTarget(Word **words, const char *word, int feeling);
Word* getTarget(Word *words, const char *word);
void freeTargets(Word *words);
Word* loadTargets();
void printTargets(Word *words);
enum Feeling detectFeeling(Word *targets, char **words);
void printFeeling(enum Feeling feeling);

#endif