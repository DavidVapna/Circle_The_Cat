//=============================================================================
#include "GameState.h"
#include "Resources.h"
//=============================================================================
enum currMap{first, second, third};
//=============================================================================
//
GameState::GameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
	:State(window, states){
	m_board.randomLava(DIFFICULTIES[(++m_difficulty) % 3]);
	setBackground(Resources::instance().getTexture((int)Textures::GameBG));
    Resources::instance().playMusic(Sounds::GameMusic);
	setTexts();
}
//=============================================================================
//
GameState::~GameState(){

}
//=============================================================================
//
void GameState::setButtons(){
	// m_buttons[(int)MenuButtons::Play_B] = std::make_unique<Button>
	//(PLAY_POS, BUTTONS_SIZE, PLAY_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
	//m_buttons[(int)MenuButtons::Help_B] = std::make_unique<Button>

    return;
}
//=============================================================================
//
void GameState::update(const float& deltaTime){
	m_deltaTime = m_clock.restart().asSeconds();

	m_texts[(int)Texts::Counter].setString(CLICKS_TEXT + std::to_string(m_clicks));

	m_deltaTime = m_gameClock.restart().asSeconds();
	updateInput(m_deltaTime);
	m_board.update(m_deltaTime);

}
//=============================================================================
//
void GameState::updateInput(const float& deltaTime){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
        this->m_end = true;
        Resources::instance().stopMusic();
        return;
    }
}
//=============================================================================
//
void GameState::draw(){
	m_window->draw(m_backGround);

	for (int i = 0; i < 3; i++)
		m_window->draw(m_texts[i]);

	m_board.draw(*m_window);
}
//=============================================================================
//
void GameState::mouseEvent(const sf::Event& evnt){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if (m_board.mouseClicked(m_mouseView)){
			m_clicks++;
		}
		if (m_texts[(int)Texts::Undo].getGlobalBounds().contains(m_mouseView)) {
			m_board.undo();
			m_clicks--;
		}
	}
}
//=============================================================================
//
void GameState::restartLevel(){
	while (m_clicks > 0)
		m_board.undo();
}
//=============================================================================
//
void GameState::handleEvents() {
	if (m_catTurn) {
		catsTurn();
		return;
	}

	for (auto evnt = sf::Event(); m_window->pollEvent(evnt);) {
		switch (evnt.type) {
		case sf::Event::Closed:
			m_window->close(); break;

		case sf::Event::KeyPressed:
			keyBoardEvent(evnt); break;

		case sf::Event::MouseButtonPressed:
			mouseEvent(evnt); break;
		}
	}
}
//=============================================================================
//

//=============================================================================
//
void GameState::catsTurn() {
	if (!m_board.validateRoute()) {
		levelWin(); return;
	}
	m_cat->tryToRun(m_board.escapeTile());
	catJump();
	if (m_cat->didCatWin())
		lostToCat();
	m_catTurn = false;
}
//=============================================================================
void GameState::levelWin(){
	bool stop = false;
	m_catTurn = false;
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
				m_board.nextLevel((++m_difficulty) % 3);
				return;
			}
		}
		m_window->display();
	}
}
//=============================================================================
void GameState::lostToCat(){
	bool stop = false;
	m_catTurn = false;
	while (!stop){
		m_window->clear();
		draw();
		m_window->draw(m_texts[(int)Texts::Lossing]);
		for (auto evnt = sf::Event(); m_window->pollEvent(evnt);){
			switch (evnt.type){
			case sf::Event::Closed:
				stop = true; m_window->close(); break;

			case sf::Event::KeyPressed:{
				switch (evnt.key.code){
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
		m_board.undo(); break;

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