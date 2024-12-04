#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

void print(uint32_t** laberint, int n, int m,
  int hi, int hj, int mi, int mj)
{
  if (laberint == nullptr) {
    printf("Labirint is empty\n");
    return;
  }
  printf("Laberint size: (%d, %d) \n", n, m);
  printf("Hero:  (%d, %d) \n", hi, hj);
  printf("Money: (%d, %d) \n", mi, mj);

  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < m; j++)
    {
      printf("%4u", laberint[i][j]);
    }
    printf("\n");
  }

}

// -------------------------------------------------------------------------------------
// reworked alloc_lab
void alloc_matrix(uint32_t**& matrix, int n, int m)
{
  matrix = (uint32_t**)malloc(sizeof(uint32_t*) * n);
  matrix[0] = (uint32_t*)malloc(sizeof(uint32_t) * n * m);
  for (size_t i = 1; i < n; i++)
  {
    matrix[i] = matrix[i - 1] + m;
  }
}
// -------------------------------------------------------------------------------------

void read(uint32_t**& laberint, int& n, int& m,
  int& hi, int& hj, int& mi, int& mj)
{
  FILE* lab_f = nullptr;

  if (lab_f = fopen("lab.txt", "r"))
  {
    fscanf(lab_f, "%d", &n);
    fscanf(lab_f, "%d", &m);
    alloc_matrix(laberint, n, m);
    char* str = (char*)malloc(sizeof(char) * (m + 3));
    for (size_t i = 0; i < n; i++)
    {
      fscanf(lab_f, "%s", str);
      for (size_t j = 0; j < m; j++)
      {
        laberint[i][j] = 333;

        if (str[j] == '0') laberint[i][j] = (n - 2) * (m - 2);
        if (str[j] == '*') {
          laberint[i][j] = 0;
          hi = i;
          hj = j;
        }
        if (str[j] == '&') {
          laberint[i][j] = (n - 2) * (m - 2);
          mi = i;
          mj = j;
        }
      }
    }
    free(str);
  }

}

void len_path(uint32_t** laberint, int ci, int cj, int cur_len)
{
  uint32_t& up = laberint[ci - 1][cj];
  uint32_t& down = laberint[ci + 1][cj];
  uint32_t& lf = laberint[ci][cj - 1];
  uint32_t& rg = laberint[ci][cj + 1];

  if ((up != 333) && (up > cur_len + 1))
  {
    up = cur_len + 1;
    len_path(laberint, ci - 1, cj, cur_len + 1);
  }

  if ((down != 333) && (down > cur_len + 1))
  {
    down = cur_len + 1;
    len_path(laberint, ci + 1, cj, cur_len + 1);
  }
  
  if ((lf != 333) && (lf > cur_len + 1))
  {
    lf = cur_len + 1;
    len_path(laberint, ci , cj - 1, cur_len + 1);
  }

  if ((rg != 333) && (rg > cur_len + 1))
  {
    rg = cur_len + 1;
    len_path(laberint, ci, cj + 1, cur_len + 1);
  }
}

// -------------------------------------------------------------------------------------
// directly hometask
void rec_path(uint32_t** laberint, int ci, int cj, uint32_t** track, int step) 
{
    uint32_t up = laberint[ci - 1][cj];
    uint32_t down = laberint[ci + 1][cj];
    uint32_t left = laberint[ci][cj - 1];
    uint32_t right = laberint[ci][cj + 1];

    if ((up != 333) && (up < laberint[ci][cj]))
    {
        track[step][0] = (uint32_t)(ci - 1);
        track[step][1] = (uint32_t)cj;
        step++; 
        rec_path(laberint, ci - 1, cj, track, step);
    }
    if ((down != 333) && (down < laberint[ci][cj]))
    {
        track[step][0] = (uint32_t)(ci + 1);
        track[step][1] = (uint32_t)cj;
        step++; 
        rec_path(laberint, ci + 1, cj, track, step);
    }
    if ((left != 333) && (left < laberint[ci][cj]))
    {
        track[step][0] = (uint32_t)ci;
        track[step][1] = (uint32_t)(cj - 1);
        step++;
        rec_path(laberint, ci, cj - 1, track, step);
    }
    if ((right != 333) && (right < laberint[ci][cj]))
    {
        track[step][0] = (uint32_t)ci;
        track[step][1] = (uint32_t)(cj + 1);
        step++; 
        rec_path(laberint, ci, cj + 1, track, step);
    }
}
// -------------------------------------------------------------------------------------

int main() 
{
    uint32_t** laberint = nullptr;
    uint32_t** track = nullptr;
    int n, m, hi, hj, mi, mj, temp;
    read(laberint, n, m, hi, hj, mi, mj);
    print(laberint, n, m, hi, hj, mi, mj);

    len_path(laberint, hi, hj, 0);
    print(laberint, n, m, hi, hj, mi, mj);

    alloc_matrix(track, laberint[mi][mj] + 1, 2);
    track[0][0] = (uint32_t)mi;
    track[0][1] = (uint32_t)mj;
    rec_path(laberint, mi, mj, track, 1);
    
    for (int i = 0;i < laberint[mi][mj] + 1;i++)
    {
        printf("(%u,%u) ", track[15 - i][0], track[15 - i][1]);
    }

    free(track[0]);
    free(track);
    free(laberint[0]);
    free(laberint);

    return 0;
}

