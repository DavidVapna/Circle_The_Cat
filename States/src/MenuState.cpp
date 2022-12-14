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
    music();
}
//=============================================================================
// 
void MenuState::music() {
    Resources::instance().playMusic(Sounds::MenuMusic);
}
//=============================================================================
void MenuState::setTitle(){
    m_title.setFont(Resources::instance().getFont((int)Fonts::Classic));
    m_title.setCharacterSize(45);
    m_title.setString(TITLE_TEXT);
    m_title.setPosition(MENU_TITLE_POS);
    m_title.setOrigin(m_title.getGlobalBounds().width / 2.f, m_title.getGlobalBounds().height / 2.f);
    m_title.setColor(sf::Color::Red);
}
//=============================================================================
MenuState::~MenuState(){

}
//=============================================================================
void MenuState::setButtons(){
    m_buttons[(int)MenuButtons::Play_B] = std::make_unique<Button>
        (PLAY_POS, MENU_BUTTON_SIZE, PLAY_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
    m_buttons[(int)MenuButtons::Help_B] = std::make_unique<Button>
        (HELP_POS, MENU_BUTTON_SIZE, HELP_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
    m_buttons[(int)MenuButtons::Quit_B] = std::make_unique<Button>
        (QUIT_POS, MENU_BUTTON_SIZE, QUIT_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
}
//=============================================================================
void MenuState::draw(){
    m_window->draw(m_backGround);
    m_window->draw(m_title);

    for (auto& button : m_buttons)
        button.second->draw(*m_window);
}
//=============================================================================
void MenuState::update(const float& deltaTime){
    updateMouse();
    updateButtons(deltaTime);
   
}
//=============================================================================
void MenuState::keyBoardEvent(const sf::Event& evnt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
        m_window->close();
        this->m_end = true;
    }
}
//=============================================================================
void MenuState::handleEvents() {
    for (auto event = sf::Event(); m_window->pollEvent(event);) {
        switch (event.type) {
        case sf::Event::Closed:
            m_window->close(); break;

        case sf::Event::KeyPressed:
            keyBoardEvent(event); break;

        case sf::Event::MouseButtonPressed:
            mouseEvent(event); break;
        
        }
    }
}
//=============================================================================
// 
void MenuState::updateButtons(const float& deltaTime) {
    for (auto& button : m_buttons) {
        button.second->update(m_mouseView, deltaTime);
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
}
//=============================================================================