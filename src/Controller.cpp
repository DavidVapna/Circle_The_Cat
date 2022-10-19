//=============================================================================
#include "Controller.h"
#include "MenuState.h"
//=============================================================================
//
Controller::Controller()
    :m_currMod(States::Menu){
    m_states.emplace(initMenu());
    m_states.top()->setWindow();
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
    handleEvents();
    if (!m_states.empty()){
        m_states.top()->update(0);
        if (m_states.top()->isEnd()){
            m_states.pop();
            if (!m_states.empty())
                m_states.top()->setWindow();
        }
    }
    else
        m_window->close();
}
//=============================================================================
// 
void Controller::display(){
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
void Controller::handleEvents(){
    for (auto evnt = sf::Event(); m_window->pollEvent(evnt);){
        switch (evnt.type){
        case sf::Event::Closed:
            m_window->close(); break;
        }
    }
}

//=============================================================================
//
void Controller::keyBoardEvent(const sf::Event& evnt){
    switch (evnt.key.code){
    case sf::Keyboard::Escape:
        m_window->close(); break;
    }
}
//=============================================================================

