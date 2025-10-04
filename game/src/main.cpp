#include "raylib.h"
#include "raymath.h"
#include <cstdlib>

inline float Random(float min, float max)
{
    return min + (rand() / ((float)RAND_MAX / (max - min)));
}

constexpr float SCREEN_WIDTH = 1200.0f;
constexpr float SCREEN_HEIGHT = 800.0f;
constexpr Vector2 CENTER{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

// Ball can move half the screen width per-second
constexpr float BALL_SPEED = SCREEN_WIDTH * 0.5f;
constexpr float BALL_SIZE = 40.0f;

// Paddles can move half the screen height per-second
constexpr float PADDLE_SPEED = SCREEN_HEIGHT * 0.5f;
constexpr float PADDLE_WIDTH = 40.0f;
constexpr float PADDLE_HEIGHT = 80.0f;

constexpr int maxScore = 5; 

struct Box
{
    float xMin;
    float xMax;
    float yMin;
    float yMax;
};

bool BoxOverlap(Box box1, Box box2)
{
    bool x = box1.xMax >= box2.xMin && box1.xMin <= box2.xMax;
    bool y = box1.yMax >= box2.yMin && box1.yMin <= box2.yMax;
    return x && y;
}

Rectangle BoxToRec(Box box)
{
    Rectangle rec;
    rec.x = box.xMin;
    rec.y = box.yMin;
    rec.width = box.xMax - box.xMin;
    rec.height = box.yMax - box.yMin;
    return rec;
}

Box BallBox(Vector2 position)
{
    Box box;
    box.xMin = position.x - BALL_SIZE * 0.5f;
    box.xMax = position.x + BALL_SIZE * 0.5f;
    box.yMin = position.y - BALL_SIZE * 0.5f;
    box.yMax = position.y + BALL_SIZE * 0.5f;
    return box;
}

Box PaddleBox(Vector2 position)
{
    Box box;
    box.xMin = position.x - PADDLE_WIDTH * 0.5f;
    box.xMax = position.x + PADDLE_WIDTH * 0.5f;
    box.yMin = position.y - PADDLE_HEIGHT * 0.5f;
    box.yMax = position.y + PADDLE_HEIGHT * 0.5f;
    return box;
}

void ResetBall(Vector2& position, Vector2& direction)
{
    position = CENTER;
    direction.x = rand() % 2 == 0 ? -1.0f : 1.0f;
    direction.y = 0.0f;
    direction = Vector2Rotate(direction, Random(0.0f, 80.0f)* DEG2RAD);
}

void DrawBall(Vector2 position, Color color)
{
    Box ballBox = BallBox(position);
    DrawRectangleRec(BoxToRec(ballBox), color);
}

void DrawPaddle(Vector2 position, Color color)
{
    Box paddleBox = PaddleBox(position);
    DrawRectangleRec(BoxToRec(paddleBox), color);
}

int main()
{
    Vector2 ballPosition;
    Vector2 ballDirection;
    ResetBall(ballPosition, ballDirection);

    Vector2 paddle1Position, paddle2Position;
    paddle1Position.x = SCREEN_WIDTH * 0.05f;
    paddle2Position.x = SCREEN_WIDTH * 0.95f;
    paddle1Position.y = paddle2Position.y = CENTER.y;

    int testScore = 0;
    int testScore2 = 0;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    InitAudioDevice();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        float ballDelta = BALL_SPEED * dt;
        float paddleDelta = PADDLE_SPEED * dt;

        // Move paddle with key input
        if (IsKeyDown(KEY_W))
            paddle1Position.y -= paddleDelta;
        if (IsKeyDown(KEY_S))
            paddle1Position.y += paddleDelta;

        if (IsKeyDown(KEY_UP))
            paddle2Position.y -= paddleDelta;
        if (IsKeyDown(KEY_DOWN))
            paddle2Position.y += paddleDelta; 


        float phh = PADDLE_HEIGHT * 0.5f;
        paddle1Position.y = Clamp(paddle1Position.y, phh, SCREEN_HEIGHT - phh);
        paddle2Position.y = Clamp(paddle2Position.y, phh, SCREEN_HEIGHT - phh);

        // Change the ball's direction on-collision
        Vector2 ballPositionNext = ballPosition + ballDirection * ballDelta;
        Box ballBox = BallBox(ballPositionNext);
        Box paddle1Box = PaddleBox(paddle1Position);
        Box paddle2Box = PaddleBox(paddle2Position);

        // TODO -- increment the scoring player's score after they've touched the ball and the ball goes too far right/left
        
        if (ballBox.xMin < 0.0f )

        {
            PlaySound(LoadSound("resources/PingPong.mp3")); //play sound when it hits the ball from one side
            testScore++;
            ResetBall(ballPosition, ballDirection);
            
        }
        
        if (testScore>= maxScore)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Player 1 wins!", SCREEN_WIDTH * 0.5f - MeasureText("Player 1 Wins!", 50) * 0.5f, SCREEN_HEIGHT * 0.5f - 30, 50, YELLOW);
            DrawText("Press 'R' to Replay || Press 'Q' to Quit", SCREEN_WIDTH * 0.5F - MeasureText("Press 'R' to Replay || Press 'Q' to Quit", 50) * 0.5f, SCREEN_HEIGHT * 0.7f - 20, 20, YELLOW);
            EndDrawing();
        }

        if (ballBox.yMin < 0.0f || ballBox.yMax > SCREEN_HEIGHT)
        {
            PlaySound(LoadSound("resources/PingPong.mp3"));
            ballDirection.y *= -1.0f;
        }
        if (BoxOverlap(ballBox, paddle1Box) || BoxOverlap(ballBox, paddle2Box))
        {
            PlaySound(LoadSound("resources/PingPong.mp3"));
            ballDirection.x *= -1.0f;
        }

        if (ballBox.xMax > SCREEN_WIDTH)
           
        {
            PlaySound(LoadSound("resources/PingPong.mp3")); //play sound when the other ball hits
            testScore2++;
            ResetBall(ballPosition, ballDirection);
        }
        if (testScore2 >= maxScore)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Player 2 wins!", SCREEN_WIDTH * 0.5f - MeasureText("Player 2 Wins!", 50) * 0.5f,SCREEN_HEIGHT * 0.5f - 30, 50, YELLOW);
            DrawText("Game Over", SCREEN_WIDTH * 0.5F - MeasureText("Game Over", 50) * 0.5f, SCREEN_HEIGHT * 0.7f - 50, 20, YELLOW);
            EndDrawing();
        }
        
        // Update ball position after collision resolution, then render
        ballPosition = ballPosition + ballDirection * ballDelta;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawBall(ballPosition, YELLOW);
        DrawPaddle(paddle1Position, BLUE);
        DrawPaddle(paddle2Position, RED);

        // Text format requires you to put a '%i' wherever you want an integer, then add said integer after the comma
        const char* testScoreText = TextFormat("Test Score: %i ", testScore);
        const char* testScoreText2 = TextFormat("Test Score: %i ", testScore2);

        // We can measure our text for more exact positioning. This puts our score in the center of our screen!
        DrawText(testScoreText, SCREEN_WIDTH * 0.5f - MeasureText(testScoreText, 20) * 0.5f, 50, 20, RED);
        DrawText(testScoreText2, SCREEN_WIDTH * 0.5f - MeasureText(testScoreText2, 20) * 0.5f, 100, 20, BLUE);
        
        EndDrawing();
    }
    BeginDrawing();

    CloseAudioDevice();
    CloseWindow();
    return 0;
}

