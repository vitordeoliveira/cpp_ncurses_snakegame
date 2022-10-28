#include "snake.hpp"

Snake::Snake(){};
Snake::Snake(int y, int x, char headChar, char bodyChar)
{
    m_bodyChar = bodyChar;
    m_headChar = headChar;
    m_head = (Point){y, x};
    for (size_t i = 0; i < 5; i++)
    {
        m_body.push_back((Point){y, x + i});
    }

    m_tail = m_body[m_body.size() - 1];
};

SnakeGame::SnakeGame()
{
    initscr();
    srand(time(NULL));
    nodelay(stdscr, true); // The getch not wait until the user press a key
    keypad(stdscr, true);  // To use keyup keydown and etc...
    noecho();
    curs_set(0);
    delay = 100000;
    direction = 'l';
    points = 0;

    getmaxyx(stdscr, maxheight, maxwidth);
    int borderGameY = maxheight - (maxheight * 0.1);
    int borderScoreY = maxheight * 0.11;

    game = newwin(borderGameY, maxwidth, 0, 0);
    scoreboard = newwin(borderScoreY, maxwidth, maxheight * 0.9, 0);

    getmaxyx(game, game_max_y, game_max_x);

    refresh();

    box(game, 0, 0);
    box(scoreboard, 0, 0);

    m_snake = Snake(game_max_y / 2, game_max_x / 2, '@', 'o');

    for (size_t i = 0; i < m_snake.m_body.size(); i++)
    {
        mvwaddch(game, m_snake.m_body[0].y, m_snake.m_body[0].x + i, m_snake.m_bodyChar);
    }

    mvwaddch(game, m_snake.m_head.y, m_snake.m_head.x, m_snake.m_headChar);

    createFood();

    updateSnakePosition();

    mvwprintw(scoreboard, 5, 5, "Direction: %c", direction);
    mvwprintw(scoreboard, 5, 20, "Points: %d", points);
    mvwprintw(scoreboard, 5, 80, "Doubled: %s", doubled ? "Get the point to doubled again" : "Double if U are not a pussy!!!");

    wrefresh(game);
    wrefresh(scoreboard);
    getch();
}

bool SnakeGame::collision()
{
    if (m_snake.m_head.x == game_max_x-1 || m_snake.m_head.y == game_max_y-1 || m_snake.m_head.x == 0 || m_snake.m_head.y == 0)
    {
        return true;
    }

    for (size_t i = 1; i < m_snake.m_body.size(); i++)
    {

        if (m_snake.m_head == m_snake.m_body[i])
        {
            return true;
        }
    }

    if (m_snake.m_head == food)
    {
        get = true;
        createFood();
        mvwprintw(scoreboard, 5, 20, "Points: %d", points += 100);
        wrefresh(scoreboard);
        delay -= 1000;
        doubled = false;
    }

    return false;
};

void SnakeGame::createFood()
{
    while (1)
    {
        int randX = rand() % game_max_x;
        int randY = rand() % game_max_y;

        mvwaddch(game, randY, randX, 'o');

        // if is inside the snake continue;
        if (randX == 0 || randY == 0 || randX == game_max_x - 1 || randY == game_max_y - 1)
        {
            continue;
        }

        food = (Point){randY, randX};
        // food.x = randX;
        // food.y = randY;
        wrefresh(game);
        break;
    }
}

void SnakeGame::updateSnakePosition()
{

    moveSnake();
    if (!get)
    {
        mvwaddch(game, m_snake.m_tail.y, m_snake.m_tail.x, ' ');
        m_snake.m_body.pop_back();
        m_snake.m_tail = m_snake.m_body[m_snake.m_body.size() - 1];
    }

    switch (direction)
    {
    case 'l':
        mvwaddch(game, m_snake.m_head.y, m_snake.m_head.x - 1, m_snake.m_headChar);
        mvwaddch(game, m_snake.m_head.y, m_snake.m_head.x, m_snake.m_bodyChar);
        m_snake.m_head.x = m_snake.m_head.x - 1;
        m_snake.m_body.insert(m_snake.m_body.begin(), (Point){m_snake.m_body[0].y, m_snake.m_body[0].x - 1});
        break;

    case 'r':
        mvwaddch(game, m_snake.m_head.y, m_snake.m_head.x + 1, m_snake.m_headChar);
        mvwaddch(game, m_snake.m_head.y, m_snake.m_head.x, m_snake.m_bodyChar);
        m_snake.m_head.x = m_snake.m_head.x + 1;
        m_snake.m_body.insert(m_snake.m_body.begin(), (Point){m_snake.m_body[0].y, m_snake.m_body[0].x + 1});
        break;

    case 'u':
        mvwaddch(game, m_snake.m_head.y - 1, m_snake.m_head.x, m_snake.m_headChar);
        mvwaddch(game, m_snake.m_head.y, m_snake.m_head.x, m_snake.m_bodyChar);
        m_snake.m_head.y = m_snake.m_head.y - 1;
        m_snake.m_body.insert(m_snake.m_body.begin(), (Point){m_snake.m_body[0].y - 1, m_snake.m_body[0].x});
        break;

    case 'd':
        mvwaddch(game, m_snake.m_head.y + 1, m_snake.m_head.x, m_snake.m_headChar);
        mvwaddch(game, m_snake.m_head.y, m_snake.m_head.x, m_snake.m_bodyChar);
        m_snake.m_head.y = m_snake.m_head.y + 1;
        m_snake.m_body.insert(m_snake.m_body.begin(), (Point){m_snake.m_body[0].y + 1, m_snake.m_body[0].x});
        break;

    case 'q':
        break;
    }

    wrefresh(game);
    get = false;
}

void SnakeGame::moveSnake()
{
    int tmp = getch();

    switch (tmp)
    {
    case KEY_LEFT:
        if (direction != 'r')
        {
            direction = 'l';
        }
        break;
    case KEY_UP:
        if (direction != 'd')
        {
            direction = 'u';
        }
        break;
    case KEY_DOWN:
        if (direction != 'u')
        {
            direction = 'd';
        }
        break;
    case KEY_RIGHT:
        if (direction != 'l')
        {
            direction = 'r';
        }
        break;
    case 'q':
        direction = 'q';
        break;

    case ' ':
        if (!doubled)
        {
            delay /= 2;
            points *= 2;
            doubled = true;
        }
        mvwprintw(scoreboard, 5, 50, "Doubled: %s", "BLOCKED");
        break;
    }

    mvwprintw(scoreboard, 5, 5, "Direction: %c", direction);
    mvwprintw(scoreboard, 5, 20, "Points: %d", points);
    mvwprintw(scoreboard, 5, 80, "Doubled: %s", doubled ? "Get the point to doubled again" : "Double if U are not a pussy!!!");

    wrefresh(scoreboard);
}

SnakeGame::~SnakeGame()
{
    nodelay(stdscr, false);
    getch();
    endwin();
}

void SnakeGame::start()
{
    while (true)
    {
        if (direction == 'q')
            break;

        if (collision())
        {
            mvwprintw(game, game_max_y / 2, game_max_x / 2 - 19, "GAME OVER CHAMPS!!");
            wrefresh(game);
            break;
        }

        updateSnakePosition();
        usleep(delay);
    }
}