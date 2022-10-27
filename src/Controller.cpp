//=============================================================================
#include "Controller.h"
#include "MenuState.h"
//=============================================================================
//
Controller::Controller()
    :m_currMod(States::Menu){
    m_states.emplace(initMenu());
}
//=============================================================================
//
void Controller::run(){
    while (m_window->isOpen()){
        update();
        display();
    }
}
//=============================================================================
void Controller::update(){
    m_deltaTime = m_clock.restart().asSeconds();
    if (!m_states.empty()){
        m_states.top()->update(m_deltaTime);
        m_states.top()->handleEvents();

        if (m_states.top()->isEnd()){
            m_states.pop();
            if(!m_states.empty())
                m_states.top()->music();
        }
    }
    else
        m_window->close();
}
//=============================================================================
// 
void Controller::display() {
    m_window->clear();

    if (!m_states.empty())
        m_states.top()->draw();

    m_window->display();
}
//=============================================================================
//
std::unique_ptr<State> Controller::initMenu(){
    sf::VideoMode windSize;
    std::string windName;
    unsigned frameLim;
    windSize = sf::VideoMode(GAME_WIDTH, GAME_HEIGHT);
    windName = "Circle The Cat";
    frameLim = 60;
    m_window = std::make_unique<sf::RenderWindow>(windSize, windName, sf::Style::Close | sf::Style::Titlebar);
    m_window->setFramerateLimit(60);
    return std::make_unique<MenuState>(m_window.get(), &m_states);
}
//=============================================================================
//