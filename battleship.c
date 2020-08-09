#include <stdio.h>

#include <ncurses.h>

#include <stdlib.h>

#include <time.h>

#include <unistd.h>


#define latime_menu 40
# define inaltime_menu 15
# define latime_joc 60
# define inaltime_joc 20

//functiile de mai jos aloca dinamic matricele utilizate in joc
void alocare_matrice(char ** * v, int n) {
  int i;
  * v = ((char ** ) malloc(n * sizeof(char * )));
  for (i = 0; i < n; i++) {
    ( * v)[i] = (char * ) malloc(n * sizeof(char));

  }
}

void alocare_matrice_parcurgere(int ** * v, int n) {
  int i;
  * v = ((int ** ) malloc(n * sizeof(int * )));
  for (i = 0; i < n; i++)
    ( * v)[i] = (int * ) malloc(n * sizeof(int));

}

//functia completeaza toate elementele
//matricei cu caracterul spatiu pentru a facilita
//mai tarziu completarea cu simbolurile X # -
void compunere_matrice(char ** * v, int n) {
  int i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      ( * v)[i][j] = ' ';

}

//cele 2 functii de mai jos elibereaza memoria utilizata
void eliberare(char ** v, int n) {
  int i;
  for (i = 0; i < n; i++)
    free(v[i]);
  free(v);
}

void eliberare_parcurgere(int ** v, int n) {
  int i;
  for (i = 0; i < n; i++)
    free(v[i]);
  free(v);
}

//cele 6 functii de mai jos au rolul de a pune navele pe harta
// in conditiile in care sa indeplineasca anumite conditii de la functiile
//populare_nava1 populare_nava2 populare_nava3 populare_nava4
int up(char ** * v, int i, int j, int n) {
  if (j == 0) {
    if (( * v)[i][j + 1] == 'X' || ( * v)[i + 1][j] == 'X' || ( * v)[i + 1][j + 1] == 'X') return 0;
  } else if (j == n) {
    if (( * v)[i][j - 1] == 'X' || ( * v)[i + 1][j] == 'X' || ( * v)[i + 1][j - 1] == 'X') return 0;
  } else if (( * v)[i][j - 1] == 'X' || ( * v)[i][j + 1] == 'X' || ( * v)[i + 1][j] == 'X' || ( * v)[i + 1][j - 1] == 'X' || ( * v)[i + 1][j + 1] == 'X') return 0;
  return 1;
}

int down(char ** * v, int i, int j, int n) {
  if (j == 0) {
    if (( * v)[i][j + 1] == 'X' || ( * v)[i - 1][j] == 'X' || ( * v)[i - 1][j + 1] == 'X') return 0;
  } else if (j == n) {
    if (( * v)[i - 1][j] == 'X' || ( * v)[i][j - 1] == 'X' || ( * v)[i - 1][j - 1] == 'X') return 0;
  } else if (( * v)[i][j - 1] == 'X' || ( * v)[i][j + 1] == 'X' || ( * v)[i - 1][j - 1] == 'X' || ( * v)[i - 1][j + 1] == 'X' || ( * v)[i - 1][j] == 'X') return 0;
  return 1;
}

int left(char ** * v, int i, int j, int n) {

  if (( * v)[i - 1][j] == 'X' || ( * v)[i + 1][j] == 'X' || ( * v)[i][j + 1] == 'X' || ( * v)[i - 1][j + 1] == 'X' || ( * v)[i + 1][j + 1] == 'X') return 0;
  return 1;
}

int right(char ** * v, int i, int j, int n) {

  if (( * v)[i - 1][j] == 'X' || ( * v)[i + 1][j] == 'X' || ( * v)[i][j - 1] == 'X' || ( * v)[i - 1][j - 1] == 'X' || ( * v)[i + 1][j - 1] == 'X') return 0;
  return 1;
}

int directii(char ** * v, int i, int j) {

  if (( * v)[i][j + 1] == 'X' || ( * v)[i][j - 1] == 'X' || ( * v)[i + 1][j] == 'X' || ( * v)[i - 1][j] == 'X') return 0;
  return 1;

}

int colturi(char ** * v, int i, int j) {

  if (( * v)[i - 1][j - 1] == 'X' || ( * v)[i - 1][j + 1] == 'X' || ( * v)[i + 1][j + 1] == 'X' || ( * v)[i + 1][j - 1] == 'X') return 0;
  return 1;

}
//functie cu rolul de a verifica daca elementul nu a depasit limitele matricei
int verificare(char ** * v, int i, int j, int n) {

  if (i == 0) {
    if (up(v, i, j, n - 1) && ( * v)[i][j] != 'X') return 1;
  } else if (i == n - 1) {
    if (down(v, i, j, n - 1) && ( * v)[i][j] != 'X') return 1;
  } else if (j == 0) {
    if (left(v, i, j, n - 1) && ( * v)[i][j] != 'X') return 1;
  } else if (j == n - 1) {
    if (right(v, i, j, n - 1) && ( * v)[i][j] != 'X') return 1;
  } else if (colturi(v, i, j) && directii(v, i, j) && ( * v)[i][j] != 'X') return 1;
  return 0;

}
// functie cu rolul de a pune pe mapa nava de 1 casute
void populare_nava1(char ** * v, int n) {
  int flag = 0;
  int i, j;
  while (flag == 0) {

    i = rand() % 10;
    j = rand() % 10;
    if (verificare(v, i, j, n)) flag = 1;

  }
  ( * v)[i][j] = 'X';

}
// functie cu rolul de a pune pe mapa nava de 2 casute
void populare_nava2(char ** * v, int n) {
  int flag1 = 0, flag2 = 0, cond;
  int conditie[5];
  int i, j, k, gasit = 1;
  while (flag2 == 0) {
    flag1 = 0;
    while (flag1 == 0) {

      i = rand() % 10;
      j = rand() % 10;
      if (verificare(v, i, j, n)) flag1 = 1;
    }
    gasit = 1;
    for (k = 1; k <= 4; k++)
      conditie[k] = 0;
    while (gasit) {
      cond = rand() % 4 + 1;
      if (j + 1 >= 0 && j + 1 <= n - 1 && cond == 1) {
        if (verificare(v, i, j + 1, n)) {
          flag2 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i][j + 1] = 'X';
          break;
        }
      }
      if (j - 1 >= 0 && j - 1 <= n - 1 && cond == 2) {
        if (verificare(v, i, j - 1, n)) {
          flag2 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i][j - 1] = 'X';
          break;
        }
      }
      if (i + 1 >= 0 && i + 1 <= n - 1 && cond == 3) {
        if (verificare(v, i + 1, j, n)) {
          flag2 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i + 1][j] = 'X';
          break;
        }
      }
      if (i - 1 >= 0 && i - 1 <= n - 1 && cond == 4) {
        if (verificare(v, i - 1, j, n)) {
          flag2 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i - 1][j] = 'X';
          break;
        }
      }
      conditie[cond]++;
      for (k = 1; k <= 4; k++)
        if (conditie[k] == 0) gasit = 0;
    }
  }

}
// functie cu rolul de a pune pe mapa nava de 3 casute
void populare_nava3(char ** * v, int n) {
  int flag1 = 0, flag2 = 0, flag3 = 0, cond;
  int conditie[5];
  int i, j, gasit = 1, k;
  while (flag3 == 0) {
    flag2 = 0;
    flag1 = 0;
    while (flag2 == 0) {
      flag1 = 0;
      while (flag1 == 0) {

        i = rand() % 10;
        j = rand() % 10;
        if (verificare(v, i, j, n)) flag1 = 1;
      }

      gasit = 1;
      for (k = 1; k <= 4; k++)
        conditie[k] = 0;
      while (gasit) {
        cond = rand() % 4 + 1;
        if (j + 1 >= 0 && j + 1 <= n - 1 && cond == 1) {
          if (verificare(v, i, j + 1, n)) {
            flag2 = 1;
            break;
          }
        } else if (j - 1 >= 0 && j - 1 <= n - 1 && cond == 2) {
          if (verificare(v, i, j - 1, n)) {
            flag2 = 1;
            break;
          }
        } else if (i + 1 >= 0 && i + 1 <= n - 1 && cond == 3) {
          if (verificare(v, i + 1, j, n)) {
            flag2 = 1;
            break;
          }
        } else if (i - 1 >= 0 && i - 1 <= n - 1 && cond == 4) {
          if (verificare(v, i - 1, j, n)) {
            flag2 = 1;
            break;
          }
        }
        conditie[cond]++;
        for (k = 1; k <= 4; k++)
          if (conditie[k] == 0) gasit = 0;
      }
    }

    switch (cond) {
    case 1:
      if (j + 2 >= 0 && j + 2 <= n - 1)
        if (verificare(v, i, j + 2, n)) {
          flag3 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i][j + 1] = 'X';
          ( * v)[i][j + 2] = 'X';
        }
      break;
    case 2:
      if (j - 2 >= 0 && j - 2 <= n - 1)
        if (verificare(v, i, j - 2, n)) {
          flag3 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i][j - 1] = 'X';
          ( * v)[i][j - 2] = 'X';
        }
      break;
    case 3:
      if (i + 2 >= 0 && i + 2 <= n - 1)
        if (verificare(v, i + 2, j, n)) {
          flag3 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i + 1][j] = 'X';
          ( * v)[i + 2][j] = 'X';
        }
      break;
    case 4:
      if (i - 2 >= 0 && i - 2 <= n - 1)
        if (verificare(v, i - 2, j, n)) {
          flag3 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i - 1][j] = 'X';
          ( * v)[i - 2][j] = 'X';
        }
      break;
    default:
      break;
    }
  }
}
// functie cu rolul de a pune pe mapa nava de 4 casute
void populare_nava4(char ** * v, int n) {
  int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, cond;
  int conditie[5];
  int i, j, gasit = 1, k;
  while (flag4 == 0) {
    flag1 = 0, flag2 = 0, flag3 = 0;
    while (flag3 == 0) {
      flag2 = 0;
      flag1 = 0;
      while (flag2 == 0) {
        flag1 = 0;
        while (flag1 == 0) {

          i = rand() % 10;
          j = rand() % 10;
          if (verificare(v, i, j, n)) flag1 = 1;
        }

        gasit = 1;
        for (k = 1; k <= 4; k++)
          conditie[k] = 0;
        while (gasit) {
          cond = rand() % 4 + 1;
          if (j + 1 >= 0 && j + 1 <= n - 1 && cond == 1) {
            if (verificare(v, i, j + 1, n)) {
              flag2 = 1;
              break;
            }
          } else if (j - 1 >= 0 && j - 1 <= n - 1 && cond == 2) {
            if (verificare(v, i, j - 1, n)) {
              flag2 = 1;
              break;
            }
          } else if (i + 1 >= 0 && i + 1 <= n - 1 && cond == 3) {
            if (verificare(v, i + 1, j, n)) {
              flag2 = 1;
              break;
            }
          } else if (i - 1 >= 0 && i - 1 <= n - 1 && cond == 4) {
            if (verificare(v, i - 1, j, n)) {
              flag2 = 1;
              break;
            }
          }
          conditie[cond]++;
          for (k = 1; k <= 4; k++)
            if (conditie[k] == 0) gasit = 0;
        }
      }

      switch (cond)

      {
      case 1:
        if (j + 2 >= 0 && j + 2 <= n - 1)
          if (verificare(v, i, j + 2, n)) flag3 = 1;
        break;
      case 2:
        if (j - 2 >= 0 && j - 2 <= n - 1)
          if (verificare(v, i, j - 2, n)) flag3 = 1;
        break;
      case 3:
        if (i + 2 >= 0 && i + 2 <= n - 1)
          if (verificare(v, i + 2, j, n)) flag3 = 1;
        break;
      case 4:
        if (i - 2 >= 0 && i - 2 <= n - 1)
          if (verificare(v, i - 2, j, n)) flag3 = 1;
        break;
      default:
        break;
      }
    }
    switch (cond) {
    case 1:
      if (j + 3 >= 0 && j + 3 <= n - 1)
        if (verificare(v, i, j + 3, n)) {
          flag4 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i][j + 1] = 'X';
          ( * v)[i][j + 2] = 'X';
          ( * v)[i][j + 3] = 'X';
        }
      break;
    case 2:
      if (j - 3 >= 0 && j - 3 <= n - 1)
        if (verificare(v, i, j - 3, n)) {
          flag4 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i][j - 1] = 'X';
          ( * v)[i][j - 2] = 'X';
          ( * v)[i][j - 3] = 'X';
        }
      break;
    case 3:
      if (i + 3 >= 0 && i + 3 <= n - 1)
        if (verificare(v, i + 3, j, n)) {
          flag4 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i + 1][j] = 'X';
          ( * v)[i + 2][j] = 'X';
          ( * v)[i + 3][j] = 'X';
        }
      break;
    case 4:
      if (i - 3 >= 0 && i - 3 <= n - 1)
        if (verificare(v, i - 3, j, n)) {
          flag4 = 1;
          ( * v)[i][j] = 'X';
          ( * v)[i - 1][j] = 'X';
          ( * v)[i - 2][j] = 'X';
          ( * v)[i - 3][j] = 'X';
        }
      break;
    default:
      break;
    }
  }
}
//cele 4 functii de mai jos sunt folosite in functia "randomize_map_task4"
int verifica(char ** * v, int i, int j) {
  if (( * v)[i][j] != '#' && ( * v)[i][j] != 'X') return 0;
  return 1;
}

void nave_ramase_vertical(int constant, int start, int final, int * nrX, char ** * v) {
  int k;
  * nrX = 0;
  for (k = start; k <= final; k++)
    if (( * v)[k][constant] == 'X') * nrX = * nrX + 1;
}

void nave_ramase_orizontal(int constant, int start, int final, int * nrX, char ** * v) {
  int k;
  * nrX = 0;
  for (k = start; k <= final; k++)
    if (( * v)[constant][k] == 'X') * nrX = * nrX + 1;
}
int verifica_vertical(int i, int j, char ** * v, int n) {
  if (i + 1 <= n - 1)
    if (( * v)[i + 1][j] == '#' || ( * v)[i + 1][j] == 'X') return 0;

  if (i - 1 >= 0)
    if (( * v)[i - 1][j] == '#' || ( * v)[i - 1][j] == 'X') return 0;

  return 1;
}

// recrearea mapelor dupa alegerea optiunii de randomizare
void randomize_map_task4(char ** * v, int n, int * nr1, int * nr2, int * nr3, int * nr4) {

  int i, j;
  int parcurgere[10][10] = {
    0
  };
  int nrX = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (( * v)[i][j] == 'X') parcurgere[i][j] = 1;
      if (( * v)[i][j] == '#') parcurgere[i][j] = 2;
    }
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (parcurgere[i][j] != 0) {

        if (j + 3 <= n - 1 && verifica_vertical(i, j, v, n) && verifica(v, i, j) && verifica(v, i, j + 1) && verifica(v, i, j + 2) && verifica(v, i, j + 3)) {
          parcurgere[i][j] = 0;
          parcurgere[i][j + 1] = 0;
          parcurgere[i][j + 2] = 0;
          parcurgere[i][j + 3] = 0;
          nave_ramase_orizontal(i, j, j + 3, & nrX, v);

          if (nrX == 1) * nr1 = * nr1 + 1;
          else if (nrX == 2) * nr2 = * nr2 + 1;
          else if (nrX == 3) * nr3 = * nr3 + 1;
          else if (nrX == 4) * nr4 = * nr4 + 1;

        } else if (j + 2 <= n - 1 && verifica_vertical(i, j, v, n) && verifica(v, i, j) && verifica(v, i, j + 1) && verifica(v, i, j + 2)) {
          parcurgere[i][j] = 0;
          parcurgere[i][j + 1] = 0;
          parcurgere[i][j + 2] = 0;
          nave_ramase_orizontal(i, j, j + 2, & nrX, v);

          if (nrX == 1) * nr1 = * nr1 + 1;
          else if (nrX == 2) * nr2 = * nr2 + 1;
          else if (nrX == 3) * nr3 = * nr3 + 1;

        } else if (j + 1 <= n - 1 && verifica_vertical(i, j, v, n) && verifica(v, i, j) && verifica(v, i, j + 1)) {
          parcurgere[i][j] = 0;
          parcurgere[i][j + 1] = 0;
          nave_ramase_orizontal(i, j, j + 1, & nrX, v);

          if (nrX == 1) * nr1 = * nr1 + 1;
          else if (nrX == 2) * nr2 = * nr2 + 1;

        } else if (verifica_vertical(i, j, v, n) && verifica(v, i, j)) {
          parcurgere[i][j] = 0;
          nave_ramase_orizontal(i, j, j, & nrX, v);
          if (nrX == 1) * nr1 = * nr1 + 1;

        }
      }
    }


for (j = 0; j < n; j++)
  for (i = 0; i < n; i++)
    if (parcurgere[i][j] != 0) {

      if (i + 3 <= n - 1 && verifica(v, i, j) && verifica(v, i + 1, j) && verifica(v, i + 2, j) && verifica(v, i + 3, j)) {
        parcurgere[i][j] = 0;
        parcurgere[i + 1][j] = 0;
        parcurgere[i + 2][j] = 0;
        parcurgere[i + 3][j] = 0;
        nave_ramase_vertical(j, i, i + 3, & nrX, v);
        if (nrX == 1) * nr1 = * nr1 + 1;
        else if (nrX == 2) * nr2 = * nr2 + 1;
        else if (nrX == 3) * nr3 = * nr3 + 1;
        else if (nrX == 4) * nr4 = * nr4 + 1;

      } else if (i + 2 <= n - 1 && verifica(v, i, j) && verifica(v, i + 1, j) && verifica(v, i + 2, j)) {
        parcurgere[i][j] = 0;
        parcurgere[i + 1][j] = 0;
        parcurgere[i + 2][j] = 0;
        nave_ramase_vertical(j, i, i + 2, & nrX, v);

        if (nrX == 1) * nr1 = * nr1 + 1;
        else if (nrX == 2) * nr2 = * nr2 + 1;
        else if (nrX == 3) * nr3 = * nr3 + 1;

      } else if (i + 1 <= n - 1 && verifica(v, i, j) && verifica(v, i + 1, j)) {
        parcurgere[i][j] = 0;
        parcurgere[i + 1][j] = 0;
        nave_ramase_vertical(j, i, i + 1, & nrX, v);

        if (nrX == 1) * nr1 = * nr1 + 1;
        else if (nrX == 2) * nr2 = * nr2 + 1;

      } else if (verifica(v, i, j)) {
        parcurgere[i][j] = 0;

        if (nrX == 1) * nr1 = * nr1 + 1;

      }

    }

}
//functia care calculeaza scorul fiecarui jucator
void score(char ** * v, int n, int * nave_distruse) {

  int i, j;
  int parcurgere[10][10] = {
    0
  };
  int nrX = 0;
  * nave_distruse = 0;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (( * v)[i][j] == 'X') parcurgere[i][j] = 1;
      if (( * v)[i][j] == '#') parcurgere[i][j] = 2;
    }

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      if (parcurgere[i][j] != 0) {

        if (j + 3 <= n - 1 && verifica_vertical(i, j, v, n) && verifica(v, i, j) && verifica(v, i, j + 1) && verifica(v, i, j + 2) && verifica(v, i, j + 3)) {
          parcurgere[i][j] = 0;
          parcurgere[i][j + 1] = 0;
          parcurgere[i][j + 2] = 0;
          parcurgere[i][j + 3] = 0;
          nave_ramase_orizontal(i, j, j + 3, & nrX, v);
          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        } else if (j + 2 <= n - 1 && verifica_vertical(i, j, v, n) && verifica(v, i, j) && verifica(v, i, j + 1) && verifica(v, i, j + 2)) {
          parcurgere[i][j] = 0;
          parcurgere[i][j + 1] = 0;
          parcurgere[i][j + 2] = 0;
          nave_ramase_orizontal(i, j, j + 2, & nrX, v);
          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        } else if (j + 1 <= n - 1 && verifica_vertical(i, j, v, n) && verifica(v, i, j) && verifica(v, i, j + 1)) {
          parcurgere[i][j] = 0;
          parcurgere[i][j + 1] = 0;
          nave_ramase_orizontal(i, j, j + 1, & nrX, v);
          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        } else if (verifica_vertical(i, j, v, n) && verifica(v, i, j)) {
          parcurgere[i][j] = 0;
          nave_ramase_orizontal(i, j, j, & nrX, v);
          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        }
      }

    }

  for (j = 0; j < n; j++)
    for (i = 0; i < n; i++)
      if (parcurgere[i][j] != 0) {

        if (i + 3 <= n - 1 && verifica(v, i, j) && verifica(v, i + 1, j) && verifica(v, i + 2, j) && verifica(v, i + 3, j)) {
          parcurgere[i][j] = 0;
          parcurgere[i + 1][j] = 0;
          parcurgere[i + 2][j] = 0;
          parcurgere[i + 3][j] = 0;
          nave_ramase_vertical(j, i, i + 3, & nrX, v);
          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        } else if (i + 2 <= n - 1 && verifica(v, i, j) && verifica(v, i + 1, j) && verifica(v, i + 2, j)) {

          parcurgere[i][j] = 0;
          parcurgere[i + 1][j] = 0;
          parcurgere[i + 2][j] = 0;
          nave_ramase_vertical(j, i, i + 2, & nrX, v);

          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        } else if (i + 1 <= n - 1 && verifica(v, i, j) && verifica(v, i + 1, j)) {

          parcurgere[i][j] = 0;
          parcurgere[i + 1][j] = 0;
          nave_ramase_vertical(j, i, i + 1, & nrX, v);
          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        } else if (verifica(v, i, j)) {

          parcurgere[i][j] = 0;
          nave_ramase_vertical(j, i, i, & nrX, v);
          if (nrX == 0) * nave_distruse = * nave_distruse + 1;

        }
      }

}

//functia asigura randomizarea mapei computerului
void random_map(char ** * v, int n, int nr1, int nr2, int nr3, int nr4) {
  int i;

  for (i = 1; i <= nr4; i++)
    populare_nava4(v, n);

  for (i = 1; i <= nr3; i++)
    populare_nava3(v, n);

  for (i = 1; i <= nr2; i++)
    populare_nava2(v, n);

  for (i = 1; i <= nr1; i++)
    populare_nava1(v, n);

}

//marcheaza pozitia cursorului pe meniu in timp ce este parcurs de jucator
void print_menu(WINDOW * menu_win, int highlight, int nr_argumente, char ** v) {
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for (i = 0; i < nr_argumente; i++) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", v[i]);
      wattroff(menu_win, A_REVERSE);
    } else
      mvwprintw(menu_win, y, x, "%s", v[i]);
    y++;
  }
  wrefresh(menu_win);
}

//meniul generalizat pentru cazurile din main
void menu(WINDOW * menu_win, int * tasta_aleasa, int nr_argumente, char ** v) {
  int highlight = 1;
  int c;
  keypad(menu_win, TRUE);
  mvprintw(2, 35, "Battleship");
  mvprintw(3, 18, "Foloseste sagetile pentru a naviga in menu:)");
  refresh();
  print_menu(menu_win, highlight, nr_argumente, v);
  while (1) {
    c = wgetch(menu_win);
    switch (c) {
    case KEY_UP:
      if (highlight == 1)
        highlight = nr_argumente;
      else
        --highlight;
      break;
    case KEY_DOWN:
      if (highlight == nr_argumente)
        highlight = 1;
      else
        ++highlight;
      break;
    case 10:
      *
      tasta_aleasa = highlight;
      break;
    default:
      break;
    }
    print_menu(menu_win, highlight, nr_argumente, v);
    if ( * tasta_aleasa != 0)
      break;
  }
}

// functia care marcheaza pozitia jucatorului, dar si starea mapei parcurse
void print_table(WINDOW * menu_win, int highlight_i, int highlight_j, int n, char ** * v) {
  int x, y, i, j;
  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      if (highlight_i == i && highlight_j == j) {
        mvwprintw(menu_win, y, x, "|");
        x++;
        if (( * v)[i][j] == 'X') {
          wattron(menu_win, A_REVERSE);
          mvwprintw(menu_win, y, x, " ");
          wattroff(menu_win, A_REVERSE);
        } else {
          wattron(menu_win, A_REVERSE);
          mvwprintw(menu_win, y, x, "%c", ( * v)[i][j]);
          wattroff(menu_win, A_REVERSE);
        }
        x++;
      }
    else {
      mvwprintw(menu_win, y, x, "|");
      x++;
      if (( * v)[i][j] == 'X')
        mvwprintw(menu_win, y, x, " ");
      else
        mvwprintw(menu_win, y, x, "%c", ( * v)[i][j]);

      x++;
    }
    mvwprintw(menu_win, y, x, "|");
    x++;
    x = 2;
    y++;
  }
  wrefresh(menu_win);
}
// functia cu rolul de a printa mapa jucatorului parcursa
//de computer in timpului jocului(dreapta)
void print_table_computer(WINDOW * menu_win, char ** * v, int n, int startx, int starty, int flag) {
  int x, y;
  int i, j;
  x = startx;
  y = starty;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      mvwprintw(menu_win, y, x, "|");
      x++;
      mvwprintw(menu_win, y, x, "%c", ( * v)[i][j]);
      x++;
    }
    mvwprintw(menu_win, y, x, "|");
    x = startx;
    y++;
  }
  wrefresh(menu_win);
  if (flag == 1) sleep(3);
}

// functia care verifica daca pozitia pe care si-a
//ales-o computerul e diferita de cele anterioare
void no_repeat(int i_rand, int j_rand, char ** * v) {
  while (( * v)[i_rand][j_rand] == '#' || ( * v)[i_rand][j_rand] == '-') {
    i_rand = rand() % 10;
    j_rand = rand() % 10;
  }
}

//functia care indeplineste comanda "destroy advance"
void destroy_advance(char ** * v, int n) {
  int nr = 10, i_rand, j_rand;
  while (nr != 0) {
    i_rand = rand() % 10;
    j_rand = rand() % 10;
    no_repeat(i_rand, j_rand, v);
    if (( * v)[i_rand][j_rand] == 'X')( * v)[i_rand][j_rand] = '#';
    else
    if (( * v)[i_rand][j_rand] != '#' && ( * v)[i_rand][j_rand] != '-')( * v)[i_rand][j_rand] = '-';
    nr--;

  }
}

//functia care descrie miscarile computerului
void computer_round(WINDOW * menu_win, int n, char ** * v) {
  int i_rand, j_rand;
  i_rand = rand() % 10;
  j_rand = rand() % 10;
  no_repeat(i_rand, j_rand, v);
  while (( * v)[i_rand][j_rand] == 'X') {

    ( * v)[i_rand][j_rand] = '#';
    print_table_computer(menu_win, v, n, 27, 2, 1);
    i_rand = rand() % 10;
    j_rand = rand() % 10;
    no_repeat(i_rand, j_rand, v);

  }
  if (( * v)[i_rand][j_rand] == ' ') {
    ( * v)[i_rand][j_rand] = '-';
    print_table_computer(menu_win, v, n, 27, 2, 1);
  }

}

//functie cu rolul de actualiza un vector cu zerouri
void zero(int ** * v, int n) {
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      ( * v)[i][j] = 0;

}

// se reactulizeaza vectorul folosit in joc care descrie starea mapei
//  jucatorului(nu calculator) cand acesta trece pe zone vizitate
void parcurgere_reactualizare(char ** * v, int n, int ** * parcurgere) {
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (( * v)[i][j] == '#' || ( * v)[i][j] == '-')( * parcurgere)[i][j] = 1;
      else( * parcurgere)[i][j] = 0;
}

// acesta este functia care descrie jocul, bazandu-se pe apelarea altor functii
void battleship(WINDOW * menu_win, int n, char ** * v1, char ** * v2, int * nr_nave_lovite1, int * nr_nave_lovite2, int ** * parcurgere) {
  int highlight_i = 0;
  int highlight_j = 0;
  int c, meniu_intoarcere = 0;
  int nr1 = 0, nr2 = 0, nr3 = 0, nr4 = 0;
  int nr_nave_lovp1 = 0, nr_nave_lovp2 = 0;

  keypad(menu_win, TRUE);
  mvprintw(0, 35, "Battleship");
  mvprintw(1, 18, "Foloseste sagetile pentru a naviga in joc:)");
  mvwprintw(menu_win, 16, 3, "Pentru \"Destroy in advance\" folositi tasta F1 ");
  mvwprintw(menu_win, 17, 3, "Pentru \"Randomize map\" folositi tasta F2 ");
  mvwprintw(menu_win, 18, 3, "Ca sa va intoarceti in meniu folositi tasta F3 ");
  refresh();
  print_table(menu_win, highlight_i, highlight_j, n, v1);
  print_table_computer(menu_win, v2, n, 27, 2, 0);
  //structura repetitiva cu rolul de a-l ajuta pe jucator sa se deplaseze pe mapa 
  // fara sa treaca de margini
  while (1) {
    c = wgetch(menu_win);
    switch (c) {
    case KEY_UP:
      if (highlight_i == 0)
        highlight_i = n - 1;
      else
        --highlight_i;
      break;
    case KEY_DOWN:
      if (highlight_i == n - 1)
        highlight_i = 0;
      else
        ++highlight_i;
      break;
    case KEY_LEFT:
      if (highlight_j == 0)
        highlight_j = n - 1;
      else
        --highlight_j;
      break;
    case KEY_RIGHT:
      if (highlight_j == n - 1)
        highlight_j = 0;
      else
        ++highlight_j;
      break;
    case KEY_F(1):
      // in cazul in care s-a selectat modul "destroy advance"
      destroy_advance(v1, n);
      parcurgere_reactualizare(v1, n, parcurgere);
      destroy_advance(v2, n);
      print_table_computer(menu_win, v2, n, 27, 2, 0);
      break;
    case KEY_F(2):
      // in cazul in care s-a selectat modul "randomize map"
      nr1 = 0, nr2 = 0, nr3 = 0, nr4 = 0;
      zero(parcurgere, 10);
      score(v1, n, & nr_nave_lovp1);
      * nr_nave_lovite1 = * nr_nave_lovite1 + nr_nave_lovp1;
      score(v2, n, & nr_nave_lovp2);
      * nr_nave_lovite2 = * nr_nave_lovite2 + nr_nave_lovp2;
      randomize_map_task4(v2, n, & nr1, & nr2, & nr3, & nr4);
      compunere_matrice(v2, n);
      random_map(v2, n, nr1, nr2, nr3, nr4);
      print_table_computer(menu_win, v2, n, 27, 2, 0);

      nr1 = 0, nr2 = 0, nr3 = 0, nr4 = 0;
      randomize_map_task4(v1, n, & nr1, & nr2, & nr3, & nr4);
      compunere_matrice(v1, n);
      random_map(v1, n, nr1, nr2, nr3, nr4);
      refresh();
      break;
    case KEY_F(3):
      // in cazul in care se doreste intoarcerea in meniu"
      meniu_intoarcere = 1;
      break;
    case 10:
      if (( * v1)[highlight_i][highlight_j] == 'X')
        ( * v1)[highlight_i][highlight_j] = '#';
      else
      if (( * v1)[highlight_i][highlight_j] != '#' && ( * v1)[highlight_i][highlight_j] != '-')
        ( * v1)[highlight_i][highlight_j] = '-';

      break;

    default:
      break;
    }

    print_table(menu_win, highlight_i, highlight_j, n, v1);

    if (( * v1)[highlight_i][highlight_j] == '-' && ( * parcurgere)[highlight_i][highlight_j] == 0) {
      ( * parcurgere)[highlight_i][highlight_j] = 1;
      computer_round(menu_win, n, v2);

    }

    //se calculeaza sccorul pentru a se observa o posibila victorie din partea cuiva
    score(v1, n, & nr_nave_lovp1);
    * nr_nave_lovite1 = * nr_nave_lovite1 + nr_nave_lovp1;
    score(v2, n, & nr_nave_lovp2);
    * nr_nave_lovite2 = * nr_nave_lovite2 + nr_nave_lovp2;
    if ( * nr_nave_lovite1 == 10 || * nr_nave_lovite2 == 10) break;
    else {
      * nr_nave_lovite1 = * nr_nave_lovite1 - nr_nave_lovp1;
      * nr_nave_lovite2 = * nr_nave_lovite2 - nr_nave_lovp2;
    }
    if (meniu_intoarcere == 1) break;

    refresh();

  }

}
// functie care arata scorul final al jucatorilor
// aceasta este disponibila chiar cand se afla jucatorul in meniu
//  nu este valabila cand se deschide prima oara jocul

void score_meniu(WINDOW * menu_win, int nr_nave_lovite1, int nr_nave_lovite2, int * resume_enter) {
  int startx = (80 - latime_joc) / 2;
  int starty = (24 - inaltime_joc) / 2;
  int c;
  int flag = 1;
  menu_win = newwin(0, 0, 0, 0);
  keypad(menu_win, TRUE);
  menu_win = newwin(inaltime_joc, latime_joc, starty, startx);
  refresh();
  box(menu_win, 0, 0);
  if (nr_nave_lovite1 == 10) {
    * resume_enter = 0;
    mvwprintw(menu_win, 16, 3, "Pentru a intra in meniu folositi tasta F1 ");
    while (flag) {
      mvwprintw(menu_win, 2, 8, "Ai doborat toate navele!!! Felicitari!! ");
      mvwprintw(menu_win, 3, 8, "Computerul a doborat %d nave", nr_nave_lovite2);
      wrefresh(menu_win);
      c = wgetch(menu_win);
      if (c == 80) flag = 0;
      wrefresh(menu_win);
    }

  }
  if (nr_nave_lovite2 == 10) {
    * resume_enter = 0;
    mvwprintw(menu_win, 16, 3, "Pentru a intra in meniu folositi tasta F1 ");
    while (flag) {
      mvwprintw(menu_win, 2, 8, "Computerul a castigat!!!");
      mvwprintw(menu_win, 3, 8, "Felicitari!! Ai doborat %d nave", nr_nave_lovite1);
      wrefresh(menu_win);
      c = wgetch(menu_win);
      if (c == 80) flag = 0;
      wrefresh(menu_win);
    }
  }
  wrefresh(menu_win);
  refresh();
}

// aceasta functie este cu rolul de pune in vector valoriile din fisier ales random
void compunere_you(WINDOW * menu_win, char ** * v, int n, char ** argv, int argc, int * ok) {
  FILE * f;
  int i, j;
  char c;
  int startx, starty;
  int alegere = rand() % (argc - 1) + 1;
  f = fopen(argv[alegere], "r");
  // se verifica daca fisierul se paote deschide
  if (!f) {
    //daca nu se poate deschide, se redeschide un nou box si se afiseaza mesajul cerut
    menu_win = newwin(0, 0, 0, 0);
    refresh();
    startx = (80 - latime_joc) / 2;
    starty = (24 - inaltime_joc) / 2;
    menu_win = newwin(inaltime_joc, latime_joc, starty, startx);
    box(menu_win, 0, 0);
    wrefresh(menu_win);
    * ok = 1;
    mvwprintw(menu_win, 5, 11, "Fisierul %s nu poate fi deschis ", argv[alegere]);
  }
  wrefresh(menu_win);

  // in cazul in care fisierul are valori se completeaza matricea cu elementele fisierului
  if ( * ok == 0)
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++) {
        fscanf(f, "%c", & c);
        ( * v)[i][j] = c;
      }

  fclose(f);
}

int main(int argc, char ** argv) {
  //vector cu rolul de afisa argumentele primului meniu
  char * vector_menu1[] = {
    "Start game",
    "Resume",
    "Score",
    "Exit",
  };
  //vector cu rolul de afisa argumentele celui de-al doilea meniu
  char * vector_menu2[] = {
    "Mapa random",
    "Mapa aleasa",
  };
  int tasta_aleasa = 0;
  int ok;
  int nr_nave_lovite1 = 0;
  int nr_nave_lovite2 = 0;
  int resume_enter, tasta_aleasa_alta;
  int ** parcurgere;
  int startx = (80 - latime_menu) / 2;
  int starty = (24 - inaltime_menu) / 2;
  char ** table_computer;
  char ** table_you;
  int n, nr1 = 4, nr2 = 3, nr3 = 2, nr4 = 1;
  WINDOW * menu_win;

  // se verifica daca are argumente functia
  if (argc == 1) {
    fprintf(stderr, "Nu s-au dat argumente de comanda");
    return 1;
  }
  srand(time(NULL));
  n = 10;
  // se aloca dinamic matricele corespunzatoare tablelor de joc
  alocare_matrice( & table_computer, n);
  alocare_matrice( & table_you, n);

  //functii cu rolul de a intra in modul ncurses
  initscr();
  clear();
  noecho();
  cbreak();

  // se aloca dinamic vectorul necesar pentru joc 
  alocare_matrice_parcurgere( & parcurgere, n);
  curs_set(0);

  // structura repetitiva care marcheaza desfasurarea jocului prin succesiunea 
  // de meniuri si harti
  while (1) {
    //se fixeaza dimensiunile ferestrei de meniu
    ok = 0;
    clear();
    menu_win = newwin(0, 0, 0, 0);
    refresh();
    startx = (80 - latime_menu) / 2;
    starty = (24 - inaltime_menu) / 2;
    menu_win = newwin(inaltime_menu, latime_menu, starty, startx);
    // se da un refresh pentru a actualiza modificarile facute
    wrefresh(menu_win);

    // functia menu de a genera un menu in functie de vectorulul ales
    menu(menu_win, & tasta_aleasa, 4, vector_menu1);
    refresh();

    // in cazul in care s-a selectat modul "New Game"
    if (tasta_aleasa == 1) {
      menu_win = newwin(0, 0, 0, 0);
      refresh();
      menu_win = newwin(inaltime_menu, latime_menu, starty, startx);
      // se intra in cel de-al doilea meniu
      menu(menu_win, & tasta_aleasa_alta, 2, vector_menu2);
      refresh();
      // se intra in prima conditie daca s-a selectat "Mapa random"
      if (tasta_aleasa_alta == 1) {
        nr_nave_lovite1 = 0;
        nr_nave_lovite2 = 0;
        resume_enter = 1;
        nr1 = 4, nr2 = 3, nr3 = 2, nr4 = 1;
        compunere_matrice( & table_computer, n);
        random_map( & table_computer, n, nr1, nr2, nr3, nr4);

        compunere_matrice( & table_you, n);
        random_map( & table_you, n, nr1, nr2, nr3, nr4);

        menu_win = newwin(0, 0, 0, 0);
        refresh();
        startx = (80 - latime_joc) / 2;
        starty = (24 - inaltime_joc) / 2;
        zero( & parcurgere, 10);
        menu_win = newwin(inaltime_joc, latime_joc, starty, startx);
        battleship(menu_win, n, & table_computer, & table_you, & nr_nave_lovite1, & nr_nave_lovite2, & parcurgere);
        refresh();
        score_meniu(menu_win, nr_nave_lovite1, nr_nave_lovite2, & resume_enter);
      }
      // se intra in prima conditie daca s-a selectat "Mapa aleasa"
      if (tasta_aleasa_alta == 2) {
        nr_nave_lovite1 = 0;
        nr_nave_lovite2 = 0;
        resume_enter = 1;
        nr1 = 4, nr2 = 3, nr3 = 2, nr4 = 1;
        compunere_matrice( & table_computer, n);
        random_map( & table_computer, n, nr1, nr2, nr3, nr4);

        compunere_you(menu_win, & table_you, n, argv, argc, & ok);
        if (ok == 1) return 1;

        menu_win = newwin(0, 0, 0, 0);
        refresh();
        startx = (80 - latime_joc) / 2;
        starty = (24 - inaltime_joc) / 2;
        zero( & parcurgere, 10);
        menu_win = newwin(inaltime_joc, latime_joc, starty, startx);
        battleship(menu_win, n, & table_computer, & table_you, & nr_nave_lovite1, & nr_nave_lovite2, & parcurgere);
        refresh();
        score_meniu(menu_win, nr_nave_lovite1, nr_nave_lovite2, & resume_enter);
      }
    }
    // in cazul in care s-a selectat modul "Resume"
    // variabile resume_enter are rolul de a bloca butonul"Resume"
    // in cazul nu exista niciun joc inceput
    if (tasta_aleasa == 2 && resume_enter == 1) {

      menu_win = newwin(0, 0, 0, 0);
      refresh();
      startx = (80 - latime_joc) / 2;
      starty = (24 - inaltime_joc) / 2;
      menu_win = newwin(inaltime_joc, latime_joc, starty, startx);
      battleship(menu_win, n, & table_computer, & table_you, & nr_nave_lovite1, & nr_nave_lovite2, & parcurgere);
      refresh();
      score_meniu(menu_win, nr_nave_lovite1, nr_nave_lovite2, & resume_enter);
    }
    // in cazul in care s-a selectat modul "Score"
    if (tasta_aleasa == 3) {
      menu_win = newwin(0, 0, 0, 0);
      menu_win = newwin(inaltime_joc, latime_joc, starty, startx);
      refresh();
      score_meniu(menu_win, nr_nave_lovite1, nr_nave_lovite2, & resume_enter);
      refresh();
    }
    // in cazul in care s-a selectat modul "Exit"
    if (tasta_aleasa == 4) break;
    tasta_aleasa = 0;

  }

  //functii cu rolul de eliberare a memoriei pentru ferestrele deschide si a continutului afisat
  getch();
  clrtoeol();
  refresh();
  endwin();

  // se elibereaza memoria alocata pentru vectori
  eliberare(table_computer, n);
  eliberare(table_you, n);
  eliberare_parcurgere(parcurgere, n);
  return 0;
}