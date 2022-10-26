//=============================================================================
#include "GameState.h"
#include "Resources.h"
//=============================================================================
enum currMap{first, second, third};
enum GameButtons{ Undo_B, Quit_B, Pause_B};
//=============================================================================
//
GameState::GameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
	:State(window, states){
	m_board = new Board(*window);
	m_board->randomLava(DIFFICULTIES[(++m_difficulty) % 3]);
	setBackground(Resources::instance().getTexture((int)Textures::GameBG));
    Resources::instance().playMusic(Sounds::GameMusic);
	setTexts();
	setButtons();
}
//=============================================================================
//
GameState::~GameState(){
	delete m_board;
}
//=============================================================================
//
void GameState::setButtons(){
	m_buttons[(int)GameButtons::Undo_B] = std::make_unique<Button>
		(UNDO_POSITION, GAME_BUTTON_SIZE, UNDO_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
}
//=============================================================================
//
void GameState::update(const float& deltaTime){
	m_deltaTime = m_gameClock.restart().asSeconds();
	updateMouse();
	m_board->update(m_deltaTime);
	updateButtons();
	m_texts[(int)Texts::Counter].setString(CLICKS_TEXT + std::to_string(m_clicks));
	
	
	if (m_board->didPlayerWin())
		levelWin();
	else if (m_board->didCatWin())
		lostToCat();
}
//=============================================================================
//
void GameState::updateButtons() {
	for (auto& button : m_buttons) {
		button.second->update(m_mouseView);
	}
	if (m_buttons.find(Undo_B)->second->isClicked()){
		if (m_board->undo()) {
			m_clicks--;
			return;
		}
	}
}
//=============================================================================
//
void GameState::handleEvents() {
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
void GameState::keyBoardEvent(const sf::Event& evnt) {
	switch (evnt.key.code) {
	case sf::Keyboard::Escape:
	case sf::Keyboard::Q:
		this->m_end = true;
		Resources::instance().stopMusic();
		break;

	case sf::Keyboard::U:
		if (m_board->undo())
			m_clicks--;
		break;

	case sf::Keyboard::R:
		m_board->resetLevel(); break;
	}
}
//=============================================================================
// 
void GameState::mouseEvent(const sf::Event& evnt) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (m_board->mouseClicked(m_mouseView)) {
			m_clicks++;
		}
	}
}
//=============================================================================
//drawing all game related objects: board which include all board tiles and the cat.
//background and the buttons.
void GameState::draw(){
	m_window->draw(m_backGround);

	m_window->draw(m_texts[(int)Texts::Title]);
	m_window->draw(m_texts[(int)Texts::Counter]);


	for (auto& button : m_buttons)
		button.second->draw(*m_window);
	
	m_board->draw();
}
//=============================================================================
void GameState::levelWin(){
	bool stop = false;
	while (!stop){
		m_window->clear();
		draw();
		m_window->draw(m_texts[(int)Texts::WIN]);
		for (auto evnt = sf::Event(); m_window->pollEvent(evnt);){
			if (evnt.type == sf::Event::Closed){
				stop = true; m_window->close();
			}
			else if (evnt.type == sf::Event::KeyPressed){
				stop = true;
				m_board->nextLevel((++m_difficulty) % 3);
				return;
			}
		}
		m_window->display();
	}
}
//=============================================================================
//
void GameState::lostToCat() {
	bool stop = false;
	while (!stop) {
		m_window->clear();
		draw();
		m_window->draw(m_texts[(int)Texts::Lossing]);
		for (auto evnt = sf::Event(); m_window->pollEvent(evnt);) {
			switch (evnt.type) {
			case sf::Event::Closed:
				stop = true; m_window->close(); break;

			case sf::Event::KeyPressed: {
				switch (evnt.key.code) {
				case sf::Keyboard::Escape:
					stop = true; m_window->close(); break;
				case sf::Keyboard::N:
					stop = true; m_window->close(); break;
				case sf::Keyboard::Y:
					stop = true; break;
				}
			}
			}
		}
		m_window->display();
	}
	
	m_board->resetLevel();
	m_clicks = 0;
	
}
//=============================================================================
//
void GameState::setTexts()
{
	setText(37, TITLE_TEXT, sf::Color::Black, GAME_TITLE_POS);
	setText(25, CLICKS_TEXT, sf::Color::White, CLICKS_POSITION);
	setText(35, LOSSING_TEXT, sf::Color::Cyan, LOSSING_POSITION);
	setText(35, WIN_TEXT, sf::Color::Yellow, WIN_POSITION);
}
//=============================================================================
//
void GameState::setText(int size, const std::string& str,
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
//=============================================================================