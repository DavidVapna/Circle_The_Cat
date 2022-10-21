//=============================================================================
#include "MenuState.h"
#include "Resources.h"
#include "GameState.h"
//=============================================================================
enum MenuButtons { Play_B, Quit_B, Help_B };
//=============================================================================
MenuState::MenuState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
    :State(window, states){
    setBackground(Resources::instance().getTexture((int)Textures::MenuBG));
    setButtons();
    setTitle();
    Resources::instance().playMusic(Sounds::MenuMusic);
}
//=============================================================================
void MenuState::setTitle(){
    m_title.setFont(Resources::instance().getFont((int)Fonts::Classic));
    m_title.setCharacterSize(45);
    m_title.setString(TITLE_TEXT);
    m_title.setPosition(TITLE_POSITION);
    m_title.setOrigin(m_title.getGlobalBounds().width / 2.f, m_title.getGlobalBounds().height / 2.f);
    m_title.setColor(sf::Color::Red);
}
//=============================================================================
MenuState::~MenuState(){

}
//=============================================================================
void MenuState::setButtons(){
    m_buttons[(int)MenuButtons::Play_B] = std::make_unique<Button>
        (PLAY_POS, BUTTONS_SIZE, PLAY_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
    m_buttons[(int)MenuButtons::Help_B] = std::make_unique<Button>
        (HELP_POS, BUTTONS_SIZE, HELP_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
    m_buttons[(int)MenuButtons::Quit_B] = std::make_unique<Button>
        (QUIT_POS, BUTTONS_SIZE, QUIT_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
}
//=============================================================================
void MenuState::draw(){
    m_window->draw(m_backGround);
    m_window->draw(m_title);

    for (auto& button : m_buttons){
        button.second->draw(*m_window);
    }
}
//=============================================================================
void MenuState::update(const float& deltaTime){
    updateMouse();

    for (auto& button : m_buttons) {
        button.second->update(m_mouseView);
    }
    if (m_buttons.find(Quit_B)->second->isClicked()) {
        //maybeAddDialog.
        this->m_end = true;
    }
    if (m_buttons.find(Play_B)->second->isClicked() ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
        m_states->emplace(std::make_unique<GameState>(m_window, this->m_states));
        return;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
        //need to ask dialog.
        this->m_end = true;
    }
}
//=============================================================================
void MenuState::keyBoardEvent(const sf::Event& evnt){
    switch (evnt.key.code){
    case sf::Keyboard::Escape:
        m_window->close(); break;
    }
}
//=============================================================================