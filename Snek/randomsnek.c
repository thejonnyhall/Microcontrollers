//
//  randomsnek.c
//  
//
//  Created by Jonny Hall on 13/10/2016.
//
//

#include "randomsnek.h"


int flashCounter = -1;
numbool gameOver = 0;
numbool wallsOn = 0;
struct Hitbox statBox = {0, 0, 15, 17};
struct Hitbox wall1 = {36, 0, 36, 22};
struct Hitbox wall2 = {51, 17, 83, 17};
struct Hitbox wall3 = {0, 36, 35, 36};

void drawBodyParts() {
    struct BodyPart *cur = &head;
    while (cur != NULL) {
        for (int x = cur->x; x < cur->x+3; x++) {
            for (int y = cur->y; y < cur->y+3; y++) {
                set_pixel(x, y, 0xFF);
            }
        }
        if (cur == &head) {
            if (direction == DOWN) {
                set_pixel(cur->x, cur->y+2, 0);
                set_pixel(cur->x+2, cur->y+2, 0);
            } else if (direction == UP) {
                set_pixel(cur->x, cur->y, 0);
                set_pixel(cur->x+2, cur->y, 0);
            } else if (direction == LEFT || direction == NONE) {
                set_pixel(cur->x, cur->y, 0);
                set_pixel(cur->x, cur->y+2, 0);
            } else if (direction == RIGHT) {
                set_pixel(cur->x+2, cur->y, 0);
                set_pixel(cur->x+2, cur->y+2, 0);
            }
            
        }
        cur = cur->next;
    }
}

void drawFruit() {
    int n = ((flashCounter = (flashCounter + 1) % 8) < 4) ? 1 : 0;
    for (; n < 9; n = n + 2) {
        set_pixel(fruit.x + (n % 3), fruit.y + (n / 3), 0xFF);
    }
}

void drawStats() {
    char str[3] = "   ";
    draw_string(0, 0, itoa(score, str, 10));
    draw_char(0, 9, 'L');
    draw_string(5, 9, itoa(lives, str, 10));
}

void drawWalls() {
    draw_line(wall1.x1, wall1.y1, wall1.x2, wall1.y2);
    draw_line(wall2.x1, wall2.y1, wall2.x2, wall2.y2);
    draw_line(wall3.x1, wall3.y1, wall3.x2, wall3.y2);
}

void initGame(numbool reset) {
    
    if (!reset) {
        //chop snek to just head :'(
        //deallocate memory
        struct BodyPart *cur = head.next;
        while (cur != NULL) {
            struct BodyPart *temp = cur->next;
            free(cur);
            cur = temp;
        }
        
    } else {
        lives = 5;
        score = 0;
    }
    
    direction = NONE;
    growSnake = 0;
    head.x = 18;
    head.y = 18;
    head.next = NULL;
    addSnek(head.x+3, head.y, &head);
    moveFruit();
    
    resetButtons();
}

void addSnek(int x, int y, struct BodyPart* tail) {
    struct BodyPart *new = malloc(sizeof(struct BodyPart));
    tail->next = new;
    new->x = x;
    new->y = y;
    new->next = NULL; //important to avoid inf loop
}

void drawGame() {
    if (gameOver) {
        draw_string(0, 0, "GAME OVER");
    } else {
        drawStats();
        drawBodyParts();
        drawFruit();
        if (wallsOn) drawWalls();
    }
}

void stepGame() {
    if (!gameOver) {
        if (checkCollision(get3Hitbox(head.x, head.y), get3Hitbox(fruit.x, fruit.y))) {
            moveFruit();
            score++;
            if (wallsOn) score++;
            growSnake = 1;
        }
        
        struct Hitbox headBox = get3Hitbox(head.x, head.y);
        if (wallsOn && (checkCollision(headBox, wall1) || checkCollision(headBox, wall2) || checkCollision(headBox, wall3))) {
            dockLife();
        }
        
        moveSnake();
    }
}

void moveSnake() {
    if (direction == NONE) return;
    int dx = 0;
    int dy = 0;
    if (direction == LEFT) dx = -3;
    else if (direction == RIGHT) dx = 3;
    else if (direction == UP) dy = -3;
    else if (direction == DOWN) dy = 3;
    
    
    struct BodyPart *cur = &head;
    struct BodyPart *last = NULL;
    
    int newX = cur->x + dx;
    int newY = cur->y + dy;
    
    //wraparaound
    if (newX < 0) newX = newX + LCD_X;
    else newX = newX % LCD_X;
    if (newY < 0) newY = newY + LCD_Y;
    else newY = newY % LCD_Y;
    
    //自殺
    
    if (snekCollision(get3Hitbox(newX, newY), 1)) {
        dockLife();
        return;
    }
    
    while (cur != NULL) {
        last = cur;
        
        int oldX = cur->x;
        int oldY = cur->y;
        
        cur->x = newX;
        cur->y = newY;
        
        newX = oldX;
        newY = oldY;
        
        cur = cur->next;
    }
    
    if (growSnake) {
        addSnek(newX, newY, last);
        growSnake = 0;
    }
}



void handleButton(uint8_t buttonState) {
    if (HATU) direction = UP;
    else if (HATD) direction = DOWN;
    else if (HATL) direction = LEFT;
    else if (HATR) direction = RIGHT;
    
    if (BUTR && BUTL && gameOver) {
        gameOver = 0;
        initGame(1);
    } else if (BUTR) {
        wallsOn = 1;
    } else if (BUTL) {
        wallsOn = 0;
    }
    resetButtons();
}

void moveFruit() {
    numbool done = 0;
    int x = -1;
    int y = -1;
    while (!done) {
        x = (rand() / (float)RAND_MAX) * LCD_X;
        y = (rand() / (float)RAND_MAX) * LCD_Y;
        struct Hitbox fruitBox = get3Hitbox(x, y);
        if (!snekCollision(fruitBox, 0) && !checkCollision(fruitBox, statBox) && 
            !checkCollision(fruitBox, wall1) && !checkCollision(fruitBox, wall2) &&
            !checkCollision(fruitBox, wall3)) {
            
            done = 1;
        }
    }
    fruit.x = x;
    fruit.y = y;
}

void dockLife() {
    flashDisplay();
    if (--lives < 0) gameOver = 1;
    else initGame(0);
}

numbool snekCollision(struct Hitbox a, numbool noHead) {
    struct BodyPart *cur = noHead ? head.next : &head;
    while (cur != NULL) {
        if (checkCollision(get3Hitbox(cur->x, cur->y), a)) return 1;
        cur = cur->next;
    }
    return 0;
}

numbool checkCollision(struct Hitbox a, struct Hitbox b) {
    return (a.x1 <= b.x2 && a.x2 >= b.x1 && a.y1 <= b.y2 && a.y2 >= b.y1);
}

struct Hitbox get3Hitbox(int x, int y) {
    return ((struct Hitbox) {x, y, x+2, y+2});
}