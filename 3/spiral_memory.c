#include <stdio.h>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct
{
    int x;
    int y;
} Point;

typedef struct
{
    int steps;
    Direction dir;
} Command;

void print_command(Command *cmd)
{
    char *direction;
    switch (cmd->dir)
    {
    case UP:
        direction = "up";
        break;
    case DOWN:
        direction = "down";
        break;
    case LEFT:
        direction = "left";
        break;
    case RIGHT:
        direction = "right";
        break;
    }
    printf("Go %s %d steps.\n", direction, cmd->steps);
}

Command *get_commands(int iteration)
{
    int iter_steps = iteration * 2;
    Command *cmds = malloc(sizeof(Command) * 5);
    Command go_right = {1, RIGHT};
    Command go_up = {1 + iter_steps, UP};
    Command go_left = {2 + iter_steps, LEFT};
    Command go_down = {2 + iter_steps, DOWN};
    Command go_right_again = {2 + iter_steps, RIGHT};
    cmds[0] = go_right;
    cmds[1] = go_up;
    cmds[2] = go_left;
    cmds[3] = go_down;
    cmds[4] = go_right_again;
    return cmds;
}

int get_command_steps(const Command *cmds)
{
    int steps = 0;
    steps += cmds[0].steps;
    steps += cmds[1].steps;
    steps += cmds[2].steps;
    steps += cmds[3].steps;
    steps += cmds[4].steps;
    return steps;
}

void update_point(Point *point, Direction dir)
{
    switch (dir)
    {
    case UP:
        point->y++;
        break;
    case DOWN:
        point->y--;
        break;
    case LEFT:
        point->x--;
        break;
    case RIGHT:
        point->x++;
        break;
    }
}

int get_steps(int input)
{
    int i;
    Point point;
    point.x = 0;
    point.y = 0;
    int spiral_steps_taken = 1;
    int count = get_command_steps(get_commands(0));
    int iter = 1;
    while (count <= input)
    {
        count += get_command_steps(get_commands(iter++));
    }

    int total_commands = iter * 5;
    Command *commands = malloc(sizeof(Command) * total_commands);

    for (i = 0; i < iter; ++i)
    {
        Command *command_iter = get_commands(i);
        commands[0 + (i * 5)] = command_iter[0];
        commands[1 + (i * 5)] = command_iter[1];
        commands[2 + (i * 5)] = command_iter[2];
        commands[3 + (i * 5)] = command_iter[3];
        commands[4 + (i * 5)] = command_iter[4];
    }

    i = 0;
    int j;
    while (spiral_steps_taken < input)
    {
        Command cmd = commands[i];
        for (j = 0; j < cmd.steps; ++j)
        {
            if (spiral_steps_taken == input)
            {
                break;
            }
            update_point(&point, cmd.dir);
            spiral_steps_taken++;
        }
        i++;
    }
    return abs(point.x) + abs(point.y);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Please give one number as input");
        return 1;
    }

    int input_val = atol(argv[1]);
    if (!input_val)
    {
        printf("Input must be a number");
        return 1;
    }
    int steps = get_steps(input_val);
    printf("%d", steps);
    return 0;
}