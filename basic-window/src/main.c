/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_INPUT_CHARS     3
#define MAX_INPUT_GUESS     7

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    srand((unsigned)time(NULL));           // <<-- seed the RNG once
    int target_value = rand() % 101;       // 0..100

    InitWindow(screenWidth, screenHeight, "raylib example - guessing game");

    char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;
    int guessCount = 0;
    int guesses[] = {0,0,0,0,0,0,0};
    bool loss = false;
    bool win = false;

    Rectangle textBox = { screenWidth/2.0f - 20, 50, 75, 50 };
    Rectangle resetBox = { screenWidth/2.0f - 20, 400, 75, 50 };
    bool mouseOnText = false;
    bool mouseOnReset = false;

    int framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
            else mouseOnText = false;

            if (mouseOnText)
            {
                // Set the window's cursor to the I-Beam
                SetMouseCursor(MOUSE_CURSOR_IBEAM);

                // Get char pressed (unicode character) on the queue
                int key = GetCharPressed();

                // Check if more characters have been pressed on the same frame
                while (key > 0)
                {
                    // NOTE: Only allow keys in range [32..125]
                    if ((key >= '0') && (key <= '9') && (letterCount < MAX_INPUT_CHARS))
                    {
                        name[letterCount] = (char)key;
                        name[letterCount+1] = '\0'; // Add null terminator at the end of the string
                        letterCount++;
                    }

                    key = GetCharPressed();  // Check next character in the queue
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    name[letterCount] = '\0';
                }

                if (IsKeyPressed(KEY_ENTER))
                {
                    if ((letterCount > 0) && (guessCount < 7) && (atoi(name) <= 100))
                    {
                        guessCount++;
                        guesses[guessCount - 1] = atoi(name);
                    }
                    else if (guessCount >= MAX_INPUT_GUESS)
                    {
                        loss = true;
                    }
                }
            }
            else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if (mouseOnText) framesCounter++;
            else framesCounter = 0;
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

                ClearBackground(BLACK);

                DrawText("Guess a number (type and press enter):", 240, 20, 20, WHITE);

                DrawRectangleRec(textBox, LIGHTGRAY);
                if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE);
                else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

                DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, BLUE);

                DrawText(TextFormat("Guessed: %i/%i", guessCount, MAX_INPUT_GUESS), 315, 250, 20, DARKGRAY);

                if (mouseOnText)
                {
                    if (letterCount < MAX_INPUT_CHARS)
                    {
                        // Draw blinking underscore char
                        if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, BLUE);
                    }
                }

                DrawLine((100), (screenHeight/2), (screenWidth-100), (screenHeight/2), DARKGRAY);
                for (int i = 0; i < 7; i++)
                {
                    if (guesses[i] == 0) {break;}
                    if (guesses[i] < target_value) {
                        DrawCircle((100+(guesses[i]*6)), (screenHeight/2), 10, BLUE);
                    }
                    else if (guesses[i] > target_value) {
                        DrawCircle((100+(guesses[i]*6)), (screenHeight/2), 10, RED);
                    }
                    else {
                        DrawCircle((100+(guesses[i]*6)), (screenHeight/2), 10, YELLOW);
                        win = true;
                    }
                }
            
                if (loss) {
                    DrawText("You Lose!", 350, 300, 40, RED);
                    DrawText(TextFormat("The number was: %i", target_value), 325, 340, 20, WHITE);
                    if (CheckCollisionPointRec(GetMousePosition(), resetBox)) mouseOnReset = true;
                        else mouseOnReset = false;
                    DrawRectangleRec(resetBox, LIGHTGRAY);
                    if (mouseOnReset) {
                        DrawRectangleLines((int)resetBox.x, (int)resetBox.y, (int)resetBox.width, (int)resetBox.height, RED);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            // Reset game
                            srand((unsigned)time(NULL));
                            target_value = rand() % 101;       // 0..100
                            letterCount = 0;
                            guessCount = 0;
                            for (int i = 0; i < 7; i++) {
                                guesses[i] = 0;
                            }
                            loss = false;
                            win = false;
                            name[0] = '\0';
                        }
                    }
                }
                if (win) {
                    DrawText("You Win!", 350, 300, 40, GREEN);
                    if (CheckCollisionPointRec(GetMousePosition(), resetBox)) mouseOnReset = true;
                        else mouseOnReset = false;
                    DrawRectangleRec(resetBox, LIGHTGRAY);
                    if (mouseOnReset) {
                        DrawRectangleLines((int)resetBox.x, (int)resetBox.y, (int)resetBox.width, (int)resetBox.height, GREEN);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            // Reset game
                            srand((unsigned)time(NULL));
                            target_value = rand() % 101;       // 0..100
                            letterCount = 0;
                            guessCount = 0;
                            for (int i = 0; i < 7; i++) {
                                guesses[i] = 0;
                            }
                            loss = false;
                            win = false;
                            name[0] = '\0';
                        }
                    }
                }

            EndDrawing();
            //----------------------------------------------------------------------------------
        }

        // De-Initialization
        //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------

        return 0;
    }

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}