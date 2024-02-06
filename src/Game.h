#pragma once
#include "Commans.hpp"
#include "EntityManager.hpp"

struct PlayerConfig {int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;};
struct EnemyConfig  {int SR, CR, OR, OG, OB, OT, Vmin, Vmax, L, SI; float Smin, Smax;};
struct BulletConfig {int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S, CD;};
struct WindowConfig {std::string name; Vec2 size; int FPS, is_full_screen;};
struct FontConfig   {std::string file_name; int size, FR, FG, FB;};

class Game
{
    sf::RenderWindow m_window;
    EntityManager    m_entity_manager;
    sf::Font         m_font;
    sf::Text         m_score_text;
    WindowConfig     m_window_config;
    FontConfig       m_font_config;
    PlayerConfig     m_player_config;
    BulletConfig     m_bullet_config;
    EnemyConfig      m_enemy_config;
    int              m_score = 0;
    int              m_current_frame = 0;
    int              m_last_enemy_spawn_time = 0;
    int              m_last_bullet_spawn_time = 0;
    int              m_last_special_spawn_time = 0;
    const int        m_special_cool_down = 200;
    float            m_delta_time;
    sf::Clock        m_clock;
    bool             m_is_paused = false;
    bool             m_running = true;
    Vec2             m_mouse_pos;
    std::shared_ptr<Entity> m_player;

private:
    void init(const std::string& file_name);
    void setPaused(bool paused);
    //ECS Systems
    ////////////////////////////
    void sMovment();          //
    void sInput();            //
    void sLifespan();         //
    void sRender();           //
    void sEnemySpawner();     //
    void sCollision();        //
    void sCoolDown();         //
    void sScore();            //
    ////////////////////////////

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> parent_enemy);
    void spawnBullet(std::shared_ptr<Entity> player, const Vec2& mouse_pos);
    void spawnSpecialAttack(std::shared_ptr<Entity> player);

public:
    Game(const std::string& file_name);

    void run();




};
