#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
}  TFlags;

void obnulenie_struct(TFlags *flags);
int opredelenie_flags(int argc, char** argv, TFlags *flags);
void readFile(char* whatIsfile, TFlags flags);

#endif  //  SRC_CAT_S21_CAT_H_
