#include "Game.h"

Game::Game(const std::string& file_name)
{
    this->init(file_name);
}

void Game::init(const std::string& file_name)
{
    std::ifstream file_stream(file_name);
    file_stream >> m_window_config.name >> m_window_config.size.x >> m_window_config.size.y >> m_window_config.FPS >> m_window_config.is_full_screen;
    file_stream >> m_font_config.file_name >> m_font_config.size >> m_font_config.FR >> m_font_config.FG >> m_font_config.FB;
    file_stream >> m_player_config.SR >> m_player_config.CR >> m_player_config.S >> m_player_config.FR;
    file_stream >> m_player_config.FG >> m_player_config.FB >> m_player_config.OR >> m_player_config.OG;
    file_stream >> m_player_config.OB >> m_player_config.OT >> m_player_config.V;
    file_stream >> m_enemy_config.SR >> m_enemy_config.CR >> m_enemy_config.Smin >> m_enemy_config.Smax;
    file_stream >> m_enemy_config.OR >> m_enemy_config.OG >> m_enemy_config.OB >> m_enemy_config.OT;
    file_stream >> m_enemy_config.Vmin >> m_enemy_config.Vmax >> m_enemy_config.L >> m_enemy_config.SI;
    file_stream >> m_bullet_config.SR >> m_bullet_config.CR >> m_bullet_config.S >> m_bullet_config.FR;
    file_stream >> m_bullet_config.FG >> m_bullet_config.FB >> m_bullet_config.OR >> m_bullet_config.OG;
    file_stream >> m_bullet_config.OB >> m_bullet_config.OT >> m_bullet_config.V >> m_bullet_config.L >> m_bullet_config.CD;
    m_window_config.is_full_screen == 1 ?
    m_window.create(sf::VideoMode(m_window_config.size.x, m_window_config.size.y),m_window_config.name,sf::Style::Fullscreen):
    m_window.create(sf::VideoMode(m_window_config.size.x, m_window_config.size.y),m_window_config.name);
    m_window.setFramerateLimit(m_window_config.FPS);
    m_font.loadFromFile(m_font_config.file_name);
    m_score_text.setFont(m_font);
    m_score_text.setFillColor(sf::Color(m_font_config.FR, m_font_config.FR, m_font_config.FR));
    m_score_text.setCharacterSize(28);
    m_score_text.setString(std::to_string(m_score));
    m_score_text.setPosition(10, 10);
}

void Game::spawnPlayer()
{
    std::shared_ptr<Entity> player = m_entity_manager.addEntity("player");
    player->cInput = std::make_shared<CInput>();
    player->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x , m_window.getSize().y) / 2,
                                                    Vec2(0, 0));
    player->cShape = std::make_shared<CShape>(m_player_config.SR, m_player_config.V,
                                              Vec3(m_player_config.FR, m_player_config.FG, m_player_config.FB),
                                              Vec3(m_player_config.OR, m_player_config.OG, m_player_config.OB),
                                              m_player_config.OT);
    player->cCollision = std::make_shared<CCollision>(m_player_config.CR);
    m_player = player;
}

void Game::spawnEnemy()
{
    std::srand(std::time(0));
    int random_posX = rand() % m_window.getSize().x;
    int random_posY = rand() % m_window.getSize().y;
    int random_speedX = rand() % (int)m_enemy_config.Smin + m_enemy_config.Smin;
    int random_speedY = rand() % (int)m_enemy_config.Smin + m_enemy_config.Smin;
    int rand_vertices = rand() % (int)m_enemy_config.Vmin + m_enemy_config.Vmin;
    int rand_sign = rand() % 2;
    rand_sign = rand_sign == 0 ? 1 : -1 ;
    std::shared_ptr<Entity> enemy = m_entity_manager.addEntity("enemy");
    enemy->cTransform = std::make_shared<CTransform>(Vec2(random_posX, random_posY),
                                                     Vec2(rand_sign * random_speedX, rand_sign * random_speedY),
                                                      2);
    enemy->cShape = std::make_shared<CShape>(m_enemy_config.SR, rand_vertices,
                                            Vec3(rand() % 255, rand() % 255, rand() % 255),
                                            Vec3(m_enemy_config.OR, m_enemy_config.OG, m_enemy_config.OB),
                                            m_enemy_config.OT);
    enemy->cCollision = std::make_shared<CCollision>(m_enemy_config.CR);
}

void Game::spawnBullet(std::shared_ptr<Entity> player, const Vec2& mouse_pos)
{
    std::shared_ptr<Entity> bullet = m_entity_manager.addEntity("bullet");
    bullet->cTransform = std::make_shared<CTransform>(m_player->cTransform->position,
                                                      Vec2(mouse_pos - m_player->cTransform->position).normalized() * -m_bullet_config.S);
    bullet->cShape = std::make_shared<CShape>(m_bullet_config.CR,
                                              m_bullet_config.V,
                                              Vec3(m_bullet_config.FR, m_bullet_config.FG, m_bullet_config.FB),
                                              Vec3(m_bullet_config.OR, m_bullet_config.OG, m_bullet_config.OB),
                                              m_bullet_config.OT);
    bullet->cLifespan = std::make_shared<CLifespan>(m_bullet_config.L);
    bullet->cCollision = std::make_shared<CCollision>(m_bullet_config.CR);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> parent_enemy)
{
    int circle_sides = 360;
    auto parent_pos = parent_enemy->cTransform->position.normalized();
    int vertices = parent_enemy->cShape->shape.getPointCount();
    float angle = circle_sides/vertices;
    float parent_speed = parent_enemy->cTransform->velocity.len();
    float prev = 0;
    float shift = angle - 90;
    for(int i = 1; i < vertices + 1; i++)
    {
        std::shared_ptr<Entity> enemy = m_entity_manager.addEntity("small_enemy");
        enemy->cTransform = std::make_shared<CTransform>(Vec2(parent_enemy->cTransform->position),
                                                        Vec2(std::cos((parent_enemy->cTransform->position.angleDeg()) + (prev * i) + shift),
                                                         std::sin((parent_enemy->cTransform->position.angleDeg()) + (prev * i)+ shift)) * parent_speed);
                                                         prev = parent_enemy->cTransform->position.angleDeg()+prev + shift;
        enemy->cShape = std::make_shared<CShape>(m_enemy_config.SR/vertices, vertices,
                                                Vec3(parent_enemy->cShape->shape.getFillColor().r,
                                                     parent_enemy->cShape->shape.getFillColor().g,
                                                     parent_enemy->cShape->shape.getFillColor().b),
                                                Vec3(m_enemy_config.OR, m_enemy_config.OG, m_enemy_config.OB),
                                                m_enemy_config.OT);
        enemy->cCollision = std::make_shared<CCollision>(m_enemy_config.CR/vertices);
        enemy->cLifespan = std::make_shared<CLifespan>(m_enemy_config.L);
    }
}

void Game::spawnSpecialAttack(std::shared_ptr<Entity> player)
{
        std::shared_ptr<Entity> shiled = m_entity_manager.addEntity("shiled");
        shiled->cTransform = std::make_shared<CTransform>(player->cTransform->position, player->cTransform->velocity * 5);
        shiled->cShape = std::make_shared<CShape>(m_player_config.SR, m_player_config.V,
                                                Vec3(255, 255, 255),
                                                Vec3(m_player_config.OR,
                                                     m_player_config.OG,
                                                     m_player_config.OB),
                                                m_player_config.OT);
        shiled->cCollision = std::make_shared<CCollision>(m_player_config.CR + 5);
        shiled->cLifespan = std::make_shared<CLifespan>(m_special_cool_down);
}

void Game::sRender()
{
    m_window.clear();
    for(auto& e : m_entity_manager.getEntites())
    {
        if(e->cLifespan && e->cShape)
        {
         int alpha_modifyer = ((255/e->cLifespan->total) * e->cLifespan->remaining);
         sf::Color fcolor = e->cShape->shape.getFillColor();
         sf::Color ocolor = e->cShape->shape.getOutlineColor();
         fcolor.a = alpha_modifyer;
         ocolor.a = alpha_modifyer;
         e->cShape->shape.setFillColor(fcolor);
         e->cShape->shape.setOutlineColor(ocolor);
        }
        if(e->cShape && e->cTransform)
        {
            e->cShape->shape.rotate(e->cTransform->angle);
            m_window.draw(e->cShape->shape);
        }
    }
    m_window.draw(m_score_text);
    m_window.display();
}


void Game::sMovment()
{
    if(m_player->cInput->up)
    {
        m_player->cTransform->velocity.y = m_player_config.S * -1;
    }
    if(m_player->cInput->down)
    {
        m_player->cTransform->velocity.y = m_player_config.S;
    }
    if(m_player->cInput->right)
    {
        m_player->cTransform->velocity.x = m_player_config.S;
    }
    if(m_player->cInput->left)
    {
        m_player->cTransform->velocity.x = m_player_config.S * -1;
    }
    for(auto& e : m_entity_manager.getEntites())
    {
        if(e->cTransform)
        {
            e->cShape->shape.setOrigin(e->cShape->shape.getRadius(), e->cShape->shape.getRadius());
            e->cTransform->position += e->cTransform->velocity * m_delta_time;
            e->cShape->shape.setPosition(e->cTransform->position.toSfVec());
        }
    }
}


void Game::sInput()
{
    m_player->cInput->up = false;
    m_player->cInput->down = false;
    m_player->cInput->right = false;
    m_player->cInput->left = false;
    m_player->cInput->shoot = false;
    m_player->cInput->special = false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_player->cInput->up = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_player->cInput->down = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_player->cInput->right = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_player->cInput->left = true;
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        m_player->cInput->shoot = true;
        m_mouse_pos.x = sf::Mouse::getPosition(m_window).x;
        m_mouse_pos.y = sf::Mouse::getPosition(m_window).y;
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        m_player->cInput->special = true;
    }
}

void Game::sCollision()
{
    for(auto& e : m_entity_manager.getEntites("enemy"))
    {
        if(e->cCollision)
        {
            if(m_player->cTransform->position.dist(e->cTransform->position)
                 <= (m_player->cCollision->radius + e->cCollision->radius))
            {
                m_player->cTransform->position = Vec2(m_window.getSize().x/2, m_window.getSize().y/2);
            }
        }
    }

    for(auto& e : m_entity_manager.getEntites("small_enemy"))
    {
        if(e->cCollision)
        {
            if(m_player->cTransform->position.dist(e->cTransform->position)
                 <= (m_player->cCollision->radius + e->cCollision->radius))
            {
                m_player->cTransform->position = Vec2(m_window.getSize().x/2, m_window.getSize().y/2);
            }
        }
    }


    for(auto& e : m_entity_manager.getEntites())
    {
        if(e->cCollision)
        {
            if(e->cTransform->position.x + e->cCollision->radius >= m_window.getSize().x
            || e->cTransform->position.x - e->cCollision->radius <= 0)
            {
                e->cTransform->position.x >  m_window.getSize().x/2 ?  e->cTransform->position.x = m_window.getSize().x - (e->cCollision->radius + 10)
                : e->cTransform->position.x = 0 + (e->cCollision->radius + 2);
                e->cTransform->velocity.x *= -1;
                //if(e->getTag() == "player") e->cTransform->position = Vec2(m_window.getSize().x/2, m_window.getSize().y/2);
            }

            if(e->cTransform->position.y + e->cCollision->radius >= m_window.getSize().y
            || e->cTransform->position.y - e->cCollision->radius <= 0)
            {
                e->cTransform->position.y >  m_window.getSize().y/2 ?  e->cTransform->position.y = m_window.getSize().y - (e->cCollision->radius + 10)
                : e->cTransform->position.y = 0 + (e->cCollision->radius + 2);
                e->cTransform->velocity.y *= -1;
                //if(e->getTag() == "player") e->cTransform->position = Vec2(m_window.getSize().x/2, m_window.getSize().y/2);
            }
        }
    }
    for(auto& e : m_entity_manager.getEntites("enemy"))
    {
        for(auto& b : m_entity_manager.getEntites("bullet"))
        {
            if(e->cTransform->position.dist(b->cTransform->position) <=
                e->cCollision->radius + b->cCollision->radius)
                {
                    this->spawnSmallEnemies(e);
                    e->destroy();
                    b->destroy();
                }
        }
    }

    for(auto& s : m_entity_manager.getEntites("shiled"))
    {
        for(auto& e : m_entity_manager.getEntites())
        {
            if(e->cCollision && e->getTag() != "player" && e->getTag() != "bullet" && e->getTag() != "shiled")
            {
                if(e->cTransform->position.dist(s->cTransform->position)
                     <= (e->cCollision->radius + s->cCollision->radius))
                {
                    e->destroy();
                    s->cLifespan->remaining -= 50;
                }
            }
        }
    }

}

void Game::sScore()
{
    m_score += m_current_frame /100;
    m_score_text.setString("Score: " + std::to_string(m_score));
    m_score_text.setPosition(10, 10);
}

void Game::sEnemySpawner()
{
    if(m_current_frame - m_last_enemy_spawn_time >= m_enemy_config.SI)
    {
        this->spawnEnemy();
        m_last_enemy_spawn_time = m_current_frame;
    }
}


void Game::sLifespan()
{
    for(auto& e : m_entity_manager.getEntites())
    {
        if(e->cLifespan && e->getTag() != "shiled")
        {
            e->cLifespan->remaining--;
            if(e->cLifespan->remaining <= 0)
            {
                e->destroy();
            }
        }
        else if(e->getTag() == "shiled")
        {
            if(e->cLifespan->remaining <= 0)
            {
                e->destroy();
            }
        }
    }
}

void Game::sCoolDown()
{
    if(m_current_frame - m_last_bullet_spawn_time >= m_bullet_config.CD && m_player->cInput->shoot)
    {
        this->spawnBullet(m_player, m_mouse_pos);
        m_last_bullet_spawn_time = m_current_frame;
    }

    if(m_current_frame - m_last_special_spawn_time >= m_special_cool_down && m_player->cInput->special)
    {
        this->spawnSpecialAttack(m_player);
        m_last_special_spawn_time = m_current_frame;
    }

}

void Game::setPaused(bool paused)
{
    m_is_paused = paused == true ? true : false;
}

void Game::run()
{
    this->init("game.conf");
    this->spawnPlayer();
    while(m_running)
    {
        m_delta_time = m_clock.restart().asSeconds();
        this->sEnemySpawner();
        m_entity_manager.update();
        sf::Event event;
        while(m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_running = false;
                m_window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::P)
                {
                    if(m_is_paused)
                        this->setPaused(false);
                    else
                        this->setPaused(true);
                }
            }
        }
        this->sInput();
        if(!m_is_paused)
        {
            m_current_frame++;
            if(m_player->cInput->shoot || m_player->cInput->special)
                this->sCoolDown();
            this->sMovment();
            this->sCollision();
            this->sLifespan();
            this->sScore();
        }
        this->sRender();
    }std::cout<<m_entity_manager.getEntites().size()<<std::endl;
}

