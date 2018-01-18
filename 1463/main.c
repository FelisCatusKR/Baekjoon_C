#include <stdio.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int MakeToOne(int N);
int smallest(int A, int B, int C)
{
    return MIN(MIN(A, B), C);
}

int main(void)
{
    int N;
    scanf("%d", &N);
    printf("%d\n", MakeToOne(N));

    return 0;
}

int MakeToOne(int N)
{
    int makeToOne[1000001] = {0, 0, 1};
    for (int i = 3; i <= N; i++)
    {
        if (i % 6 == 0)
            makeToOne[i] = smallest(makeToOne[i / 3], makeToOne[i / 2], makeToOne[i - 1]) + 1;
        else if (i % 3 == 0)
            makeToOne[i] = MIN(makeToOne[i / 3], makeToOne[i - 1]) + 1;
        else if (i % 2 == 0)
            makeToOne[i] = MIN(makeToOne[i / 2], makeToOne[i - 1]) + 1;
        else
            makeToOne[i] = makeToOne[i - 1] + 1;
    }
    return makeToOne[N];
}
