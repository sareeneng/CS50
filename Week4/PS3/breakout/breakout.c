//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5
#define BRICK_HEIGHT 10
#define BRICK_HEIGHT_BUFFER 50

// number of columns of bricks
#define COLS 10

//space between bricks
#define BRICK_X_BUFFER 5
#define BRICK_Y_BUFFER 5

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//Pause between moving the ball
#define PAUSE 10

//Speed multiplier to multiply by drand48 to get velocity
#define SPEED_MULTIPLIER 3

//  paddle characteristics
#define PADDLE_WIDTH RADIUS*6
#define PADDLE_HEIGHT 10
#define PADDLE_BUFFER 30

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double x_velocity = drand48()*SPEED_MULTIPLIER+1;
    double y_velocity = drand48()*SPEED_MULTIPLIER*2+1;
    
    bool readyToPlay=false;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent eventWhilePaused = getNextEvent(MOUSE_EVENT);
        
        if(eventWhilePaused!=NULL)
            if(getEventType(eventWhilePaused)==MOUSE_CLICKED)
                readyToPlay=true;
        
        while(readyToPlay)
        {
            //Code to make ball move around
            move(ball,x_velocity,y_velocity);
            pause(PAUSE);
            
            GObject objectHit = detectCollision(window,ball);
            if(objectHit!=NULL)
                if(strcmp(getType(objectHit),"GRect")==0)
                {
                    y_velocity = -y_velocity;
                    if(objectHit != paddle)
                        removeGWindow(window, objectHit);
                    else
                        x_velocity = (getX(ball)+RADIUS/2-(getX(paddle)+PADDLE_WIDTH/2))/(PADDLE_WIDTH/4);
                }
                
            if ( (getX(ball)+getWidth(ball)>=getWidth(window)) || (getX(ball)<=0))
                x_velocity = -x_velocity;
            
            if ( getY(ball)<=0)
                y_velocity = -y_velocity;
            else if(getY(ball)>HEIGHT)
            {
                lives--;
                removeGWindow(window,ball);
                ball = initBall(window);
                x_velocity = drand48()*SPEED_MULTIPLIER+1;
                y_velocity = drand48()*SPEED_MULTIPLIER*2+1;
                readyToPlay=false;
            }
            
            // check for mouse event
            GEvent event = getNextEvent(MOUSE_EVENT);

            // if we heard one
            if (event != NULL)
            {
                // if the event was movement
                if (getEventType(event) == MOUSE_MOVED)
                {
                    // ensure paddle follows cursor only in Y direction
                    double x = getX(event)-PADDLE_WIDTH/2;
                   // printf("%0.f %0.f\n", getX(event),getY(event));
                    if(x>0 && x+PADDLE_WIDTH<WIDTH)
                        setLocation(paddle, x, HEIGHT-PADDLE_BUFFER);
                }
                
            }
        
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    //determine dimension of each brick
    
    int width = WIDTH/COLS-BRICK_X_BUFFER;    //30
    int height = BRICK_HEIGHT;              //30
    
    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLS; j++)
        {
            int x = j*width-BRICK_X_BUFFER/2+BRICK_X_BUFFER*(j+1);
            int y = BRICK_HEIGHT_BUFFER+i*height + BRICK_Y_BUFFER*(i+1);
            GRect brick = newGRect(x,y,width,height);
            setFilled(brick,true);
            string color;
            switch(i)
            {
                case 0:color="BLACK";break;
                case 1:color="RED";break;
                case 2:color="YELLOW";break;
                case 3:color="GREEN";break;
                case 4:color="BLUE";break;
                default:color="ORANGE";
            }
            setColor(brick,color);
            add(window,brick);
        }   
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2-RADIUS,HEIGHT/2-RADIUS,RADIUS*2, RADIUS*2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int xcoord = WIDTH/2-PADDLE_WIDTH/2;
    int ycoord = HEIGHT-PADDLE_BUFFER;
    GRect paddle = newGRect(xcoord,ycoord,PADDLE_WIDTH,PADDLE_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
