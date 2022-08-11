#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS          5
#define TFT_RST        32
#define TFT_DC         33
#define BACKLIGHT      12

#define GAMEON_UP      39
#define GAMEON_DOWN    15
#define GAMEON_LEFT    26
#define GAMEON_RIGHT   00
#define GAMEON_BUTTON  34

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {

  // setup screen
  tft.init(240, 240);
  tft.setRotation( 2 );
  tft.fillScreen( ST77XX_BLACK );

  pinMode( GAMEON_DOWN, INPUT_PULLUP );
  pinMode( GAMEON_UP, INPUT_PULLUP );
  pinMode( GAMEON_LEFT, INPUT_PULLUP );
  pinMode( GAMEON_RIGHT, INPUT_PULLUP );
  pinMode( GAMEON_BUTTON, INPUT_PULLUP );

}

enum directions { UP, RIGHT, DOWN, LEFT };

bool welcomescreen_rendered = false;
bool player_alive = false;
int player_x;
int player_y;
int player_direction;
int player_length = 0;
std::vector< std::pair< int, int > > player_positions;

int apple_x;
int apple_y;

int last_score = 0;
int high_score = 0;

void loop(){

  if( player_alive ) { // we are alive

    // if a joystick button is pushed, change the direction, make sure players don't go back
    if( ( player_direction != DOWN ) && ( digitalRead( GAMEON_UP ) == LOW ) ) player_direction = UP;
    else if( ( player_direction != UP ) && ( digitalRead( GAMEON_DOWN ) == LOW ) ) player_direction = DOWN;
    else if( ( player_direction != RIGHT ) && ( digitalRead( GAMEON_LEFT ) == LOW ) ) player_direction = LEFT;
    else if( ( player_direction != LEFT ) && ( digitalRead( GAMEON_RIGHT ) == LOW ) ) player_direction = RIGHT;

    // update playter position based on direction
    if( player_direction == UP ) player_y--;
    if( player_direction == DOWN ) player_y++;
    if( player_direction == LEFT ) player_x--;
    if( player_direction == RIGHT ) player_x++;

    // check if player eats apple
    if( ( player_x == apple_x ) && ( player_y == apple_y ) ) {
      player_length += 10;
      // find a new free position for the apple
      bool apple_placed = false;
      while( !apple_placed ) {
        apple_x = rand() % 30;
        apple_y = rand() % 30;
        // check if the apple is on the snake
        apple_placed = true;
        for( std::vector< std::pair< int, int > >::iterator i = player_positions.begin(); i != player_positions.end(); i++ )
          if( ( apple_x == i->first ) && ( apple_y == i->second ) )
            apple_placed = false;
      }
      tft.fillCircle( apple_x * 8 + 4, apple_y * 8 + 4, 3, ST77XX_RED );
    }
    
    // check if player hits boundary
    if( ( player_x < 0 ) || ( player_x >= 30 ) || ( player_y < 0 ) || ( player_y >= 30 ) )
      player_alive = false;

    // check if player hits themselves
    for( std::vector< std::pair< int, int > >::iterator i = player_positions.begin(); i != player_positions.end(); i++ )
      if( ( player_x == i->first ) && ( player_y == i->second ) )
        player_alive = false;

    // update position history to represent the snake
    player_positions.push_back( std::pair< int, int >( player_x, player_y ) );
    if( player_positions.size() > player_length ) {
      tft.fillRect( player_positions[ 0 ].first * 8, player_positions[ 0 ].second * 8, 8, 8, ST77XX_BLACK );
      player_positions.erase( player_positions.begin() );
    }

    // draw current head position of the snake
    tft.fillRect( player_x * 8, player_y * 8, 8, 8, ST77XX_WHITE );

  } else { // we are dead

    last_score = player_length;
    if( last_score > high_score ) high_score = last_score;
    
    if( !welcomescreen_rendered ) { // render the welcome screen and scores

      tft.fillScreen( ST77XX_BLACK );
      tft.setTextColor( ST77XX_RED );
      
      tft.setTextSize( 3 );
      tft.setCursor( 80, 30 );
      tft.println( "SNAKE");

      tft.setTextColor( ST77XX_WHITE );

      tft.setTextSize( 2 );
      tft.setCursor( 10, 100 );
      tft.println( "Score");
      tft.setCursor( 10, 140 );
      tft.println( "Hi score");

      tft.setTextSize( 3 );
      tft.setCursor( 150, 100 );
      tft.println( String( last_score ) );
      tft.setCursor( 150, 140 );
      tft.println( String( high_score ) );

      tft.setTextSize( 1 );
      tft.setCursor( 10, 200 );
      tft.println( "Press joystick to start" );

      welcomescreen_rendered = true;

    }
    
    if( digitalRead( GAMEON_BUTTON ) == LOW ) { // reset the game

      player_positions.clear();
      welcomescreen_rendered = false;
      player_alive = true;
      player_x = 15;
      player_y = 15;
      player_direction = UP;
      apple_x = 15;
      apple_y = 14;
      player_length = 0;         
      tft.fillScreen(ST77XX_BLACK);
      
   }
   
  }
 
 delay(100);
}