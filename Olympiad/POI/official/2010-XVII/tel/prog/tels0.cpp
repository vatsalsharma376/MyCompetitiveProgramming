/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 tels0.cpp                                     *
 *   Autor:                Łukasz Bieniasz-Krzywiec                      *
 *   Opis:                 Rozwiazanie powolne - algorytm brutalny.      *
 *   Zlozonosc czasowa:    O(n^2 * 2^(n^2))                              *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************/

#include <cstdlib>
#include <cstdio>

#include <vector>

using namespace std;

/*
 * DEKLARACJE STAŁYCH
 */

#define MAXN 40000
#define MAXM 1000000

#define INF MAXN


/*
 * DEKLARACJE TYPÓW:
 */

typedef vector<int>   VI;
typedef vector<bool>  VB;
typedef vector<VB >   VVB;


/*
 * DEKLARACJE ZMIENNYCH GLOBALNYCH:
 */

int n, m, w;  /* liczba wierzchołków, liczba krawędzi, wynik */
VVB g;        /* graf w postaci macierzy sąsiedztwa */
VI  d;        /* tablica pomocnicza */


/*
 * DEKLARACJE PODPROGRAMÓW:
 */

/* Funkcja dodaje do grafu krawędź {a,b}. */
void inline dodajKrawedz(int a, int b) {
  g[a][b] = true;
  g[b][a] = true;
}

/* Funkcja wczytuje dane. */
void wczytajDane() {
  int a, b, i, j;

  scanf("%d%d", &n, &m);

  g.reserve(n);
  for (i = 0; i < n; ++i) {
    g[i].reserve(n);
    for (j = 0; j < n; ++j) {
      g[i][j] = false;
    }
  }

  for (i = 0; i < m; ++i) {
    scanf("%d%d", &a, &b);
    dodajKrawedz(a - 1, b - 1);
  }
}

/* Przeszukiwanie wszerz. */
void bfs(int v) {
  int i, u, w;
  VI  q;

  for (i = 0; i < n; ++i) {
    d[i] = INF;
  }

  d[v] = 0; q.push_back(v);
  for (i = 0; i < (int)q.size(); ++i) {
    u = q[i];
    for (w = 0; w < n; ++w) {
      if (g[u][w] && d[w] == INF) {
        d[w] = d[u] + 1;
        if (d[w] < 4) {
          q.push_back(w);
        }
      }
    }
  }
}

/* Funkcja generuje wszystkie możliwe grafy. */
void dfs(int i, int j, int k) {
  if (i == n) {
    bfs(0);
    if (d[1] >= 5 && k > w) {
      w = k;
    }
  } else {
    int ni, nj;
    if (j == n) {
      ni = i + 1; nj = ni + 1;
    } else {
      ni = i; nj = j + 1;
    }
    dfs(ni, nj, k);
    if (j < n && !g[i][j]) {
      g[i][j] = g[j][i] = true;
      dfs(ni, nj, k + 1);
      g[i][j] = g[j][i] = false;
    }
  }
}

/* 
 * Funkcja oblicza moc maksymalnego rozszerzenia grafu.
 */
void obliczWynik() {
  d.reserve(n);
  w = 0;
  dfs(0, 1, 0);
}

/* Funkcja wypisuje wynik. */
void wypiszWynik() {
  printf("%d\n", w);
}


/*
 * PROGRAM GŁÓWNY:
 */

int main() {
  wczytajDane();
  obliczWynik();
  wypiszWynik();

  return 0;
}

