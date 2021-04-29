#include "get_next_line.h"

int get_next_line(char **line)
{
    int i = 0;
    int ret;
    char c;
    char buf[99999];

    while (1)
    {
        if ((ret = read(0, &c, 1)) < 0)
            return (-1);
        if (ret == 0 || c == '\n')
        {
            buf[i] = 0;
            *line = malloc(sizeof(char) * (i + 1));
            (*line)[i] = 0;
            while (--i >= 0)
                (*line)[i] = buf[i];
            return ((ret == 0) ? 0 : 1);
        }
        buf[i++] = c;
    }
    return (0);
}

int main()
{
    char *line;
    int i = 0;

    while ((i = get_next_line(&line)))
    {
        printf("%s\n", line);
        free(line);
    }
    printf("%s", line);
    free(line);
    return (0);
}
