#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    int t;

    if (argc == 3)
    {
        i = -1;
        while (argv[1][++i])
        {
            t = 0;
            j = -1;
            while (i > ++j && t == 0)
                if (argv[1][i] == argv[1][j])
                    t = 1;
            j = -1;
            while (argv[2][++j] && t == 0)
                if (argv[1][i] == argv[2][j])
                {               
                    write(1, &argv[1][i], 1);
                    break;
                }
        }
    }
    write(1, "\n", 1);

    return (0);
}