//=============================================================================
#include "GameState.h"
#include "Resources.h"
//=============================================================================
enum currMap{first, second, third};
enum GameButtons{ Undo_B, Quit_B, Pause_B};
//=============================================================================
//C-tor, points to the main window and states so it can update if needed
//to remove itself or add another state on top of it (like pause, help etc..).
GameState::GameState(sf::RenderWindow* window, std::stack<std::unique_ptr<State>>* states)
	:State(window, states){
	m_board = new Board(*window);
	m_board->randomLava(DIFFICULTIES[(++m_difficulty) % 3]);
	setBackground(Resources::instance().getTexture((int)Textures::GameBG));
	setButtons();
	setTexts();
	music();
}
//=============================================================================
//
void GameState::music() {
	Resources::instance().playMusic(Sounds::GameMusic);
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
		(UNDO_POS, GAME_BUTTON_SIZE, UNDO_TEXT, sf::Color::Red, sf::Color::Yellow, sf::Color::Green);
}
//=============================================================================
//
void GameState::update(const float& deltaTime) {
	m_time += m_gameClock.restart();

	if (m_board->didPlayerWin())
		updateWin();
	else if (m_board->didCatWin())
		updateLose();
	else
		gameUpdate(deltaTime);
	m_texts[(int)Texts::Counter].setString(CLICKS_TEXT + std::to_string(m_clicks));
}
//=============================================================================
//
void GameState::updateButtons(const float& deltaTime) {
	for (auto& button : m_buttons) {
		button.second->update(m_mouseView, deltaTime);
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
	m_board->draw();
	for (auto i = 0; i < DEEFAULT_TEXTS; ++i) {
		m_window->draw(m_texts[i]);
	}
	for (auto& button : m_buttons)
		button.second->draw(*m_window);

	if (m_board->didPlayerWin())
		m_window->draw(m_texts[(int)Texts::WIN]);
	else if (m_board->didCatWin())
		m_window->draw(m_texts[(int)Texts::Lost]);
}
//=============================================================================
// 
void GameState::updateWin() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		m_board->loadLevel((++m_difficulty) % 3);
		m_time = sf::Time().Zero;
	}
}
//=============================================================================
//
void GameState::updateLose() {
	m_board->update(0);

	if (sf::Event::Closed) {
		m_window->close();
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape)) ||
		sf::Keyboard::isKeyPressed((sf::Keyboard::N))) {
		this->m_end = true;
		Resources::instance().stopMusic();
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Y))) {
		m_clicks = 0;
		m_board->resetLevel();
		m_time = sf::Time().Zero;
	}
}
//=============================================================================
//
void GameState::gameUpdate(const float& deltaTime) {
	updateMouse();
	m_board->update(deltaTime);
	updateButtons(deltaTime);
	m_texts[(int)Texts::Time].setString(TIME_TEXT + std::to_string((int)m_time.asSeconds()));
}
//=============================================================================
//
void GameState::setTexts()
{
	setText(37, TITLE_TEXT, sf::Color::Black, GAME_TITLE_POS);
	setText(25, CLICKS_TEXT, sf::Color::White, CLICKS_POS);
	setText(25, TIME_TEXT, sf::Color::Yellow, TIME_POS);
	setText(35, LOSSING_TEXT, sf::Color::Cyan, LOSSING_POS);
	setText(35, WIN_TEXT, sf::Color::Yellow, WIN_POS);

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