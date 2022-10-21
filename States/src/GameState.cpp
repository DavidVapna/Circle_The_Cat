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
		(UNDO_POSITION, BUTTONS_SIZE, UNDO_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);

    return;
}
//=============================================================================
//
void GameState::update(const float& deltaTime){
	if(m_board->didPlayerWin()) {
		levelWin();
	}
	if (m_board->didCatWin()) {
		lostToCat();
	}

	m_deltaTime = m_gameClock.restart().asSeconds();
	updateMouse();

	for (auto& button : m_buttons) {
		button.second->update(m_mouseView);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (m_board->mouseClicked(m_mouseView)) {
			m_clicks++;
		}
		if (m_texts[(int)Texts::Undo].getGlobalBounds().contains(m_mouseView)) {
			m_board->undo();
			m_clicks--;
		}
		
		//updateButtons();
		
		//if (m_buttons.find(Quit_B)->second->isClicked()) {
		//	//maybeAddDialog.
		//	this->m_end = true;
		//}
		//if (m_buttons.find(Undo_B)->second->isClicked() ||
		//	sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
		//	m_states->emplace(std::make_unique<GameState>(m_window, this->m_states));
		//	return;
		//}
	}
	//updateInput()
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		this->m_end = true;
		Resources::instance().stopMusic();
		return;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		//need to ask dialog.
		this->m_end = true;

	}
	m_texts[(int)Texts::Counter].setString(CLICKS_TEXT + std::to_string(m_clicks));
	m_board->update(m_deltaTime);

	//m_board->checkIfWin();
}
//=============================================================================
//
void GameState::draw(){
	m_window->draw(m_backGround);

	for (int i = 0; i < 3; i++)
		m_window->draw(m_texts[i]);

	m_board->draw();
}
//=============================================================================
//
void GameState::restartLevel(){
	while (m_clicks > 0)
		m_board->undo();
}
//=============================================================================
//
void GameState::handleEvents() {
	for (auto evnt = sf::Event(); m_window->pollEvent(evnt);) {
		switch (evnt.type) {
		case sf::Event::Closed:
			m_window->close(); break;

		case sf::Event::KeyPressed:
			keyBoardEvent(evnt); break;
		}
	}
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

	restartLevel();
}
//=============================================================================
//
void GameState::keyBoardEvent(const sf::Event& evnt){
	switch (evnt.key.code){
	case sf::Keyboard::Escape:
		m_window->close(); break;

	case sf::Keyboard::U:
		m_board->undo(); break;

	case sf::Keyboard::R:
		restartLevel();
		break;
	}
}
//=============================================================================
//
void GameState::setTexts()
{
	setText(37, TITLE_TEXT, sf::Color::Black, TITLE_POSITION);
	setText(25, CLICKS_TEXT, sf::Color::White, CLICKS_POSITION);
	setText(25, UNDO_TEXT, sf::Color::Magenta, UNDO_POSITION);
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