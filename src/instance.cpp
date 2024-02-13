#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>

#include "components.h"
#include "globals.h"
#include "grid_entry.h"
#include "tetromino.h"

/// Globals
sf::RenderWindow *window;
sf::Clock clk;
Score score = Score();
sf::Event evnt;

// TODO add paused state
enum Scene
{
    WELCOME,
    PLAYING,
    GAME_OVER,
    HELP
} scene = WELCOME;

/// function declarations
void draw_border_col(int pos);
void draw_border_row(int pos);
void draw_grid_debug();
void key_handler(sf::Keyboard::Key key, Tetromino_Controller &block);
bool detect_game_over(Tetromino tetromino);

class SceneManager
{
    sf::Font font;
    sf::Text text;

    unsigned int points = 0, rows = 0;

    inline void set_heading_text()
    {
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition(5 * GRID_SIZE, 5 * GRID_SIZE);
    }

    inline void set_info_text()
    {
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(3 * GRID_SIZE + 10, 10 * GRID_SIZE);
    }

  public:
    void display_help()
    {
        set_info_text();
        text.setPosition(GRID_SIZE, GRID_SIZE);
        text.setFillColor(sf::Color::Green);
        text.setCharacterSize(20);
        text.setString(
            "GAME CONTROL:\n\n\n"
            "Left \tmove block left\n\n"
            "Right\tmove block right\n\n"
            "Down \tland block down\n\n\n"

            "Ctrl + Right\n\t\t   Rotate clockwise\n\n"
            "Ctrl + Left\n\t\t   Rotate anti clockwise\n"
            "\n\n\n\n\n\n(Escape) to exit help");
        window->draw(text);
    }

    SceneManager()
    {
        // load font
        font.loadFromFile("pixel_font.ttf");

        // Create a text
        text = sf::Text();
        text.setFont(font);
        text.setStyle(sf::Text::Regular);
    }

    void record_points()
    {
        points = score.get_points();
        rows = score.get_rows();
    }

    void display_welcome()
    {
        set_heading_text();
        text.setString("Tetris");
        window->draw(text);

        set_info_text();
        text.setString("press Enter to play\n\n\n\nF1 -> Tetris Help");
        window->draw(text);
    }

    void display_game_over()
    {
        set_heading_text();
        text.setPosition(4 * GRID_SIZE, 5 * GRID_SIZE);
        text.setString("Game Over");
        window->draw(text);

        set_info_text();
        std::ostringstream os;
        os << "rows: " << rows << "\t"
           << "points: " << points
           << "\n\n\nPress Enter to replay";

        text.setString(os.str());
        window->draw(text);
    }

    static void play(Tetromino_Controller &controller, Tetromino_Preview &preview)
    {
        draw_border_col(SEPERATOR_POS);

        // draw the active tetromino
        controller.draw();

        // display score
        score.draw();

        // display the preview of next tetromino
        preview.draw();

        // enable falling blocks
        if (static_cast<unsigned int>(clk.getElapsedTime().asMilliseconds()) > ELAPSED_TIME)
        {
            if (!controller.has_block_finished())
                controller.move(Down);

            // spawn new block after time limit
            else
                preview.submit_tetromino(controller);

            clk.restart();
        }

        // draw grid for debugging
        draw_grid_debug();
    }
};

int instance()
{
    auto controller = Tetromino_Controller();
    auto preview = Tetromino_Preview();
    SceneManager manager;

    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris",
                                  sf::Style::Close);
    window->setFramerateLimit(FPS);

    while (window->isOpen())
    {
        while (window->pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window->close();

            if (evnt.type == sf::Event::KeyPressed &&
                scene == PLAYING)
            {
                key_handler(evnt.key.code, controller);
            }

            else if (evnt.type == sf::Event::KeyPressed &&
                     scene == WELCOME)
            {
                if (evnt.key.code == sf::Keyboard::Enter)
                    scene = PLAYING;
                else if (evnt.key.code == sf::Keyboard::F1)
                    scene = HELP;
            }
            else if (evnt.type == sf::Event::KeyPressed &&
                     scene == HELP &&
                     evnt.key.code == sf::Keyboard::Escape)
            {
                scene = WELCOME;
            }
            else if (evnt.type == sf::Event::KeyPressed &&
                     scene == GAME_OVER &&
                     evnt.key.code == sf::Keyboard::Enter)
            {
                scene = PLAYING;
            }
        }
        window->clear();

        if (detect_game_over(preview.preview))
        {
            manager.record_points();
            score.reset();
            Grid_Entry::reset();
            scene = GAME_OVER; // set game over scene
        }

        // Show Different Scenes
        switch (scene)
        {
        case WELCOME:
            manager.display_welcome();
            break;
        case PLAYING:
            SceneManager::play(controller, preview);
            break;
        case GAME_OVER:
            manager.display_game_over();
            break;
        case HELP:
            manager.display_help();
            break;
        }

        window->display();
    }
    delete window;
    return 0;
}

bool detect_game_over(Tetromino tetromino)
{
    // if there are blocks in starting pos
    for (auto &b : tetromino.blocks)
    {
        sf::Vector2i spawning_pos = b.grid_pos;
        spawning_pos.x -= (PREVIEW_X - STARTING_X);
        spawning_pos.y -= PREVIEW_Y;

        if (Grid_Entry::has_entry(spawning_pos))
            return true;
    }
    return false;
}
