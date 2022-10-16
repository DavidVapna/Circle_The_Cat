//=============================================================================
#include "Controller.h"
//=============================================================================
//
Controller::Controller()
    :m_window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Circle The Cat", sf::Style::Default)
{
    setSprites();
    setTexts();
    m_cat = new Cat(m_board.getTile(CAT_START));
    m_board.randomLava(DIFFICULTIES[(++m_difficulty)%3]);
}
//=============================================================================
//
void Controller::run()
{
    while (m_window.isOpen())
    {
        m_window.clear();
        handleEvents();
        update();
        draw();
        m_window.display();
    }
}
//=============================================================================
//
void Controller::handleEvents()
{
    m_mousePos = sf::Mouse::getPosition(m_window);
    m_mouseView = m_window.mapPixelToCoords(m_mousePos);

    if (m_catTurn)
    {
        catsTurn();
        return;
    }

    for (auto evnt = sf::Event(); m_window.pollEvent(evnt);)
    {
        switch (evnt.type)
        {
        case sf::Event::Closed:
            m_window.close(); break;

        case sf::Event::KeyPressed:
            keyBoardEvent(evnt); break;

        case sf::Event::MouseButtonPressed:
            mouseEvent(evnt);

            break;
        }
    }
}
//=============================================================================
//
void Controller::catsTurn()
{
    if (!m_board.validateRoute())
        if (!m_board.findExit(m_cat->getPosition()))
        {
            levelWin(); return;
        }
    m_cat->tryToRun(m_board.escapeTile());
    catJump();
    if (m_cat->didCatWin())
        lostToCat();
    m_catTurn = false;
}
//=============================================================================
//
void Controller::update()
{
    m_deltaTime = m_clock.restart().asSeconds();
    m_cat->update(m_deltaTime);
    m_texts[(int)Texts::Counter].setString(CLICKS_TEXT + std::to_string(m_clicks));
}
//=============================================================================
//
void Controller::draw() 
{
    for (auto& sprite : m_sprites)
        m_window.draw(sprite);

    for (int i = 0; i < 3; i++)
        m_window.draw(m_texts[i]);

    m_board.draw(m_window);
    m_catTurn ? m_cat->drawJump(m_window) : m_cat->draw(m_window);
}
//=============================================================================
//
void Controller::keyBoardEvent(const sf::Event& evnt)
{
    switch (evnt.key.code)
    {
    case sf::Keyboard::Escape:
        m_window.close(); break;

    case sf::Keyboard::U:
        undo(); break;

    case sf::Keyboard::R:
        restartLevel();
        break;
    }
}
//=============================================================================
//
void Controller::mouseEvent(const sf::Event& evnt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (m_board.mouseClicked(m_mouseView)) 
        {
            m_clicks++;
            m_catTurn = true;
        }
        if (m_texts[(int)Texts::Undo].getGlobalBounds().contains(m_mouseView))
            undo();
    }
}
//=============================================================================
//
void Controller::setSprites()
{
    sf::Sprite sprite(Resources::instance().getTexture((int)Textures::BackG));
    sf::Vector2f scaleTo;
    scaleTo.x = (float)GAME_WIDTH / sprite.getTexture()->getSize().x;
    scaleTo.y = (float)GAME_HEIGHT / sprite.getTexture()->getSize().y;
    sprite.setScale(scaleTo);
    m_sprites.push_back(sprite);
}
//=============================================================================
//
void Controller::undo()
{
    if (m_board.undo())
    {
        m_cat->undo();
        m_board.findExit(m_cat->getPosition());
        m_clicks--;
    }
}
//=============================================================================
//
void Controller::restartLevel()
{
    while (m_clicks > 0)
        undo();
}
//=============================================================================
//
void Controller::lostToCat()
{
    bool stop = false;
    m_catTurn = false;
    while (!stop)
    {
        m_window.clear();
        draw();
        m_window.draw(m_texts[(int)Texts::Lossing]);
        for (auto evnt = sf::Event(); m_window.pollEvent(evnt);)
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                stop = true; m_window.close(); break;

            case sf::Event::KeyPressed:
            {
                switch (evnt.key.code)
                {
                case sf::Keyboard::Escape:
                    stop = true; m_window.close(); break;
                case sf::Keyboard::N:
                    stop = true; m_window.close(); break;
                case sf::Keyboard::Y:
                    stop = true; break;
                }
            }
            }
        }
        m_window.display();
    }

    restartLevel();
}
//=============================================================================
//
void Controller::catJump()
{
    float deltaTime = 0.0f;
    sf::Clock clock;
    for (auto i = 0; i < JUMP_FRAMES; ++i)
    {
        m_window.clear();
        deltaTime = clock.restart().asSeconds();
        m_cat->jump(deltaTime);
        draw();
        m_window.display();
    }
}
//=============================================================================
//
void Controller::levelWin()
{
    bool stop = false;
    m_catTurn = false;
    while (!stop)
    {
        m_window.clear();
        draw();
        m_window.draw(m_texts[(int)Texts::WIN]);
        for (auto evnt = sf::Event(); m_window.pollEvent(evnt);)
        {
            if (evnt.type == sf::Event::Closed)
            {
                stop = true; m_window.close();
            }
            else if (evnt.type == sf::Event::KeyPressed)
            {
                stop = true;
                loadNextLevel((++m_difficulty)%3);
                return;
            }
        }
        m_window.display();
    }
}
//=============================================================================
//
void Controller::loadNextLevel(int difficulty)
{
    m_board.clearBoard();
    m_cat->newLevel(m_board.getTile(CAT_START));
    m_board.randomLava(DIFFICULTIES[difficulty]);
}
//=============================================================================
//
void Controller::setTexts()
{
    setText(37, TITLE_TEXT, sf::Color::Black, TITLE_POSITION);
    setText(25, CLICKS_TEXT, sf::Color::White, CLICKS_POSITION);
    setText(25, UNDO_TEXT, sf::Color::Magenta, UNDO_POSITION);
    setText(35, LOSSING_TEXT, sf::Color::Cyan, LOSSING_POSITION);
    setText(35, WIN_TEXT, sf::Color::Yellow, WIN_POSITION);
}
//=============================================================================
//
void Controller::setText(int size, const std::string& str,
    const sf::Color& color, const sf::Vector2f& pos)
{
    sf::Text text;
    text.setFont(Resources::instance().getFont((int)Fonts::Classic));
    text.setCharacterSize(size);
    text.setString(str);
    text.setFillColor(color);
    text.setPosition(pos);
    m_texts.push_back(text);
}