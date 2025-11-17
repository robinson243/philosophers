#include "philo.h"

int main(int argc, char **argv)
{
    t_args args;

    if (parse_args(argc, argv, &args) == 1)
        return (1);
    return (0);
}
